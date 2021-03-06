// Copyright (c) Lawrence Livermore National Security, LLC and other VisIt
// Project developers.  See the top-level LICENSE file for dates and other
// details.  No copyright assignment is required to contribute to VisIt.

// ************************************************************************* //
//  File: avtStaggerFilter.C
// ************************************************************************* //

#include <avtStaggerFilter.h>
#include <vtkDataSet.h>
#include <vtkDataObject.h>
#include <vtkInformation.h>
#include <vtkPointData.h>
#include <vtkCellData.h>
#include <vtkDataArray.h>
#include <DebugStream.h>
#include <vtkStructuredGrid.h>
#include <string>


// ****************************************************************************
//  Method: avtStaggerFilter constructor
//
//  Programmer: mdurant -- generated by xml2avt
//  Creation:   Fri Mar 23 12:44:32 PDT 2012
//
// ****************************************************************************

avtStaggerFilter::avtStaggerFilter()
{
}


// ****************************************************************************
//  Method: avtStaggerFilter destructor
//
//  Programmer: mdurant -- generated by xml2avt
//  Creation:   Fri Mar 23 12:44:32 PDT 2012
//
//  Modifications:
//
// ****************************************************************************

avtStaggerFilter::~avtStaggerFilter()
{
}


// ****************************************************************************
//  Method:  avtStaggerFilter::Create
//
//  Programmer: mdurant -- generated by xml2avt
//  Creation:   Fri Mar 23 12:44:32 PDT 2012
//
// ****************************************************************************

avtFilter *
avtStaggerFilter::Create()
{
    return new avtStaggerFilter();
}


// ****************************************************************************
//  Method:      avtStaggerFilter::SetAtts
//
//  Purpose:
//      Sets the state of the filter based on the attribute object.
//
//  Arguments:
//      a        The attributes to use.
//
//  Programmer: mdurant -- generated by xml2avt
//  Creation:   Fri Mar 23 12:44:32 PDT 2012
//
// ****************************************************************************

void
avtStaggerFilter::SetAtts(const AttributeGroup *a)
{
    atts = *(const StaggerAttributes*)a;
    debug5 <<"offset x = " <<atts.GetOffsetX() <<std::endl;
    debug5 <<"offset y = " <<atts.GetOffsetY()<<std::endl;
    debug5 <<"offset z = " <<atts.GetOffsetZ()<<std::endl;
}


// ****************************************************************************
//  Method: avtStaggerFilter::Equivalent
//
//  Purpose:
//      Returns true if creating a new avtStaggerFilter with the given
//      parameters would result in an equivalent avtStaggerFilter.
//
//  Programmer: mdurant -- generated by xml2avt
//  Creation:   Fri Mar 23 12:44:32 PDT 2012
//
// ****************************************************************************

bool
avtStaggerFilter::Equivalent(const AttributeGroup *a)
{
    return (atts == *(StaggerAttributes*)a);
}


// ****************************************************************************
//  Method: avtStaggerFilter::ExecuteData
//
//  Purpose:
//      Sends the specified input and output through the Stagger filter.
//
//  Arguments:
//      in_dr      The input data representation.
//
//  Returns:       The output data representation.
//
//  Programmer: mdurant -- generated by xml2avt
//  Creation:   Fri Mar 23 12:44:32 PDT 2012
//
//  Modifications:
//    Kathleen Biagas, Thu Oct 18 10:14:54 PDT 2012
//    Preserve coordinate data type.
//
//    Eric Brugger, Thu Aug 14 16:46:42 PDT 2014
//    Modified the class to work with avtDataRepresentation.
//
// ****************************************************************************

