// Copyright (c) Lawrence Livermore National Security, LLC and other VisIt
// Project developers.  See the top-level LICENSE file for dates and other
// details.  No copyright assignment is required to contribute to VisIt.

// ****************************************************************************
//  avtMeshPlot.C
// ****************************************************************************

#include <avtMeshPlot.h>

#include <vtkLookupTable.h>

#include <ColorAttribute.h>
#include <MeshAttributes.h>
#include <PointGlyphAttributes.h>

#include <avtColorTables.h>
#include <avtMeshFilter.h>
#include <avtMeshPlotMapper.h>
#include <avtSmoothPolyDataFilter.h>
#include <avtVariableLegend.h>
#include <avtVertexExtractor.h>

#include <DebugStream.h>


// ****************************************************************************
//  Method: avtMeshPlot constructor
//
//  Programmer: Kathleen Bonnell
//  Creation:   March 21, 2001
//
//  Modifications:
//
//    Kathleen Bonnell, Fri Jun 15 14:58:51 PDT 2001
//    Added initialization of filter.
//
//    Kathleen Bonnell, Wed Aug 22 15:22:55 PDT 2001
//    Intialize new renderer, mapper and property.
//
//    Kathleen Bonnell, Wed Sep  5 12:34:40 PDT 2001
//    Getting run-time warnings about legend not having a lut (even though one
//    isn't needed in this case.)  Send a default lut to the legend to
//    remove these warnings.
//
//    Kathleen Bonnell, Wed Sep 26 15:19:31 PDT 2001
//    Initialize fgColor, bgColor.
//
//    Kathleen Bonnell, Wed Sep 26 17:47:41 PDT 2001
//    Use new renderer methods for turning off primitive drawing.
//
//    Hank Childs, Tue Apr 23 20:16:50 PDT 2002
//    Instatiate the renderer through 'New' to insulate from graphics
//    library issues.
//
//    Hank Childs, Mon May 20 10:47:18 PDT 2002
//    Reflect that our renderer is now reference counted.
//
//    Hank Childs, Sun Jun 23 21:07:55 PDT 2002
//    Initialize the glyph filter.
//
//    Jeremy Meredith, Mon Jul  8 18:38:04 PDT 2002
//    Added facelist filter.
//
//    Hank Childs, Fri Jul 19 08:41:39 PDT 2002
//    Opted to use the ghost zone and facelist filter instead.
//
//    Kathleen Bonnell, Wed Aug 14 12:33:59 PDT 2002
//    Tell the renderer to ignore lighting.
//
//    Jeremy Meredith, Tue Dec 10 10:00:34 PST 2002
//    Added poly data smooth filter.
//
//    Eric Brugger, Wed Jul 16 10:57:44 PDT 2003
//    Modified to work with the new way legends are managed.
//
//    Kathleen Bonnell, Thu Aug 28 10:03:42 PDT 2003
//    Initialize opaqueMeshIsAppropriate.
//
//    Kathleen Bonnell, Tue Nov  2 10:41:33 PST 2004
//    Initialize glyphMapper, remove glyphPoints.
//
//    Kathleen Bonnell, Tue Nov  2 10:41:33 PST 2004
//    Replaced avtPointGlyphMapper with avtVariablePointGlyphMapper.
//
//    Hank Childs, Wed Dec 27 13:51:01 PST 2006
//    Make sure that ghost data is removed.
//
//    Jeremy Meredith, Tue Oct 14 15:47:40 EDT 2008
//    Don't set the create-poly-data flag in the gz/fl filter here; we
//    can sometimes avoid it (and get better performance), but we don't
//    know that until we're about to execute it.
//
//    Kathleen Biagas, Wed Jun 10 13:00:59 PDT 2020
//    Add vertexExtractor, remove glyphMapper.
//
// ****************************************************************************

avtMeshPlot::avtMeshPlot()
{
    filter = NULL;
    smooth             = new avtSmoothPolyDataFilter();
    ghostAndFaceFilter = new avtGhostZoneAndFacelistFilter;
    ghostAndFaceFilter->SetUseFaceFilter(true);
    ghostAndFaceFilter->GhostDataMustBeRemoved();
    vertexExtractor = nullptr;

    mapper = new avtMeshPlotMapper();

    varLegend = new avtVariableLegend;
    varLegend->SetTitle("Mesh");
    vtkLookupTable *lut = vtkLookupTable::New();
    varLegend->SetLookupTable(lut);
    lut->Delete();
    varLegend->SetColorBarVisibility(0);
    varLegend->SetVarRangeVisibility(0);

    bgColor[0] = bgColor[1] = bgColor[2] = 1.0;  // white
    fgColor[0] = fgColor[1] = fgColor[2] = 0.0;  // black

    wireframeRenderingIsInappropriate = false;

    //
    // This is to allow the legend to be reference counted so the behavior can
    // still access it after the plot is deleted.  The legend cannot be
    // reference counted all of the time since we need to know that it is a
    // VariableLegend.
    //
    varLegendRefPtr = varLegend;
}


