// Copyright (c) Lawrence Livermore National Security, LLC and other VisIt
// Project developers.  See the top-level LICENSE file for dates and other
// details.  No copyright assignment is required to contribute to VisIt.

#include <GetSILRPC.h>
#include <GetMetaDataException.h>
#include <DebugStream.h>
#include <string>
using std::string;

// ****************************************************************************
// Method: GetSILRPC::GetSILRPC
//
// Purpose: 
//   Constructor for the GetSILRPC class.
//
// Programmer: Hank Childs
// Creation:   March 29, 2001
//
// Modifications:
//
//   Mark C. Miller, Wed Aug 22 20:16:59 PDT 2007
//   Added treatAllDBsAsTimeVarying
// ****************************************************************************

GetSILRPC::GetSILRPC() : BlockingRPC("sib",&sil)
{
    timeState = 0;
    treatAllDBsAsTimeVarying = false;
}

// ****************************************************************************
// Method: GetSILRPC::~GetSILRPC
//
// Purpose: 
//   Destructor for the GetSILRPC class.
//
// Programmer: Hank Childs
// Creation:   March 29, 2001
//
// Modifications:
//
// ****************************************************************************

GetSILRPC::~GetSILRPC()
{
}

// ****************************************************************************
// Method: GetSILRPC::TypeName
//
// Purpose: 
//   Returns the RPC name,
//
// Programmer: Brad Whitlock
// Creation:   Tue May 13 15:33:12 PST 2003
//
// Modifications:
//   
// ****************************************************************************

const string
GetSILRPC::TypeName() const
{
    return "GetSILRPC";
}

// ****************************************************************************
//  Method: GetSILRPC::operator()
//
//  Purpose: 
//    This is the () operator for the GetSILRPC class. This method
//    makes the objects of this class function objects. This method
//    executes the RPC to get the sil from a file and returns
//    a pointer to it.
//
//  Programmer: Hank Childs
//  Creation:   March 29, 2001
//
//  Modifications:
//    Brad Whitlock, Thu Feb 7 11:12:11 PDT 2002
//    Added the error message to the new exception.
//
//    Brad Whitlock, Tue May 13 15:33:32 PST 2003
//    Added timeState.
//
//    Mark C. Miller, Wed Aug 22 20:16:59 PDT 2007
//    Added treatAllDBsAsTimeVarying
// ****************************************************************************

const SILAttributes *
GetSILRPC::operator()(const string &f, int ts, bool treatAllDBsAsTimeVarying)
{
    debug3 << "Executing GetSIL RPC on file " << f.c_str()
           << ", timestate = " << ts << endl;

    SetFile(f);
    SetTimeState(ts);
    SetTreatAllDBsAsTimeVarying(treatAllDBsAsTimeVarying);

    // Try to execute the RPC.
    Execute();

    // If the RPC returned an error, throw an exception.
    if(GetReply()->GetStatus() == error)
    {
        EXCEPTION1(GetMetaDataException, GetReply()->Message());
    }

    return &sil;
}

// ****************************************************************************
// Method: GetSILRPC::SelectAll
//
// Purpose: 
//   This method selects all of the components in the GetSILRPC
//   before the RPC is executed. This is so RPC function parameters
//   would be communicated.
//
// Programmer: Hank Childs
// Creation:   March 29, 2001
//
// Modifications:
//   Brad Whitlock, Tue May 13 15:34:13 PST 2003
//   Added timeState.
//
//   Mark C. Miller, Wed Aug 22 20:16:59 PDT 2007
//   Added treatAllDBsAsTimeVarying
// ****************************************************************************

void
GetSILRPC::SelectAll()
{
    Select(0, (void*)&file);
    Select(1, (void*)&timeState);
    Select(2, (void*)&treatAllDBsAsTimeVarying);
}

// ****************************************************************************
// Method: GetSILRPC::SetFile
//
// Purpose: 
//   This sets the file name from which to get the SIL.
//
// Programmer: Hank Childs
// Creation:   March 29, 2001
//
// Modifications:
//   
// ****************************************************************************

void
GetSILRPC::SetFile(const std::string &f)
{
    file = f;
    Select(0, (void*)&file);
}

// ****************************************************************************
// Method: GetSILRPC::SetTimeState
//
// Purpose: 
//   This sets the time state for which to get the SIL.
//
// Programmer: Hank Childs
// Creation:   March 29, 2001
//
// Modifications:
//   
// ****************************************************************************

void
GetSILRPC::SetTimeState(int ts)
{
    timeState = ts;
    Select(1, (void*)&timeState);
}

// ****************************************************************************
// Method: GetSILRPC::SetTreatAllDBsAsTimeVarying
//
// Programmer: Mark C. Miller 
// Creation:   August 22, 2007 
//   
// ****************************************************************************
void
GetSILRPC::SetTreatAllDBsAsTimeVarying(bool val)
{
    treatAllDBsAsTimeVarying = val;
    Select(2, (void*)&treatAllDBsAsTimeVarying);
}

// ****************************************************************************
// Method: GetSILRPC::GetFile
//
// Purpose: 
//   This gets the file name from which to get the metadata.
//
// Programmer: Hank Childs
// Creation:   March 29, 2001
//
// Modifications:
//   
// ****************************************************************************

string
GetSILRPC::GetFile() const
{
    return file;
}

// ****************************************************************************
// Method: GetSILRPC::GetTimeState
//
// Purpose: 
//   Gets the timestate.
//
// Programmer: Brad Whitlock
// Creation:   Tue May 13 15:35:39 PST 2003
//
// Modifications:
//   
// ****************************************************************************

int
GetSILRPC::GetTimeState() const
{
    return timeState;
}

// ****************************************************************************
// Method: GetSILRPC::GetTreatAllDBsAsTimeVarying
//
// Programmer: Mark C. Miller 
// Creation:   August 22, 2007 
//   
// ****************************************************************************
bool
GetSILRPC::GetTreatAllDBsAsTimeVarying() const
{
    return treatAllDBsAsTimeVarying;
}