avtDataRepresentation *
avtStaggerFilter::ExecuteData(avtDataRepresentation *in_dr)
{
  //
  // Get the VTK data set.
  //
  vtkDataSet *in_ds = in_dr->GetDataVTK();
  
  if (!in_ds) {
    return in_dr;
  }
  
  vtkDataSet* outDS = NULL;
  
  debug5 <<"avtStaggerFilter::ExecuteData()" <<std::endl;
  
  //Extract the offset information from the dataset
  double nodeOffset[3];
  nodeOffset[0] = atts.GetOffsetX();
  nodeOffset[1] = atts.GetOffsetY();
  nodeOffset[2] = atts.GetOffsetZ();
  debug5 <<"avtStaggerFilter::ExecuteData() - offset is " <<nodeOffset[0] <<", " <<nodeOffset[1] <<", " <<nodeOffset[2] <<std::endl;
  
  int dstype = in_ds->GetDataObjectType();
  switch (dstype)
  {
    case VTK_RECTILINEAR_GRID:
      //rv = ReflectRectilinear((vtkRectilinearGrid *) ds, dim);
      debug5 <<"avtStaggerFilter::ExecuteData() - This is a RECTILINEAR grid." <<std::endl;
      break;
    case VTK_STRUCTURED_GRID:
    {
      debug5 <<"avtStaggerFilter::ExecuteData() - This is a STRUCTURED grid." <<std::endl;
      
      vtkStructuredGrid* grid = vtkStructuredGrid::SafeDownCast(in_ds);
      
      vtkStructuredGrid* newGrid = vtkStructuredGrid::New();
      newGrid->ShallowCopy(grid);
      
      vtkPoints* oldPoints = grid->GetPoints();
      vtkIdType numPoints = oldPoints->GetNumberOfPoints();
      vtkPoints* newPoints = vtkPoints::New(oldPoints->GetDataType());
      newPoints->SetNumberOfPoints(numPoints);
      newGrid->SetPoints(newPoints);
      
      int* dims = newGrid->GetDimensions();
      int mulSizes[3];
      debug5 <<"avtStaggerFilter::ExecuteData() - mesh has dimensions " <<dims[0] <<", " <<dims[1] <<", " <<dims[2] <<std::endl;
      mulSizes[0] = 1;
      mulSizes[1] = dims[0];
      mulSizes[2] = dims[0] * dims[1];
      debug5 <<"avtStaggerFilter::ExecuteData() - mulSizes = " <<mulSizes[0] <<", " <<mulSizes[1] <<", " <<mulSizes[2] <<std::endl;
      
      int index[3];
      //Scan through all points and adjust location
      //NOTE - this only works with POSITIVE OFFSETS
      for (vtkIdType k = 0; k < numPoints; k++) {
        // Set the base coordinates
        for (size_t j = 0; j < 3; j++) {
          index[j] = (k / mulSizes[j]) % dims[j];
        }
        
        double originalXYZ[3];
        oldPoints->GetPoint(k, &originalXYZ[0]);
        debug5 <<"avtStaggerFilter::ExecuteData() - point " <<k <<" = (" <<originalXYZ[0] <<", " <<originalXYZ[1] <<", " <<originalXYZ[2] <<")" <<std::endl;
        
        double newXYZ[3];
        newXYZ[0] = originalXYZ[0];
        newXYZ[1] = originalXYZ[1];
        newXYZ[2] = originalXYZ[2];
        // Apply node offsets
        for (size_t j1 = 0; j1 < 3; j1++) {
          //debug5 <<"j1 = " <<j1 <<std::endl;
          //debug5 <<"nodeOffset[j1] = " <<nodeOffset[j1] <<std::endl;
          // Must be inside domain, no offset if hitting the boundary
          if (index[j1] < dims[j1] - 1) {
            int kPlus = k + mulSizes[j1];
            double otherXYZ[3];
            oldPoints->GetPoint(kPlus, &otherXYZ[0]);
            //debug5 <<"avtStaggerFilter::ExecuteData() - neighbor point point(#" <<kPlus <<") = (" <<otherXYZ[0] <<", " <<otherXYZ[1] <<", " <<otherXYZ[2] <<")" <<std::endl;
            for (size_t j2 = 0; j2 < 3; j2++) {
              //debug5 <<"avtStaggerFilter::ExecuteData() - otherXYZ[" <<j2 <<"] = " <<otherXYZ[j2] <<std::endl;
              //debug5 <<"avtStaggerFilter::ExecuteData() - xyz[" <<j2 <<"] = " <<xyz[j2] <<std::endl;
              double difference = otherXYZ[j2] - originalXYZ[j2];
              double displacement = difference * nodeOffset[j1];
              //debug5 <<"avtStaggerFilter::ExecuteData() - j2 = " <<j2 <<" difference = " <<difference <<"  displacement = " <<displacement <<std::endl;
              newXYZ[j2] += displacement;
              //debug5 <<"avtStaggerFilter::ExecuteData() - newXYZ = " <<newXYZ[j2] <<std::endl;
            }
          }
        }
        
        debug5 <<"avtStaggerFilter::ExecuteData() - displaced point[" <<k <<"] = " <<newXYZ[0] <<", " <<newXYZ[1] <<", " <<newXYZ[2] <<std::endl;
        newPoints->SetPoint(k, newXYZ[0], newXYZ[1], newXYZ[2]);
      }
      
      outDS = newGrid;
    }
      break;
      
    case VTK_UNSTRUCTURED_GRID:
      debug5 <<"avtStaggerFilter::ExecuteData() -This is an UNSTRUCTURED grid." <<std::endl;
      break;
    case VTK_POLY_DATA:
      debug5 <<"avtStaggerFilter::ExecuteData() -This is a POLY_DATA grid." <<std::endl;
      //rv = ReflectPointSet((vtkPointSet *) ds, dim);
      break;
    default:
      debug1 << "avtStaggerFilter::ExecuteData() - Unknown data type = " << dstype << endl;
      break;
  }  //end switch(dstype)
  
  if (outDS) {
    avtDataRepresentation *out_dr = new avtDataRepresentation(outDS,
        in_dr->GetDomain(), in_dr->GetLabel());

    outDS->Delete();

    return out_dr;
  }
  
  return in_dr;
}

// ****************************************************************************
// Method: avtStaggerFilter::UpdateDataObjectInfo
//
// Purpose:
//   Update the data object information.
//
// Note:       Work partially supported by DOE Grant SC0007548.
//
// Programmer: Brad Whitlock
// Creation:   Tue Mar 18 10:49:16 PDT 2014
//
// Modifications:
//
// ****************************************************************************

void
avtStaggerFilter::UpdateDataObjectInfo(void)
{
    avtPluginDataTreeIterator::UpdateDataObjectInfo();
    GetOutput()->GetInfo().GetAttributes().AddFilterMetaData("Stagger");
}