// ****************************************************************************
//  Method: avtMeshPlot destructor
//
//  Programmer: Kathleen Bonnell
//  Creation:   March 21, 2001
//
//  Modifications:
//
//    Kathleen Bonnell, Fri Jun 15 14:58:51 PDT 2001
//    Added destruction of filter.
//
//    Kathleen Bonnell, Wed Aug 22 15:22:55 PDT 2001
//    Destruct new renderer, mapper and property.
//
//    Hank Childs, Mon May 20 10:47:18 PDT 2002
//    Do not delete the renderer, because it is now reference counted.
//
//    Hank Childs, Sun Jun 23 21:09:56 PDT 2002
//    Destruct glyphPoints.
//
//    Jeremy Meredith, Mon Jul  8 18:38:04 PDT 2002
//    Destruct facelist filter.
//
//    Hank Childs, Fri Jul 19 08:41:39 PDT 2002
//    Renamed facelistFilter to ghostAndFaceFilter
//
//    Jeremy Meredith, Tue Dec 10 10:00:09 PST 2002
//    Added poly data smooth filter.
//
//    Kathleen Bonnell, Tue Nov  2 10:41:33 PST 2004
//    Added glyphMapper, removed glyphPoints.
//
//    Kathleen Biagas, Wed Jun 10 13:00:59 PDT 2020
//    Add vertexExtractor, remove glyphMapper.
//
// ****************************************************************************

avtMeshPlot::~avtMeshPlot()
{
    if (filter != NULL)
    {
        delete filter;
        filter = NULL;
    }
    if (ghostAndFaceFilter != NULL)
    {
        delete ghostAndFaceFilter;
        ghostAndFaceFilter = NULL;
    }
    if (mapper != NULL)
    {
        delete mapper;
        mapper = NULL;
    }
    if (smooth != NULL)
    {
        delete smooth;
        smooth = NULL;
    }
    if (vertexExtractor != nullptr)
    {
        delete vertexExtractor;
        vertexExtractor = nullptr;
    }

    //
    // Do not delete the varLegend since it is being held by varLegendRefPtr.
    //
}


// ****************************************************************************
//  Method:  avtMeshPlot::Create
//
//  Purpose:
//    Call the constructor.
//
//  Programmer:  Kathleen Bonnell
//  Creation:    March 21, 2001
//
// ****************************************************************************

avtPlot*
avtMeshPlot::Create()
{
    return new avtMeshPlot;
}

// ****************************************************************************
//  Method:  avtMeshPlot::SetCellCountMultiplierForSRThreshold
//
//  Purpose: Sets number of polygons each point in the plot's output will be
//  glyphed into.
//
//  Programmer:  Mark C. Miller
//  Creation:    August 12, 2004
//
//  Modifications:
//
//    Mark C. Miller, Mon Aug 23 20:24:31 PDT 2004
//    Changed to the Set... method (Get is now done in avtPlot.C)
//
// ****************************************************************************

void
avtMeshPlot::SetCellCountMultiplierForSRThreshold(const avtDataObject_p dob)
{
    if (*dob)
    {
        int dim = dob->GetInfo().GetAttributes().GetSpatialDimension();
        if (dim == 0)
            cellCountMultiplierForSRThreshold = 6.0;
        else
            cellCountMultiplierForSRThreshold = 1.0;
    }
}

// ****************************************************************************
//  Method: avtMeshPlot::SetAtts
//
//  Purpose:
//      Sets the atts for the mesh plot.
//
//  Arguments:
//      atts    The attributes for this mesh plot.
//
//  Programmer: Kathleen Bonnell
//  Creation:   March 05, 2001
//
//  Modifications:
//    Jeremy Meredith, Tue Jun  5 20:33:13 PDT 2001
//    Added code to set a flag if the plot needs recalculation.  Also
//    store the attributes as a class member.
//
//    Kathleen Bonnell, Mon Jun 25 09:03:29 PDT 2001
//    Added call to SetRenderOpaque, removed call to SetMeshColor, SetLegend,
//    already part of 'CustomizeBehavior'. No need to call them twice.
//
//    Kathleen Bonnell, Mon Jun 25 09:03:29 PDT 2001
//    Modified arguments to SetLineWidth/Style.
//
//    Eric Brugger, Fri Sep  7 15:19:03 PDT 2001
//    I moved the calls to SetMeshColor, SetOpaqueColor and SetLegend from
//    CustomizeBehavior to here, since this is appropriate place for them.
//
//    Kathleen Bonnell, Wed Sep 26 15:19:31 PDT 2001
//    Added logic to handle new meshAtts ForgroundFlag and BackgroundFlag.
//
//    Kathleen Bonnell, Mon Mar 24 17:48:27 PST 2003
//    Call SetOpaqueColor and SetMeshColor instead of setting property's
//    color directly.
//
//    Kathleen Bonnell, Thu Sep  4 11:15:30 PDT 2003
//    SetRenderOpaque no longer requires an argument.
//
//    Kathleen Bonnell, Thu Feb  5 13:15:08 PST 2004
//    Added spatialDim in call to atts.ChangesRequireRecalculation.
//
//    Kathleen Bonnell, Tue Nov  2 10:41:33 PST 2004
//    Set up glyphMapper.
//
//    Kathleen Bonnell, Tue Nov  2 10:41:33 PST 2004
//    Updated glyphMapper methods calls with new names.
//
//    Brad Whitlock, Wed Jul 20 13:26:13 PST 2005
//    I made the pointSize in the atts be used for to set the point size for
//    points, which is not the same as what's used for Box, Axis, Icosahedra.
//
//    Jeremy Meredith, Fri Feb 20 17:25:49 EST 2009
//    Added per-plot alpha support.
//
//    Brad Whitlock, Mon Jan  7 17:00:39 PST 2013
//    I added some new glyph types.
//
//    Kathleen Biagas, Wed Dec 21 08:07:48 PST 2016
//    Glyph types now in central location, can pass pointType directly to
//    mapper.
//
//    Kathleen Biagas, Wed Jun 10 13:00:59 PDT 2020
//    Remove glyphMapper.
//
// ****************************************************************************

