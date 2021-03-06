// Copyright (c) Lawrence Livermore National Security, LLC and other VisIt
// Project developers.  See the top-level LICENSE file for dates and other
// details.  No copyright assignment is required to contribute to VisIt.

// ************************************************************************* //
//                             avtIVPVTKField.C                              //
// ************************************************************************* //

#include <avtIVPVTKField.h>

#include <vtkUnsignedCharArray.h>
#include <vtkDataSet.h>
#include <vtkPointData.h>
#include <vtkCellData.h>
#include <vtkFieldData.h>
#include <vtkDoubleArray.h>
#include <vtkGenericCell.h>

#include <limits>

#include <DebugStream.h>

// ****************************************************************************
//  Method: avtIVPVTKField constructor
//
//  Programmer: Christoph Garth
//  Creation:   February 25, 2008
//
//  Modifications:
//
//    Hank Childs, Thu Apr  2 16:40:08 PDT 2009
//    Use vtkVisItInterpolatedVelocityField, not vtkInterpolatedVelocityField.
//
//   Christoph Garth, Fri Jul 9, 10:10:22 PDT 2010
//   Incorporate vtkVisItInterpolatedVelocityField in avtIVPVTKField.
//
// ****************************************************************************

avtIVPVTKField::avtIVPVTKField( vtkDataSet* dataset, avtCellLocator* locator ) 
  : ds(dataset), loc(locator)
{
    if( ds )
        ds->Register( NULL );

    if( (velData = ds->GetPointData()->GetVectors()) ) {
        velCellBased = false;
    }
    else if( (velData = ds->GetCellData()->GetVectors()) ) {
        velCellBased = true;
    }
    else 
    {
        velData = 0;
        EXCEPTION1( ImproperUseException, "avtIVPVTKField: Can't locate vectors to interpolate." );
    }

    directionless = false;

    lastCell = -1;
    lastPos.x = lastPos.y = lastPos.z =
        std::numeric_limits<double>::quiet_NaN();

    std::fill( sclData, sclData+256, (vtkDataArray*)NULL );
    std::fill( sclCellBased, sclCellBased+256, false );

    // Periodic boundaries are posible.
    vtkFieldData *fieldData = ds->GetFieldData();

    vtkDoubleArray *boundaries = 
      (vtkDoubleArray *) fieldData->GetAbstractArray("Periodic Boundaries");
    
    if( boundaries )
    {
      hasPeriodicBoundaries = true;
      periodic_boundary_x = boundaries->GetValue(0);
      periodic_boundary_y = boundaries->GetValue(1);
      periodic_boundary_z = boundaries->GetValue(2);
    }
    else
      hasPeriodicBoundaries =
        periodic_boundary_x = periodic_boundary_y = periodic_boundary_z = 0;
}

// ****************************************************************************
//  Method: avtIVPVTKField destructor
//
//  Programmer: Christoph Garth
//  Creation:   February 25, 2008
//
//   Christoph Garth, Fri Jul 9, 10:10:22 PDT 2010
//   Incorporate vtkVisItInterpolatedVelocityField in avtIVPVTKField.
//
//   David Camp, Fri Jul 29 06:55:39 PDT 2011
//   Release loc data set.
// ****************************************************************************

avtIVPVTKField::~avtIVPVTKField()
{
    if (ds)
        ds->Delete();
    if (loc)
       loc->ReleaseDataSet();
}

// ****************************************************************************
//  Method: avtIVPVTKField::GetExtents
//
//  Purpose:
//      Get field bounding box.
//
//  Programmer: Dave Pugmire
//  Creation:   June 8, 2009
//
//  Modifications:
//
//   Christoph Garth, Fri Jul 9, 10:10:22 PDT 2010
//   Incorporate vtkVisItInterpolatedVelocityField in avtIVPVTKField.
//
// ****************************************************************************

void
avtIVPVTKField::GetExtents( double extents[6] ) const
{
    ds->GetBounds(extents);
}

