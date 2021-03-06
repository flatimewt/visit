// Copyright (c) Lawrence Livermore National Security, LLC and other VisIt
// Project developers.  See the top-level LICENSE file for dates and other
// details.  No copyright assignment is required to contribute to VisIt.

// ************************************************************************* //
//                             avtSiloOptions.h                              //
// ************************************************************************* //

#ifndef AVT_Silo_OPTIONS_H
#define AVT_Silo_OPTIONS_H

class DBOptionsAttributes;

#include <string>

namespace SiloDBOptions
{
    // Read options
    const char *const SILO_RDOPT_FORCE_SINGLE = "Force Single";
    const char *const SILO_RDOPT_SEARCH_ANNOTINT = "Search For ANNOTATION_INT (!!Slow!!)";
    const char *const SILO_RDOPT_IGNORE_SEXTS = "Ignore spatial extents";
    const char *const SILO_RDOPT_IGNORE_DEXTS = "Ignore data extents";

    // Old (obsolete) read option names. Note case difference between these strings
    // and the current options. This is to maintain distinction between old and
    // new interfaces for read options for extents.
    const char *const SILO_RDOPT_IGNORE_SEXTS2 = "Ignore Spatial Extents";
    const char *const SILO_RDOPT_IGNORE_DEXTS2 = "Ignore Data Extents";

    // Write options
    const char *const SILO_WROPT_DRIVER = "Driver";
    const char *const SILO_WROPT_CKSUMS = "Checksums";
    const char *const SILO_WROPT_COMPRESSION = "DBSetCompression()";
}

// ****************************************************************************
//  Functions: avtSiloOptions
//
//  Purpose:
//      Creates the options for  Silo readers and/or writers.
//
//  Programmer: miller -- generated by xml2avt
//  Creation:   Thu Nov 29 14:10:56 PST 2007
//
// ****************************************************************************

DBOptionsAttributes *GetSiloReadOptions(void);
DBOptionsAttributes *GetSiloWriteOptions(void);


#endif