void
avtMeshPlot::SetAtts(const AttributeGroup *a)
{
    int const maxColorsToTry = 50;

    needsRecalculation =
        atts.ChangesRequireRecalculation(*(const MeshAttributes*)a,
        behavior->GetInfo().GetAttributes().GetSpatialDimension());

    atts = *(const MeshAttributes*)a;

    SetLineWidth(Int2LineWidth(atts.GetLineWidth()));
    if (atts.GetMeshColorSource() == MeshAttributes::Foreground)
    {
        SetMeshColor(fgColor);
    }
    else if (atts.GetMeshColorSource() == MeshAttributes::MeshRandom)
    {
        unsigned char rgb[3] = {0,0,0};
        unsigned char bg[3] = {static_cast<unsigned char>(bgColor[0]*255),
                               static_cast<unsigned char>(bgColor[1]*255),
                               static_cast<unsigned char>(bgColor[2]*255)};
        avtColorTables *ct = avtColorTables::Instance();
        if (! ct->GetJNDControlPointColor(ct->GetDefaultDiscreteColorTable(), this->instanceIndex, bg, rgb))
            ct->GetJNDControlPointColor("distinct", this->instanceIndex, bg, rgb);
        SetMeshColor(rgb);
    }
    else // MeshAttributes::MeshCustom
    {
        SetMeshColor(atts.GetMeshColor().GetColor());
    }

    SetRenderOpaque();
    if (atts.GetOpaqueColorSource() == MeshAttributes::Background)
    {
        SetOpaqueColor(bgColor);
    }
    else if (atts.GetOpaqueColorSource() == MeshAttributes::OpaqueRandom)
    {
        unsigned char rgb[3] = {0,0,0};
        avtColorTables *ct = avtColorTables::Instance();
        if (! ct->GetControlPointColor(ct->GetDefaultDiscreteColorTable(), this->instanceIndex+1, rgb))
            ct->GetControlPointColor("distinct", this->instanceIndex+1, rgb);
        SetOpaqueColor(rgb);
    }
    else // MeshAttributes::OpaqueCustom
    {
        SetOpaqueColor(atts.GetOpaqueColor().GetColor());
    }
    SetLegend(atts.GetLegendFlag());

    //
    // Setup glyphMapper
    //
    mapper->SetScale(atts.GetPointSize());

    if (atts.GetPointSizeVarEnabled() &&
        atts.GetPointSizeVar() != "default" &&
        atts.GetPointSizeVar() != "" &&
        atts.GetPointSizeVar() != "\0")
    {
        mapper->ScaleByVar(atts.GetPointSizeVar());
    }
    else
    {
        mapper->DataScalingOff();
    }
    mapper->SetGlyphType(atts.GetPointType());

    SetPointGlyphSize();

    //
    // Do the opacity stuff
    //
    double opacity = atts.GetOpacity();
    mapper->SetOpacity(opacity);
    behavior->SetRenderOrder((atts.GetOpacity() < 1.0) ?
                             ABSOLUTELY_LAST : DOES_NOT_MATTER);
    behavior->SetAntialiasedRenderOrder(ABSOLUTELY_LAST);
}


// ****************************************************************************
//  Method: avtMeshPlot::SetMeshColor
//
//  Purpose:
//      Sets the color of the mesh.
//
//  Arguments:
//      col      The color for the mesh.
//
//  Programmer:   Kathleen Bonnell
//  Creation:     March 21, 2001
//
//  Modifications:
//
//    Kathleen Bonnell, Mon Jun 25 09:03:29 PDT 2001
//    Set property edge color instead of mapper actor color.
//
//    Kathleen Bonnell, Mon Mar 24 17:48:27 PST 2003
//    Added call to SetOpaqueColor.
//
//    Mark C. Miller, Wed Jun 19 22:26:53 PDT 2019
//    Simplify. Delegate to the double method.
// ****************************************************************************

