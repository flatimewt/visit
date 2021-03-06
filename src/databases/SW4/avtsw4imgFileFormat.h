// Copyright (c) Lawrence Livermore National Security, LLC and other VisIt
// Project developers.  See the top-level LICENSE file for dates and other
// details.  No copyright assignment is required to contribute to VisIt.

// ************************************************************************* //
//                          avtsw4imgFileFormat.h                            //
// ************************************************************************* //

#ifndef AVT_sw4img_FILE_FORMAT_H
#define AVT_sw4img_FILE_FORMAT_H

#include <avtSTMDFileFormat.h>

#include <vector>
#include <string>


// ****************************************************************************
//  Class: avtsw4imgFileFormat
//
//  Purpose:
//      Reads in sw4img files as a plugin to VisIt.
//
//  Programmer: petersson1 -- generated by xml2avt
//  Creation:   Tue Nov 11 12:42:37 PDT 2014
//
// ****************************************************************************

class avtsw4imgFileFormat : public avtSTMDFileFormat
{
  public:
                       avtsw4imgFileFormat(const char *);
    virtual           ~avtsw4imgFileFormat() {;};

    virtual const char    *GetType(void)   { return "sw4img"; };
    virtual void           FreeUpResources(void); 

    virtual vtkDataSet    *GetMesh(int, const char *);
    virtual vtkDataArray  *GetVar(int, const char *);
    virtual vtkDataArray  *GetVectorVar(int, const char *);

  protected:
    virtual void           PopulateDatabaseMetaData(avtDatabaseMetaData *);

    // imagevolume data
    void Initialize();
    bool m_initialized;
    bool m_data_stored;
    bool m_volimage;
    bool m_CartGrid;
    double m_time;
    std::vector<float*> m_dataptr;
    std::vector<float*> m_gridptr;
    std::string m_filename;
    int m_prec;
    int m_nblocks; // total number of data patches on file (the grid data is not considered a separate patch)
    int m_gridOffset; // file offset to grid z-coords (if m_grdinfo == 1)
    
    int m_plane;
    double m_plane_coord;
    int m_mode_number;
    int m_grdinfo;
    std::string m_file_creation_time;
    
    std::vector<double> m_gridsize;
    std::string m_mode;
    std::vector<double> m_xmin;
    std::vector<double> m_ymin;
    std::vector<double> m_zmin;
    std::vector<double> m_z0;
    std::vector<int> m_ni;
    std::vector<int> m_nj;
    std::vector<int> m_nk;
    std::vector<off_t> m_offset;
};


#endif
