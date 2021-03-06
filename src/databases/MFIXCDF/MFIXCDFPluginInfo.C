// Copyright (c) Lawrence Livermore National Security, LLC and other VisIt
// Project developers.  See the top-level LICENSE file for dates and other
// details.  No copyright assignment is required to contribute to VisIt.

// ****************************************************************************
//  File: MFIXCDFPluginInfo.C
// ****************************************************************************

#include <MFIXCDFPluginInfo.h>

#include <visit-config.h>
VISIT_PLUGIN_VERSION(MFIXCDF,DBP_EXPORT)

VISIT_DATABASE_PLUGIN_ENTRY(MFIXCDF,General)

// ****************************************************************************
//  Method: MFIXCDFGeneralPluginInfo::GetName
//
//  Purpose:
//    Return the name of the database plugin.
//
//  Returns:    A pointer to the name of the database plugin.
//
//  Programmer: generated by xml2info
//  Creation:   omitted
//
// ****************************************************************************

const char *
MFIXCDFGeneralPluginInfo::GetName() const
{
    return "MFIXCDF";
}

// ****************************************************************************
//  Method: MFIXCDFGeneralPluginInfo::GetVersion
//
//  Purpose:
//    Return the version of the database plugin.
//
//  Returns:    A pointer to the version of the database plugin.
//
//  Programmer: generated by xml2info
//  Creation:   omitted
//
// ****************************************************************************

const char *
MFIXCDFGeneralPluginInfo::GetVersion() const
{
    return "1.0";
}

// ****************************************************************************
//  Method: MFIXCDFGeneralPluginInfo::GetID
//
//  Purpose:
//    Return the id of the database plugin.
//
//  Returns:    A pointer to the id of the database plugin.
//
//  Programmer: generated by xml2info
//  Creation:   omitted
//
// ****************************************************************************

const char *
MFIXCDFGeneralPluginInfo::GetID() const
{
    return "MFIXCDF_1.0";
}
// ****************************************************************************
//  Method: MFIXCDFGeneralPluginInfo::EnabledByDefault
//
//  Purpose:
//    Return true if this plugin should be enabled by default; false otherwise.
//
//  Returns:    true/false
//
//  Programmer: generated by xml2info
//  Creation:   omitted
//
// ****************************************************************************

bool
MFIXCDFGeneralPluginInfo::EnabledByDefault() const
{
    return true;
}
// ****************************************************************************
//  Method: MFIXCDFGeneralPluginInfo::HasWriter
//
//  Purpose:
//    Return true if this plugin has a database writer.
//
//  Returns:    true/false
//
//  Programmer: generated by xml2info
//  Creation:   omitted
//
// ****************************************************************************

bool
MFIXCDFGeneralPluginInfo::HasWriter() const
{
    return false;
}
// ****************************************************************************
//  Method:  MFIXCDFGeneralPluginInfo::GetDefaultFilePatterns
//
//  Purpose:
//    Returns the default patterns for a MFIXCDF database.
//
//  Programmer:  generated by xml2info
//  Creation:    omitted
//
// ****************************************************************************
std::vector<std::string>
MFIXCDFGeneralPluginInfo::GetDefaultFilePatterns() const
{
    std::vector<std::string> defaultPatterns;
    defaultPatterns.push_back(".nc");

    return defaultPatterns;
}

// ****************************************************************************
//  Method:  MFIXCDFGeneralPluginInfo::AreDefaultFilePatternsStrict
//
//  Purpose:
//    Returns if the file patterns for a MFIXCDF database are
//    intended to be interpreted strictly by default.
//
//  Programmer:  generated by xml2info
//  Creation:    omitted
//
// ****************************************************************************
bool
MFIXCDFGeneralPluginInfo::AreDefaultFilePatternsStrict() const
{
    return false;
}

// ****************************************************************************
//  Method:  MFIXCDFGeneralPluginInfo::OpensWholeDirectory
//
//  Purpose:
//    Returns if the MFIXCDF plugin opens a whole directory name
//    instead of a single file.
//
//  Programmer:  generated by xml2info
//  Creation:    omitted
//
// ****************************************************************************
bool
MFIXCDFGeneralPluginInfo::OpensWholeDirectory() const
{
    return false;
}