void
avtMeshPlot::SetMeshColor(const unsigned char *col)
{
    double rgb[3] = {col[0]/255.0,col[1]/255.0,col[2]/255.0};
    SetMeshColor(rgb);
}

// ****************************************************************************
//  Method: avtMeshPlot::SetMeshColor
//
//  Purpose:
//      Sets the color of the mesh.
//
//  Arguments:
//      col      The color for the mesh.
//
//  Programmer:   Kathleen Bonnell
//  Creation:     March 24, 2003
//
//  Modifications:
//    Kathleen Biagas, Wed Jun 10 13:00:59 PDT 2020
//    Remove glyphMapper.
//
// ****************************************************************************

void
avtMeshPlot::SetMeshColor(const double *col)
{
    double rgb[3];
    std::copy(col,col+3,rgb);
    mapper->SetMeshColor(rgb);

    if (wireframeRenderingIsInappropriate)
    {
        SetOpaqueColor(col, true);
    }
}

// ****************************************************************************
//  Method: avtMeshPlot::SetOpaqueColor
//
//  Purpose:
//      Sets the color of the opaque portion.
//
//  Arguments:
//      col      The color for the opaque portion.
//
//  Programmer:   Kathleen Bonnell
//  Creation:     September 5, 2001
//
//  Modifications:
//    Kathleen Bonnell, Mon Mar 24 17:48:27 PST 2003
//    The opaque color should match the mesh color if wireframe rendering
//    is inappropriate.  Don't allow the color to be set incorrectly.
//
//    Mark C. Miller, Wed Jun 19 22:34:38 PDT 2019
//    Simplify. Delegate to double method.
// ****************************************************************************

void
avtMeshPlot::SetOpaqueColor(const unsigned char *col, bool force)
{
    double rgb[3] = {col[0]/255.0,col[1]/255.0,col[2]/255.0};
    SetOpaqueColor(rgb, force);
}

// ****************************************************************************
//  Method: avtMeshPlot::SetOpaqueColor
//
//  Purpose:
//      Sets the color of the opaque portion.
//
//  Arguments:
//      col    The color for the opaque portion.
//
//  Programmer:   Kathleen Bonnell
//  Creation:     March 24, 2003
//
// ****************************************************************************

void
avtMeshPlot::SetOpaqueColor(const double *col, bool force)
{
    if (!wireframeRenderingIsInappropriate || force)
    {
        double rgb[3];
        std::copy(col,col+3,rgb);
        mapper->SetSurfaceColor(rgb);
    }
}

// ****************************************************************************
//  Method: avtMeshPlot::SetLegend
//
//  Purpose:
//      Turns the legend on or off.
//
//  Arguments:
//      legendOn     true if the legend should be turned on, false otherwise.
//
//  Programmer: Kathleen Bonnell
//  Creation:   March 21, 2001
//
// ****************************************************************************

void
avtMeshPlot::SetLegend(bool legendOn)
{
    if (legendOn)
    {
        varLegend->LegendOn();
    }
    else
    {
        varLegend->LegendOff();
    }
}


// ****************************************************************************
//  Method: avtMeshPlot::SetLineWidth
//
//  Purpose:
//      Sets the line width.
//
//  Programmer: Kathleen Bonnell
//  Creation:   March 21, 2001
//
//  Modifications:
//
//    Kathleen Bonnell, Sat Aug 18 18:09:04 PDT 2001
//    Use LineAttributes to ensure proper format gets sent to vtk.
//
//    Kathleen Bonnell, Mon Jun 25 09:03:29 PDT 2001
//    Set property linewidth instead of mapper line width.
//
// ****************************************************************************

void
avtMeshPlot::SetLineWidth(_LineWidth lw)
{
    mapper->SetLineWidth(LineWidth2Int(lw));
}


// ****************************************************************************
//  Method: avtMeshPlot::SetRenderOpaque
//
//  Purpose:
//    Turns on/off opaque mode.
//
//  Arguments:
//    on        True if opaque mode on.
//
//  Programmer: Kathleen Bonnell
//  Creation:   June 25, 2001
//
//  Modifications:
//
//    Kathleen Bonnell, Wed Aug 22 15:22:55 PDT 2001
//    Set appropriate renderer and property attributes depending
//    upon value of argument.
//
//    Kathleen Bonnell, Wed Sep 26 17:47:41 PDT 2001
//    Use new renderer methods for turning on/off drawing of primitives.
//
//    Kathleen Bonnell, Mon Mar 24 17:48:27 PST 2003
//    Don't use wireframe mode if not appropriate.
//
//    Kathleen Bonnell, Wed Aug 27 15:45:45 PDT 2003
//    Don't use opaque mode if not appropriate.
//
//    Kathleen Bonnell, Thu Sep  4 11:15:30 PDT 2003
//    Modified to support tri-modal opaque mode.
//
// ****************************************************************************