// ****************************************************************************
//  Method: avtIVPVTKField::FindCell
//
//  Purpose:
//      Find the cell containing a given position. Does nothing
//      if this coincides with the position of the last lookup.
//      Returns true if a cell was found, false otherwise.
//
//  Programmer: Christoph Garth
//  Creation:   July 12, 2010
//
//  Modifications:
//
//   Dave Pugmire, Mon Feb  7 13:46:56 EST 2011
//   Fix ghost mask for ghost cell integration.
//
//   Christoph Garth, Tue Mar 6 16:38:00 PDT 2012
//   Moved ghost data handling into cell locator and changed IsInside()
//   to only consider non-ghost cells.
//
// ****************************************************************************

avtIVPField::Result
avtIVPVTKField::FindCell( const double& time, const avtVector& pos ) const
{
    if (pos != lastPos)
    {
        lastPos  = pos;

        if( hasPeriodicBoundaries )
        {
          avtVector pt = pos;

          if( periodic_boundary_x > 0 )
          {
            while(                pt.x < 0    ) pt.x += periodic_boundary_x;
            while( periodic_boundary_x < pt.x ) pt.x -= periodic_boundary_x;
          }

          if( periodic_boundary_y > 0 )
          {
            while(                pt.y < 0   ) pt.y += periodic_boundary_y;
            while( periodic_boundary_y < pt.y ) pt.y -= periodic_boundary_y;
          }

          if( periodic_boundary_z > 0 )
          {
            while(                pt.z < 0    ) pt.z += periodic_boundary_z;
            while( periodic_boundary_z < pt.z ) pt.z -= periodic_boundary_z;
          }

          lastCell = loc->FindCell(&pt.x, &lastWeights, false);
        }
        else
          lastCell = loc->FindCell(&pos.x, &lastWeights, false);
    }
    
    return (lastCell != -1 ? OK : OUTSIDE_SPATIAL);
}

// ****************************************************************************
//  Method: avtIVPVTKField::operator
//
//  Purpose:
//      Evaluates a point location by consulting a VTK grid.
//
//  Programmer: Christoph Garth
//  Creation:   February 25, 2008
//
//  Modifications:
//
//    Hank Childs, Thu Apr  2 16:40:08 PDT 2009
//    Use vtkVisItInterpolatedVelocityField, not vtkInterpolatedVelocityField.
//
//    Dave Pugmire, Tue Dec  1 11:50:18 EST 2009
//    Switch from avtVec to avtVector.
//
//   Christoph Garth, Fri Jul 9, 10:10:22 PDT 2010
//   Incorporate vtkVisItInterpolatedVelocityField in avtIVPVTKField.
//
// ****************************************************************************

avtIVPField::Result
avtIVPVTKField::operator()(const double &t, const avtVector &p, avtVector &retV) const
{
    if (FindCell(t, p) != OK || !FindValue(velData, retV))
        return OUTSIDE_SPATIAL;
    else
        return OK;
}

// ****************************************************************************
//  Method: avtIVPVTKField::FindValue
//
//  Purpose:
//      Evaluates a point after consulting a VTK grid.
//
//  Programmer: Christoph Garth
//  Creation:   February 25, 2008
//
// ****************************************************************************

bool
avtIVPVTKField::FindValue(vtkDataArray *vectorData, avtVector &vel) const
{
    if( directionless )
    {
      avtVector lastVel = vel;  // Save obtaining the dot product.

      // Cell based with directionless field.
      if (velCellBased)
      {
        vectorData->GetTuple(lastCell, &vel.x);

        // For a directionless field orient each vector so that it is
        // in the same direction as the last vector.
        if(lastVel.dot( vel ) < 0 )
          vel *= -1.0;
      }

      // Node based with directionless field.
      else
      {
        vel.x = vel.y = vel.z = 0.0;

        for (avtInterpolationWeights::const_iterator wi=lastWeights.begin();
             wi!=lastWeights.end(); ++wi)
        {
          double tmp[3];
          vectorData->GetTuple( wi->i, tmp );

          // For a directionless field orient each vector so that it is
          // in the same direction as the last vector.
          if( tmp[0]*lastVel.x + tmp[1]*lastVel.y + tmp[2]*lastVel.z < 0 )
          {
            vel.x -= wi->w * tmp[0];
            vel.y -= wi->w * tmp[1];
            vel.z -= wi->w * tmp[2];
          }
          else
          {
            vel.x += wi->w * tmp[0];
            vel.y += wi->w * tmp[1];
            vel.z += wi->w * tmp[2];
          }
        }
      }
      
      lastVel = vel;
    }

    // Cell based with directional field.
    else if (velCellBased)
    {
      vectorData->GetTuple(lastCell, &vel.x);
    }

    // Node based with directional field.
    else
    {
      vel.x = vel.y = vel.z = 0.0;

      for (avtInterpolationWeights::const_iterator wi=lastWeights.begin();
           wi!=lastWeights.end(); ++wi)
      {
        double tmp[3];
        vectorData->GetTuple( wi->i, tmp );
        
        vel.x += wi->w * tmp[0];
        vel.y += wi->w * tmp[1];
        vel.z += wi->w * tmp[2];
      }
    }

    return true;
}

