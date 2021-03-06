// Copyright (c) Lawrence Livermore National Security, LLC and other VisIt
// Project developers.  See the top-level LICENSE file for dates and other
// details.  No copyright assignment is required to contribute to VisIt.

// ************************************************************************* //
//                             avtSiloOptions.C                              //
// ************************************************************************* //

#include <avtSiloOptions.h>

#include <DBOptionsAttributes.h>

#include <string>
#include <vector>

using std::string;
using std::vector;
using namespace SiloDBOptions;

// ****************************************************************************
//  Function: GetSiloReadOptions
//
//  Purpose:
//      Creates the options for Silo readers.
//
//  Important Note:
//      The code below sets up empty options.  If your format 
//      does not require read options, no modifications are 
//      necessary.
//
//  Programmer: miller -- generated by xml2avt
//  Creation:   Thu Nov 29 14:10:56 PST 2007
//
//    Mark C. Miller, Wed Dec 24 01:30:35 PST 2008
//    Added option for ANNOTATION_INT nodelists. Ordinarily, we'd just want
//    the database to tell us when these exist. However, there is no way to
//    do that without also taking a big performance hit of having to open all
//    the subfiles in a multi-file Silo file. So, we make it the user's 
//    responsibility to turn on this functionality via a read option.
//
//    Mark C. Miller, Wed Mar  4 08:56:57 PST 2009
//    Made controls for ignoring extents tri-state.
//
//    Mark C. Miller, Mon Mar 16 23:31:58 PDT 2009
//    Added logic for obsolete options.
//    Added const names of options to SiloDBOptions namespace
// ****************************************************************************

DBOptionsAttributes *
GetSiloReadOptions(void)
{
    DBOptionsAttributes *rv = new DBOptionsAttributes;
    vector<string> ignoreOpts;
    ignoreOpts.push_back("Always"); // 0
    ignoreOpts.push_back("Auto");   // 1
    ignoreOpts.push_back("Never");  // 2
    ignoreOpts.push_back("Undef");  // 3
    rv->SetEnum(SILO_RDOPT_IGNORE_SEXTS, 3); // Undef 
    rv->SetEnumStrings(SILO_RDOPT_IGNORE_SEXTS, ignoreOpts);
    rv->SetEnum(SILO_RDOPT_IGNORE_DEXTS, 3); // Undef 
    rv->SetEnumStrings(SILO_RDOPT_IGNORE_DEXTS, ignoreOpts);
    rv->SetBool(SILO_RDOPT_FORCE_SINGLE, false);
    rv->SetBool(SILO_RDOPT_SEARCH_ANNOTINT, false);

    // Specify obsolete options and their default values
    rv->SetObsolete(SILO_RDOPT_IGNORE_SEXTS2);
    rv->SetObsolete(SILO_RDOPT_IGNORE_DEXTS2);

    return rv;
}


// ****************************************************************************
//  Function: GetSiloWriteOptions
//
//  Purpose:
//      Creates the options for Silo writers.
//
//  Important Note:
//      The code below sets up empty options.  If your format 
//      does not require write options, no modifications are 
//      necessary.
//
//  Programmer: miller -- generated by xml2avt
//  Creation:   Thu Nov 29 14:10:56 PST 2007
//
//    Mark C. Miller, Thu Jul 31 18:06:08 PDT 2008
//    Added option to write all data to a single file 
//
//    Mark C. Miller, Tue Mar 17 18:13:22 PDT 2009
//    Use const char * option name symbols defined in avtSiloOptions.h
//
//    Mark C. Miller, Fri May  8 17:09:39 PDT 2009
//    Added compression/checksum options.
//
//    Mark C. Miller, Wed Apr 10 11:43:29 PDT 2019
//    Add help string.
// ****************************************************************************

DBOptionsAttributes *
GetSiloWriteOptions(void)
{
    DBOptionsAttributes *rv = new DBOptionsAttributes;

    //
    // Driver type options
    //
    rv->SetEnum(SILO_WROPT_DRIVER, 0);
    vector<string> drivers;
    drivers.push_back("PDB");  // 0
    drivers.push_back("HDF5"); // 1
    rv->SetEnumStrings(SILO_WROPT_DRIVER, drivers);
    rv->SetBool(SILO_WROPT_CKSUMS, false);
    rv->SetString(SILO_WROPT_COMPRESSION, "");

    char helpStr[512];
    snprintf(helpStr, sizeof(helpStr),
        "<p><b>%s</b>:"
        "<ul>"
        "<li>PDB: Silo library will create a PDB file.</li>"
        "<li>HDF5: Silo library will create an HDF5 file.</li>"
        "</ul>"
        "<p><b>%s</b>:"
        "<ul>"
        "<li>Valid only for HDF5 files.</li>"
        "<li>Enables HDF5's Fletcher32 checksum filter.</li>"
        "</ul>"
        "<p><b>%s</b>:"
        "Enter any compression string that would be valid to pass to Silo's"
        "<a href=\"https://wci.llnl.gov/content/assets/docs/simulation/computer-codes/silo/LLNL-SM-654357.pdf#page=49\">"
        "DBSetCompression()</a> method.",
        SILO_WROPT_DRIVER,
        SILO_WROPT_CKSUMS,
        SILO_WROPT_COMPRESSION);
    rv->SetHelp(helpStr);

    return rv;
}