void
avtMeshPlot::SetRenderOpaque()
{
    mapper->SetSurfaceVisibility(ShouldRenderOpaque());
}


// ****************************************************************************
//  Method: avtMeshPlot::GetMapper
//
//  Purpose:
//      Gets the var mapper as its base class (avtMapper) for our base
//      class (avtPlot).
//
//  Returns:    The mapper for this plot.
//
//  Programmer: Kathleen Bonnell
//  Creation:   March 21, 2001
//
//  Modifications:
//    Kathleen Bonnell, Tue Nov  2 10:41:33 PST 2004
//    Return glyphMapper when mesh type is point mesh.
//
//    Kathleen Bonnell, Wed Nov  3 16:51:24 PST 2004
//    Changed test from PointMesh to topologicalDimension == 0.
//
//    Kathleen Biagas, Wed Jun 10 13:00:59 PDT 2020
//    Remove glyphMapper.
//
// ****************************************************************************

avtMapperBase *
avtMeshPlot::GetMapper(void)
{
    return mapper;
}


// ****************************************************************************
//  Method: avtMeshPlot::NeedZBufferToCompositeEvenIn2D
//
//  Purpose:
//      Tells the compositer that it needs zbuffer info to composite correctly,
//      in the case that the mesh plot is bleeding over the domain boundary,
//      which means it can spill into other processor's portion of image
//      space.
//
//  Programmer: Hank Childs
//  Creation:   August 13, 2008
//
// ****************************************************************************

bool
avtMeshPlot::NeedZBufferToCompositeEvenIn2D(void)
{
    if (atts.GetLineWidth() > 0)
        return true;
    if (atts.GetPointSizePixels() > 0)
        return true;

    return false;
}


// ****************************************************************************
//  Method: avtMeshPlot::ApplyOperators
//
//  Purpose:
//    Performs the implied operators for a mesh plot.
//
//  Arguments:
//    input     The input data object.
//
//  Returns:    The data object after the mesh plot applies (same data object).
//
//  Programmer: Kathleen Bonnell
//  Creation:   March  21, 2001
//
//  Modifications:
//    Kathleen Bonnell, Tue Mar 27 14:38:23 PST 2001
//    Set the topological dimension to 1.
//
//    Hank Childs, Fri Jun 15 09:22:37 PDT 2001
//    Use more general data objects.
//
//    Kathleen Bonnell, Thu Jun 21 09:03:29 PDT 2001
//    Added filter.
//
//    Hank Childs, Sun Jun 23 21:09:56 PDT 2002
//    Add the point to glyph filter if needed.
//
//    Jeremy Meredith, Mon Jul  8 18:38:04 PDT 2002
//    Added facelist filter for all non-zero-dimensional data.
//    Set the flag to create the 3D cell number array.
//
//    Hank Childs, Fri Jul 19 08:41:39 PDT 2002
//    Opted to use the ghost zone and facelist filter instead.
//
//    Kathleen Bonnell, Tue Oct 22 08:41:29 PDT 2002
//    Moved entire method to ApplyRenderingTransformation, so that mesh
//    plots can be query-able.  (Output of this method is the query input).
//
// ****************************************************************************

avtDataObject_p
avtMeshPlot::ApplyOperators(avtDataObject_p input)
{
    return input;
}


// ****************************************************************************
//  Method: avtMeshPlot::ApplyRenderingTransformation
//
//  Purpose:
//    Performs the rendering transformation for a mesh plot.
//
//  Arguments:
//    input     The input data object.
//
//  Returns:    The data object after the mesh plot applies (same data object).
//
//  Programmer: Kathleen Bonnell
//  Creation:   October 22, 2002
//
//  Modifications:
//    Jeremy Meredith, Tue Dec 10 10:07:34 PST 2002
//    Added smooth poly data filter.
//
//    Jeremy Meredith, Fri Dec 20 11:36:03 PST 2002
//    Added scaling of point variables by a scalar field.
//
//    Hank Childs, Thu Aug 21 23:07:47 PDT 2003
//    Added support for different types of glyphs.
//
//    Kathleen Bonnell, Thu Feb  5 11:06:01 PST 2004
//    Don't use facelist filter if user wants to see internal zones.
//
//    Kathleen Bonnell, Tue Nov  2 10:41:33 PST 2004
//    Remove glyphPoints filter, glyphing now done by avtPointGlyphMapper.
//
//    Jeremy Meredith, Tue Oct 14 15:49:15 EDT 2008
//    Set the gz/fl filter must-create-polydata flag appropriately.  In this
//    case, it only needs to be set if we're going to attempt to smooth
//    the geometry before applying the mesh filter.
//
//    Kathleen Biagas, Wed Jun 10 13:00:59 PDT 2020
//    Add vertexExtractor.
//
// ****************************************************************************