// ****************************************************************************
//  Method: avtIVPVTKField::ConvertToCartesian
//
//  Purpose: Does nothing because the original coordinate system is
//      unknown.
//
//  Programmer: Christoph Garth
//  Creation:   February 25, 2008
//
// ****************************************************************************

avtVector 
avtIVPVTKField::ConvertToCartesian(const avtVector& pt) const
{
    return pt;
}

// ****************************************************************************
//  Method: avtIVPVTKField::ConvertToCylindrical
//
//  Purpose: Does nothing because the original coordinate system is
//      unknown.
//
//  Programmer: Christoph Garth
//  Creation:   February 25, 2008
//
// ****************************************************************************

avtVector 
avtIVPVTKField::ConvertToCylindrical(const avtVector& pt) const
{
    return pt;
}

// ****************************************************************************
//  Method: avtIVPVTKField::ComputeVorticity
//
//  Purpose:
//      Computes the vorticity at a point.
//
//  Programmer: Christoph Garth
//  Creation:   February 25, 2008
//
//  Modifications:
//
//    Hank Childs, Tue Aug 19 16:59:16 PDT 2008
//    Increase the size of the "w" (weights) variable to prevent stack 
//    overwrites.
//
//    Hank Childs, Thu Apr  2 16:40:08 PDT 2009
//    Use vtkVisItInterpolatedVelocityField, not vtkInterpolatedVelocityField.
//
//    Dave Pugmire, Tue Dec  1 11:50:18 EST 2009
//    Switch from avtVec to avtVector.
//
//    Christoph Garth, Fri Jul 9, 10:10:22 PDT 2010
//    Incorporate vtkVisItInterpolatedVelocityField in avtIVPVTKField, and
//    use vtkGenericCell for thread safety.
//
// ****************************************************************************

double
avtIVPVTKField::ComputeVorticity( const double& t, const avtVector &pt ) const
{
    if( velCellBased )
        return 0.0;

    avtVector y;
    this->operator()( t, pt, y );

    double ylen = y.length();

    if( ylen == 0.0 )
        return 0.0;

    double derivs[9], *vel = new double[3*lastWeights.size()];

    for( unsigned int i=0; i<lastWeights.size(); ++i )
        velData->GetTuple( lastWeights[i].i, vel + 3*i );
         
    vtkGenericCell *cell = vtkGenericCell::New();
    ds->GetCell( lastCell, cell );


    {
        double tmp1[3], pcoord[3], dist2, w[1024];
        int subid;

        cell->EvaluatePosition( (double*)&pt.x, tmp1, subid, pcoord, dist2, w );
        cell->Derivatives( 0, pcoord, vel, 3, derivs );
    }

    delete[] vel;
    cell->Delete();

    avtVector vort( derivs[7]-derivs[5],
                    derivs[2]-derivs[6],
                    derivs[3]-derivs[1] );

    return (vort * y) / ylen;
}

// ****************************************************************************
//  Method: avtIVPVTKField::ComputeScalarVariable
//
//  Purpose:
//      Computes the variable value at a point.
//
//  Programmer: Dave Pugmire
//  Creation:   June 5, 2009
//
//  Modifications:
//
//    Dave Pugmire, Tue Dec  1 11:50:18 EST 2009
//    Switch from avtVec to avtVector.
//
//   Dave Pugmire, Tue Dec 29 14:37:53 EST 2009
//   Generalize the compute scalar variable.
//
//   Christoph Garth, Fri Jul 9, 10:10:22 PDT 2010
//   Incorporate vtkVisItInterpolatedVelocityField in avtIVPVTKField.
//
// ****************************************************************************