avtDataObject_p
avtMeshPlot::ApplyRenderingTransformation(avtDataObject_p input)
{
    avtDataObject_p dob = input;

    int topoDim = dob->GetInfo().GetAttributes().GetTopologicalDimension();

    if (topoDim > 0 && atts.GetPointType() != Point)
    {
        // vertexExtractor will pull all vertex cells into a separate dataset
        // for rendering via vtkPointGlyphMapper.
        if (vertexExtractor == nullptr)
        {
            vertexExtractor = new avtVertexExtractor();
        }
        vertexExtractor->SetInput(dob);
        vertexExtractor->SetLabelPrefix("mesh");
        vertexExtractor->SetConvertAllPoints(false);
        vertexExtractor->SetKeepNonVertex(true);
        vertexExtractor->SetPointGlyphAtts((PointGlyphAttributes*)(atts.CreateCompatible("PointGlyph")));
        dob = vertexExtractor->GetOutput();
    }

    if (topoDim > 0)
    {
        // Turn off facelist filter if user wants to see internal zones in 3d.
        if (atts.GetShowInternal() &&
            dob->GetInfo().GetAttributes().GetSpatialDimension()== 3)
            ghostAndFaceFilter->SetUseFaceFilter(false);
        else
            ghostAndFaceFilter->SetUseFaceFilter(true);
        ghostAndFaceFilter->SetCreate3DCellNumbers(true);
        ghostAndFaceFilter->SetInput(dob);
        ghostAndFaceFilter->SetMustCreatePolyData(atts.GetSmoothingLevel()>0);
        dob = ghostAndFaceFilter->GetOutput();
    }

    // Do smoothing if required
    if (atts.GetSmoothingLevel() > 0)
    {
        smooth->SetSmoothingLevel(atts.GetSmoothingLevel());
        smooth->SetInput(dob);
        dob = smooth->GetOutput();
    }

    if (filter != NULL)
    {
        delete filter;
    }
    filter = new avtMeshFilter(atts);
    filter->SetInput(dob);

    return filter->GetOutput();
}


// ****************************************************************************
//  Method: avtMeshPlot::CustomizeBehavior
//
//  Purpose:
//      Customizes the behavior of the output.
//
//  Programmer: Kathleen Bonnell
//  Creation:   March 21, 2001
//
//  Modifications:
//
//    Jeremy Meredith, Tue Jun  5 20:45:02 PDT 2001
//    Allow storage of attributes as a class member.
//
//    Kathleen Bonnell, Wed Aug 22 15:22:55 PDT 2001
//    Set renderer's property.
//
//    Kathleen Bonnell, Wed Sep  5 17:16:17 PDT 2001
//    Added call to SetOpaqueColor.
//
//    Eric Brugger, Fri Sep  7 15:19:03 PDT 2001
//    I moved the calls to SetMeshColor, SetOpaqueColor and SetLegend from
//    here to SetAtts, since that is the appropriate place for them.
//
//    Eric Brugger, Wed Jul 16 10:57:44 PDT 2003
//    Modified to work with the new way legends are managed.
//
//    Kathleen Bonnell, Mon Sep 29 13:07:50 PDT 2003
//    Set AntialiasedRenderOrder.
//
//    Brad Whitlock, Thu Jul 21 15:27:40 PST 2005
//    Added SetPointGlyphSize.
//
//    Jeremy Meredith, Fri Feb 20 17:26:05 EST 2009
//    Added per-plot alpha support.
//
// ****************************************************************************

void
avtMeshPlot::CustomizeBehavior(void)
{
    SetPointGlyphSize();

    behavior->SetLegend(varLegendRefPtr);
    behavior->SetShiftFactor(0.5);
    behavior->SetRenderOrder((atts.GetOpacity() < 1.0) ?
                             ABSOLUTELY_LAST : DOES_NOT_MATTER);
    behavior->SetAntialiasedRenderOrder(ABSOLUTELY_LAST);
}


// ****************************************************************************
//  Method: avtMeshPlot::CustomizeMapper
//
//  Purpose:
//      Lets the mapper know if we the data we are plotting is only appropriate
//      as opaque.
//
//  Programmer: Hank Childs
//  Creation:   June 23, 2002
//
//  Modifications:
//    Kathleen Bonnell, Mon Mar 24 17:48:27 PST 2003
//    Set internal flag regarding appropriateness of wireframe rendering.
//
//    Kathleen Bonnell, Thu Sep  4 11:15:30 PDT 2003
//    SetRenderOpaque no longer requires an argument.
//
// ****************************************************************************

void
avtMeshPlot::CustomizeMapper(avtDataObjectInformation &info)
{
    if (info.GetValidity().GetWireframeRenderingIsInappropriate() &&
        atts.GetOpaqueMode() == MeshAttributes::Auto)
    {
        wireframeRenderingIsInappropriate = true;
        SetRenderOpaque();

        //
        // This means that we want the opaque mesh to be the same color as
        // the wireframe.
        //
        SetOpaqueColor(atts.GetMeshColor().GetColor(), true);
    }
    else
    {
        wireframeRenderingIsInappropriate = false;
    }
}


// ****************************************************************************
//  Method: avtMeshPlot::TargetTopologicalDimension
//
//  Purpose:
//      Determines what the target topological dimension should be (1 for mesh
//      lines, 2 for opaque mesh).
//
//  Returns:    The target topological dimension for the mesh plot.
//
//  Programmer: Hank Childs
//  Creation:   July 24, 2001
//
//  Modifications:
//    Kathleen Bonnell, Thu Sep  4 11:15:30 PDT 2003
//    Changed logic to support tri-modal opaque mode.
//
// ****************************************************************************

int
avtMeshPlot::TargetTopologicalDimension(void)
{
    return (ShouldRenderOpaque() ? 2 : 1);
}


// ****************************************************************************
//  Method: avtMeshPlot::SetBackgroundColor
//
//  Purpose:
//    Sets the background color.
//
//  Returns:    True if using this color will require the plot to be redrawn.
//
//  Programmer: Kathleen Bonnell
//  Creation:   September 26, 2001
//
//  Modifications:
//    Kathleen Bonnell, Mon Mar 24 17:48:27 PST 2003
//    Call SetOpaqueColor instead of setting property's color directly.
//
//    Kathleen Bonnell, Thu Sep  4 11:35:18 PDT 2003
//    Call ShouldRenderOpaque.
//
// ****************************************************************************

bool
avtMeshPlot::SetBackgroundColor(const double *bg)
{
    bool retVal = false;

    if (atts.GetOpaqueColorSource() == MeshAttributes::Background && ShouldRenderOpaque())
    {
       if (bgColor[0] != bg[0] || bgColor[1] != bg[1] || bgColor[2] != bg[2])
       {
           retVal = true;
       }
       SetOpaqueColor(bg);
    }
    bgColor[0] = bg[0];
    bgColor[1] = bg[1];
    bgColor[2] = bg[2];

    return retVal;
}


// ****************************************************************************
//  Method: avtMeshPlot::SetForegroundColor
//
//  Purpose:
//    Sets the foreground color.
//
//  Returns:    True if using this color will require the plot to be redrawn.
//
//  Programmer: Kathleen Bonnell
//  Creation:   September 26, 2001
//
//  Modifications:
//    Kathleen Bonnell, Mon Mar 24 17:48:27 PST 2003
//    Call SetMeshColor instead of setting property's edge color directly.
//
// ****************************************************************************

bool
avtMeshPlot::SetForegroundColor(const double *fg)
{
    bool retVal = false;

    if (atts.GetMeshColorSource() == MeshAttributes::Foreground)
    {
       if (fgColor[0] != fg[0] || fgColor[1] != fg[1] || fgColor[2] != fg[2])
       {
           retVal = true;
       }
       SetMeshColor(fg);
    }
    fgColor[0] = fg[0];
    fgColor[1] = fg[1];
    fgColor[2] = fg[2];

    return retVal;
}

// ****************************************************************************
//  Method:  avtMeshPlot::Equivalent
//
//  Purpose:
//    Returns true if changes will not require recalculation.
//
//  Arguments:
//    a          the atts to compare
//
//  Programmer:  Jeremy Meredith
//  Creation:    November  7, 2001
//
//  Modification:
//    Kathleen Bonnell, Thu Feb  5 13:15:08 PST 2004
//    Added spatialDim in call to atts.ChangesRequireRecalculation.
//
// ****************************************************************************

bool
avtMeshPlot::Equivalent(const AttributeGroup *a)
{
    return !(atts.ChangesRequireRecalculation(*(const MeshAttributes*)a,
             behavior->GetInfo().GetAttributes().GetSpatialDimension()));
}


// ****************************************************************************
//  Method: avtMeshPlot::ReleaseData
//
//  Purpose:
//      Release the problem sized data associated with this plot.
//
//  Programmer: Hank Childs
//  Creation:   September 12, 2002
//
//  Modifications:
//
//    Kathleen Bonnell, Tue Nov  2 10:58:26 PST 2004
//    Removed glyphPoints.
//
//    Hank Childs, Thu Jan  8 11:18:13 CST 2009
//    Release data from the smooth filter.
//
//    Kathleen Biagas, Wed Jun 10 13:00:59 PDT 2020
//    Add vertexExtractor.
//
// ****************************************************************************