double
avtIVPVTKField::ComputeScalarVariable(unsigned char index,
                                      const double& t,
                                      const avtVector &pt) const
{
    vtkDataArray* data = sclData[index];

    if( data == NULL )
        return 0.0;

    if (FindCell(t, pt) != OK)
        return 0.0;

    double result = 0.0, tmp;

    if( !sclCellBased[index] )
    {
        for( avtInterpolationWeights::const_iterator wi=lastWeights.begin();
             wi!=lastWeights.end(); ++wi )
        {
            data->GetTuple( wi->i, &tmp );
            result += wi->w * tmp;
        }
    }
    else
    {
        sclData[index]->GetTuple( lastCell, &result );
    }

    return result;
}

// ****************************************************************************
//  Method: avtIVPVTKField::SetScalarVariable
//
//  Purpose:
//      Set up a scalar variable for query through ComputeScalarVariable().
//
//  Programmer: Christoph Garth
//  Creation:   July 13, 2010
//
// ****************************************************************************

void
avtIVPVTKField::SetScalarVariable(unsigned char index, const std::string& name)
{
    vtkDataArray* data;
    bool cellBased;

    if( (data = ds->GetPointData()->GetScalars( name.c_str() )) ) {
        cellBased = false;
    }
    else if( (data = ds->GetCellData()->GetScalars( name.c_str() )) ) {
        cellBased = true;
    }
    else 
        EXCEPTION1( ImproperUseException, 
                    "avtIVPVTKField: Can't locate scalar \"" + name + 
                    "\" to interpolate." );

    if( data->GetNumberOfComponents() != 1 )
        EXCEPTION1( ImproperUseException,
                    "avtIVPVTKField: Given variable \"" + name +
                    "\" is not scalar." );
        
    sclData[index] = data;
    sclCellBased[index] = cellBased;
}

// ****************************************************************************
//  Method: avtIVPVTKField::IsInside
//
//  Purpose:
//      Determines if a point is inside a field, excluding any 
//      ghost regions.
//
//  Programmer: Christoph Garth
//  Creation:   February 25, 2008
//
//  Modifications:
//
//    Hank Childs, Thu Apr  2 16:40:08 PDT 2009
//    Use vtkVisItInterpolatedVelocityField, not vtkInterpolatedVelocityField.
//
//    Dave Pugmire, Tue Dec  1 11:50:18 EST 2009
//    Switch from avtVec to avtVector.
//
//    Christoph Garth, Fri Jul 9, 10:10:22 PDT 2010
//    Incorporate vtkVisItInterpolatedVelocityField in avtIVPVTKField.
//
//    Christoph Garth, Tue Mar 6, 16:22:00 PDT 2012
//    Explicitly exclude ghost cells.
//    
// ****************************************************************************

avtIVPField::Result
avtIVPVTKField::IsInside(const double &t, const avtVector &pt) const
{
    return (loc->FindCell(&pt.x, NULL, true) >= 0 ? OK : OUTSIDE_SPATIAL);
}

// ****************************************************************************
//  Method: avtIVPVTKField::GetTimeRange
//
//  Purpose:
//      Returns temporal extent of the field.
//
//  Programmer: Dave Pugmire
//  Creation:   August 6, 2008
//
// ****************************************************************************

void
avtIVPVTKField::GetTimeRange(double range[2]) const
{
    range[0] = -std::numeric_limits<double>::infinity();
    range[1] =  std::numeric_limits<double>::infinity();
}

// ****************************************************************************
//  Method: avtIVPVTKField::HasPeriodicBoundaries
//
//  Purpose:
//      
//
//  Programmer: Allen Sanderson
//  Creation:   April 16, 2015
//
// ****************************************************************************

bool
avtIVPVTKField::HasPeriodicBoundaries() const
{
  return hasPeriodicBoundaries;
}


// ****************************************************************************
//  Method: avtIVPVTKField::HasPeriodicBoundaries
//
//  Purpose:
//      
//
//  Programmer: Allen Sanderson
//  Creation:   April 16, 2015
//
// ****************************************************************************

void
avtIVPVTKField::GetBoundaries( double& x,
                               double& y,
                               double& z) const
{
  x = periodic_boundary_x;
  y = periodic_boundary_y;
  z = periodic_boundary_z;
}