void
avtMeshPlot::ReleaseData(void)
{
    avtPlot::ReleaseData();

    if (filter != NULL)
    {
        filter->ReleaseData();
    }
    if (ghostAndFaceFilter != NULL)
    {
        ghostAndFaceFilter->ReleaseData();
    }
    if (smooth != NULL)
    {
        smooth->ReleaseData();
    }
    if (vertexExtractor != nullptr)
    {
        vertexExtractor->ReleaseData();
    }
}


// ****************************************************************************
//  Method: avtMeshPlot::SetOpaqueMeshIsAppropriate
//
//  Purpose:
//    Sets the flag specifying whether or not opaque Mode is appropriate.
//
//  Returns:
//    The changed MeshAtts, or NULL if atts did not change.
//
//  Arguments:
//    val  The new mode.
//
//  Programmer: Kathleen Bonnell
//  Creation:   August 27, 2003
//
//  Modifications:
//    Kathleen Bonnell, Thu Sep  4 11:35:18 PDT 2003
//    Only update the value opaqueMode is Auto.
//
//    Kathleen Bonnell, Tue Aug 24 16:12:03 PDT 2004
//    Exclude point mesh from auto-opaque mode.
//
//    Kathleen Bonnell, Tue Nov  2 10:41:33 PST 2004
//    Removed avtMeshType arg, now available as data member of avtPlot.
//
//    Kathleen Bonnell, Wed Nov  3 14:44:17 PST 2004
//    Removed meshType, now use topologicalDim.
//
// ****************************************************************************

const AttributeSubject *
avtMeshPlot::SetOpaqueMeshIsAppropriate(bool val)
{
    if ((atts.GetOpaqueMode() == MeshAttributes::Auto) &&
       (val != atts.GetOpaqueMeshIsAppropriate() && topologicalDim != 0))
    {
        atts.SetOpaqueMeshIsAppropriate(val);
        return &atts;
    }
    return NULL;
}


// ****************************************************************************
//  Method: avtMeshPlot::ShouldlRenderOpaque
//
//  Purpose:
//    Determines whether the opaque surface should be rendered.
//
//  Returns:
//    True if opaque surface should be rendered, false otherwise.
//
//  Programmer: Kathleen Bonnell
//  Creation:   September 4, 2003
//
//  Modifications:
//    Kathleen Bonnell, Thu Feb  5 11:07:05 PST 2004
//    If Auto mode, only show opaque if ShowInternal is OFF.
//
//    Kathleen Biagas, Tue Jul  8 11:19:38 PDT 2014
//    Made Auto also be the default (its the default in the atts), so that
//    shouldBeOn is guaranteed to be set.
//
// ****************************************************************************

bool
avtMeshPlot::ShouldRenderOpaque(void)
{
    bool shouldBeOn = false;

    switch (atts.GetOpaqueMode())
    {
        case MeshAttributes::On:
            // Always on
            shouldBeOn = true;
            break;
        case MeshAttributes::Off:
            // On if wireframeRendering is Inappropriate.
            shouldBeOn = wireframeRenderingIsInappropriate;
            break;
        case MeshAttributes::Auto:
        default:
            // Only on if appropriate
            shouldBeOn = atts.GetOpaqueMeshIsAppropriate() &&
                         !atts.GetShowInternal();
            break;
    }
    return shouldBeOn;
}

// ****************************************************************************
// Method: avtMeshPlot::SetPointGlyphSize
//
// Purpose:
//   Sets the point glyph size into the mapper.
//
// Programmer: Brad Whitlock
// Creation:   Thu Jul 21 15:24:25 PST 2005
//
// Modifications:
//   Brad Whitlock, Thu Aug 25 10:13:40 PDT 2005
//   Added sphere points.
//
//   Kathleen Biagas, Wed Apr  3 16:09:31 PDT 2019
//   Send the pointsize to the regular mapper as well.
//
//   Kathleen Biagas, Wed Jun 10 13:00:59 PDT 2020
//   Remove glyphMapper.
//
// ****************************************************************************

void
avtMeshPlot::SetPointGlyphSize()
{
    mapper->SetPointSize(atts.GetPointSizePixels());
}


// ****************************************************************************
//  Method: avtMeshPlot::GetExtraInfoForPick
//
//  Purpose:
//    Override default settings for extraPickinfo.
//
//  Programmer: Kathleen Biagas
//  Creation:   February 29, 2012
//
// ****************************************************************************

const MapNode &
avtMeshPlot::GetExtraInfoForPick()
{
    extraPickInfo["canGlyphPickOnEngine"] = false;

    return extraPickInfo;
}


// ****************************************************************************
//  Method: avtMeshPlot::PlotHasBeenGlyphed
//
//  Purpose:
//    Return whether or not the plot has had point glyphs applied.
//
//  Programmer: Kathleen Biagas
//  Creation:   October 31, 2019
//
// ****************************************************************************

bool
avtMeshPlot::PlotHasBeenGlyphed()
{
    return (atts.GetPointType() != Point && atts.GetPointType() != Sphere);
}

