// Copyright (c) Lawrence Livermore National Security, LLC and other VisIt
// Project developers.  See the top-level LICENSE file for dates and other
// details.  No copyright assignment is required to contribute to VisIt.

#include <PySpreadsheetAttributes.h>
#include <ObserverToCallback.h>
#include <stdio.h>
#include <Py2and3Support.h>
#include <ColorAttribute.h>

// ****************************************************************************
// Module: PySpreadsheetAttributes
//
// Purpose:
//   Contains the attributes for the visual spreadsheet.
//
// Note:       Autogenerated by xml2python. Do not modify by hand!
//
// Programmer: xml2python
// Creation:   omitted
//
// ****************************************************************************

//
// This struct contains the Python type information and a SpreadsheetAttributes.
//
struct SpreadsheetAttributesObject
{
    PyObject_HEAD
    SpreadsheetAttributes *data;
    bool        owns;
    PyObject   *parent;
};

//
// Internal prototypes
//
static PyObject *NewSpreadsheetAttributes(int);
std::string
PySpreadsheetAttributes_ToString(const SpreadsheetAttributes *atts, const char *prefix)
{
    std::string str;
    char tmpStr[1000];

    snprintf(tmpStr, 1000, "%ssubsetName = \"%s\"\n", prefix, atts->GetSubsetName().c_str());
    str += tmpStr;
    snprintf(tmpStr, 1000, "%sformatString = \"%s\"\n", prefix, atts->GetFormatString().c_str());
    str += tmpStr;
    if(atts->GetUseColorTable())
        snprintf(tmpStr, 1000, "%suseColorTable = 1\n", prefix);
    else
        snprintf(tmpStr, 1000, "%suseColorTable = 0\n", prefix);
    str += tmpStr;
    snprintf(tmpStr, 1000, "%scolorTableName = \"%s\"\n", prefix, atts->GetColorTableName().c_str());
    str += tmpStr;
    if(atts->GetShowTracerPlane())
        snprintf(tmpStr, 1000, "%sshowTracerPlane = 1\n", prefix);
    else
        snprintf(tmpStr, 1000, "%sshowTracerPlane = 0\n", prefix);
    str += tmpStr;
    const unsigned char *tracerColor = atts->GetTracerColor().GetColor();
    snprintf(tmpStr, 1000, "%stracerColor = (%d, %d, %d, %d)\n", prefix, int(tracerColor[0]), int(tracerColor[1]), int(tracerColor[2]), int(tracerColor[3]));
    str += tmpStr;
    const char *normal_names = "X, Y, Z";
    switch (atts->GetNormal())
    {
      case SpreadsheetAttributes::X:
          snprintf(tmpStr, 1000, "%snormal = %sX  # %s\n", prefix, prefix, normal_names);
          str += tmpStr;
          break;
      case SpreadsheetAttributes::Y:
          snprintf(tmpStr, 1000, "%snormal = %sY  # %s\n", prefix, prefix, normal_names);
          str += tmpStr;
          break;
      case SpreadsheetAttributes::Z:
          snprintf(tmpStr, 1000, "%snormal = %sZ  # %s\n", prefix, prefix, normal_names);
          str += tmpStr;
          break;
      default:
          break;
    }

    snprintf(tmpStr, 1000, "%ssliceIndex = %d\n", prefix, atts->GetSliceIndex());
    str += tmpStr;
    snprintf(tmpStr, 1000, "%sspreadsheetFont = \"%s\"\n", prefix, atts->GetSpreadsheetFont().c_str());
    str += tmpStr;
    if(atts->GetShowPatchOutline())
        snprintf(tmpStr, 1000, "%sshowPatchOutline = 1\n", prefix);
    else
        snprintf(tmpStr, 1000, "%sshowPatchOutline = 0\n", prefix);
    str += tmpStr;
    if(atts->GetShowCurrentCellOutline())
        snprintf(tmpStr, 1000, "%sshowCurrentCellOutline = 1\n", prefix);
    else
        snprintf(tmpStr, 1000, "%sshowCurrentCellOutline = 0\n", prefix);
    str += tmpStr;
    snprintf(tmpStr, 1000, "%scurrentPickType = %d\n", prefix, atts->GetCurrentPickType());
    str += tmpStr;
    snprintf(tmpStr, 1000, "%scurrentPickLetter = \"%s\"\n", prefix, atts->GetCurrentPickLetter().c_str());
    str += tmpStr;
    {   const stringVector &pastPickLetters = atts->GetPastPickLetters();
        snprintf(tmpStr, 1000, "%spastPickLetters = (", prefix);
        str += tmpStr;
        for(size_t i = 0; i < pastPickLetters.size(); ++i)
        {
            snprintf(tmpStr, 1000, "\"%s\"", pastPickLetters[i].c_str());
            str += tmpStr;
            if(i < pastPickLetters.size() - 1)
            {
                snprintf(tmpStr, 1000, ", ");
                str += tmpStr;
            }
        }
        snprintf(tmpStr, 1000, ")\n");
        str += tmpStr;
    }
    return str;
}

static PyObject *
SpreadsheetAttributes_Notify(PyObject *self, PyObject *args)
{
    SpreadsheetAttributesObject *obj = (SpreadsheetAttributesObject *)self;
    obj->data->Notify();
    Py_INCREF(Py_None);
    return Py_None;
}

/*static*/ PyObject *
SpreadsheetAttributes_SetSubsetName(PyObject *self, PyObject *args)
{
    SpreadsheetAttributesObject *obj = (SpreadsheetAttributesObject *)self;

    char *str;
    if(!PyArg_ParseTuple(args, "s", &str))
        return NULL;

    // Set the subsetName in the object.
    obj->data->SetSubsetName(std::string(str));

    Py_INCREF(Py_None);
    return Py_None;
}

/*static*/ PyObject *
SpreadsheetAttributes_GetSubsetName(PyObject *self, PyObject *args)
{
    SpreadsheetAttributesObject *obj = (SpreadsheetAttributesObject *)self;
    PyObject *retval = PyString_FromString(obj->data->GetSubsetName().c_str());
    return retval;
}

/*static*/ PyObject *
SpreadsheetAttributes_SetFormatString(PyObject *self, PyObject *args)
{
    SpreadsheetAttributesObject *obj = (SpreadsheetAttributesObject *)self;

    char *str;
    if(!PyArg_ParseTuple(args, "s", &str))
        return NULL;

    // Set the formatString in the object.
    obj->data->SetFormatString(std::string(str));

    Py_INCREF(Py_None);
    return Py_None;
}

/*static*/ PyObject *
SpreadsheetAttributes_GetFormatString(PyObject *self, PyObject *args)
{
    SpreadsheetAttributesObject *obj = (SpreadsheetAttributesObject *)self;
    PyObject *retval = PyString_FromString(obj->data->GetFormatString().c_str());
    return retval;
}

/*static*/ PyObject *
SpreadsheetAttributes_SetUseColorTable(PyObject *self, PyObject *args)
{
    SpreadsheetAttributesObject *obj = (SpreadsheetAttributesObject *)self;

    int ival;
    if(!PyArg_ParseTuple(args, "i", &ival))
        return NULL;

    // Set the useColorTable in the object.
    obj->data->SetUseColorTable(ival != 0);

    Py_INCREF(Py_None);
    return Py_None;
}

/*static*/ PyObject *
SpreadsheetAttributes_GetUseColorTable(PyObject *self, PyObject *args)
{
    SpreadsheetAttributesObject *obj = (SpreadsheetAttributesObject *)self;
    PyObject *retval = PyInt_FromLong(obj->data->GetUseColorTable()?1L:0L);
    return retval;
}

/*static*/ PyObject *
SpreadsheetAttributes_SetColorTableName(PyObject *self, PyObject *args)
{
    SpreadsheetAttributesObject *obj = (SpreadsheetAttributesObject *)self;

    char *str;
    if(!PyArg_ParseTuple(args, "s", &str))
        return NULL;

    // Set the colorTableName in the object.
    obj->data->SetColorTableName(std::string(str));

    Py_INCREF(Py_None);
    return Py_None;
}

/*static*/ PyObject *
SpreadsheetAttributes_GetColorTableName(PyObject *self, PyObject *args)
{
    SpreadsheetAttributesObject *obj = (SpreadsheetAttributesObject *)self;
    PyObject *retval = PyString_FromString(obj->data->GetColorTableName().c_str());
    return retval;
}

/*static*/ PyObject *
SpreadsheetAttributes_SetShowTracerPlane(PyObject *self, PyObject *args)
{
    SpreadsheetAttributesObject *obj = (SpreadsheetAttributesObject *)self;

    int ival;
    if(!PyArg_ParseTuple(args, "i", &ival))
        return NULL;

    // Set the showTracerPlane in the object.
    obj->data->SetShowTracerPlane(ival != 0);

    Py_INCREF(Py_None);
    return Py_None;
}

/*static*/ PyObject *
SpreadsheetAttributes_GetShowTracerPlane(PyObject *self, PyObject *args)
{
    SpreadsheetAttributesObject *obj = (SpreadsheetAttributesObject *)self;
    PyObject *retval = PyInt_FromLong(obj->data->GetShowTracerPlane()?1L:0L);
    return retval;
}

/*static*/ PyObject *
SpreadsheetAttributes_SetTracerColor(PyObject *self, PyObject *args)
{
    SpreadsheetAttributesObject *obj = (SpreadsheetAttributesObject *)self;

    int c[4];
    if(!PyArg_ParseTuple(args, "iiii", &c[0], &c[1], &c[2], &c[3]))
    {
        c[3] = 255;
        if(!PyArg_ParseTuple(args, "iii", &c[0], &c[1], &c[2]))
        {
            double dr, dg, db, da;
            if(PyArg_ParseTuple(args, "dddd", &dr, &dg, &db, &da))
            {
                c[0] = int(dr);
                c[1] = int(dg);
                c[2] = int(db);
                c[3] = int(da);
            }
            else if(PyArg_ParseTuple(args, "ddd", &dr, &dg, &db))
            {
                c[0] = int(dr);
                c[1] = int(dg);
                c[2] = int(db);
                c[3] = 255;
            }
            else
            {
                PyObject *tuple = NULL;
                if(!PyArg_ParseTuple(args, "O", &tuple))
                    return NULL;

                if(!PyTuple_Check(tuple))
                    return NULL;

                // Make sure that the tuple is the right size.
                if(PyTuple_Size(tuple) < 3 || PyTuple_Size(tuple) > 4)
                    return NULL;

                // Make sure that all elements in the tuple are ints.
                for(int i = 0; i < PyTuple_Size(tuple); ++i)
                {
                    PyObject *item = PyTuple_GET_ITEM(tuple, i);
                    if(PyInt_Check(item))
                        c[i] = int(PyInt_AS_LONG(PyTuple_GET_ITEM(tuple, i)));
                    else if(PyFloat_Check(item))
                        c[i] = int(PyFloat_AS_DOUBLE(PyTuple_GET_ITEM(tuple, i)));
                    else
                        return NULL;
                }
            }
        }
        PyErr_Clear();
    }

    // Set the tracerColor in the object.
    ColorAttribute ca(c[0], c[1], c[2], c[3]);
    obj->data->SetTracerColor(ca);

    Py_INCREF(Py_None);
    return Py_None;
}

/*static*/ PyObject *
SpreadsheetAttributes_GetTracerColor(PyObject *self, PyObject *args)
{
    SpreadsheetAttributesObject *obj = (SpreadsheetAttributesObject *)self;
    // Allocate a tuple the with enough entries to hold the tracerColor.
    PyObject *retval = PyTuple_New(4);
    const unsigned char *tracerColor = obj->data->GetTracerColor().GetColor();
    PyTuple_SET_ITEM(retval, 0, PyInt_FromLong(long(tracerColor[0])));
    PyTuple_SET_ITEM(retval, 1, PyInt_FromLong(long(tracerColor[1])));
    PyTuple_SET_ITEM(retval, 2, PyInt_FromLong(long(tracerColor[2])));
    PyTuple_SET_ITEM(retval, 3, PyInt_FromLong(long(tracerColor[3])));
    return retval;
}

/*static*/ PyObject *
SpreadsheetAttributes_SetNormal(PyObject *self, PyObject *args)
{
    SpreadsheetAttributesObject *obj = (SpreadsheetAttributesObject *)self;

    int ival;
    if(!PyArg_ParseTuple(args, "i", &ival))
        return NULL;

    // Set the normal in the object.
    if(ival >= 0 && ival < 3)
        obj->data->SetNormal(SpreadsheetAttributes::NormalAxis(ival));
    else
    {
        fprintf(stderr, "An invalid normal value was given. "
                        "Valid values are in the range of [0,2]. "
                        "You can also use the following names: "
                        "X, Y, Z.");
        return NULL;
    }

    Py_INCREF(Py_None);
    return Py_None;
}

/*static*/ PyObject *
SpreadsheetAttributes_GetNormal(PyObject *self, PyObject *args)
{
    SpreadsheetAttributesObject *obj = (SpreadsheetAttributesObject *)self;
    PyObject *retval = PyInt_FromLong(long(obj->data->GetNormal()));
    return retval;
}

/*static*/ PyObject *
SpreadsheetAttributes_SetSliceIndex(PyObject *self, PyObject *args)
{
    SpreadsheetAttributesObject *obj = (SpreadsheetAttributesObject *)self;

    int ival;
    if(!PyArg_ParseTuple(args, "i", &ival))
        return NULL;

    // Set the sliceIndex in the object.
    obj->data->SetSliceIndex((int)ival);

    Py_INCREF(Py_None);
    return Py_None;
}

/*static*/ PyObject *
SpreadsheetAttributes_GetSliceIndex(PyObject *self, PyObject *args)
{
    SpreadsheetAttributesObject *obj = (SpreadsheetAttributesObject *)self;
    PyObject *retval = PyInt_FromLong(long(obj->data->GetSliceIndex()));
    return retval;
}

/*static*/ PyObject *
SpreadsheetAttributes_SetSpreadsheetFont(PyObject *self, PyObject *args)
{
    SpreadsheetAttributesObject *obj = (SpreadsheetAttributesObject *)self;

    char *str;
    if(!PyArg_ParseTuple(args, "s", &str))
        return NULL;

    // Set the spreadsheetFont in the object.
    obj->data->SetSpreadsheetFont(std::string(str));

    Py_INCREF(Py_None);
    return Py_None;
}

/*static*/ PyObject *
SpreadsheetAttributes_GetSpreadsheetFont(PyObject *self, PyObject *args)
{
    SpreadsheetAttributesObject *obj = (SpreadsheetAttributesObject *)self;
    PyObject *retval = PyString_FromString(obj->data->GetSpreadsheetFont().c_str());
    return retval;
}

/*static*/ PyObject *
SpreadsheetAttributes_SetShowPatchOutline(PyObject *self, PyObject *args)
{
    SpreadsheetAttributesObject *obj = (SpreadsheetAttributesObject *)self;

    int ival;
    if(!PyArg_ParseTuple(args, "i", &ival))
        return NULL;

    // Set the showPatchOutline in the object.
    obj->data->SetShowPatchOutline(ival != 0);

    Py_INCREF(Py_None);
    return Py_None;
}

/*static*/ PyObject *
SpreadsheetAttributes_GetShowPatchOutline(PyObject *self, PyObject *args)
{
    SpreadsheetAttributesObject *obj = (SpreadsheetAttributesObject *)self;
    PyObject *retval = PyInt_FromLong(obj->data->GetShowPatchOutline()?1L:0L);
    return retval;
}

/*static*/ PyObject *
SpreadsheetAttributes_SetShowCurrentCellOutline(PyObject *self, PyObject *args)
{
    SpreadsheetAttributesObject *obj = (SpreadsheetAttributesObject *)self;

    int ival;
    if(!PyArg_ParseTuple(args, "i", &ival))
        return NULL;

    // Set the showCurrentCellOutline in the object.
    obj->data->SetShowCurrentCellOutline(ival != 0);

    Py_INCREF(Py_None);
    return Py_None;
}

/*static*/ PyObject *
SpreadsheetAttributes_GetShowCurrentCellOutline(PyObject *self, PyObject *args)
{
    SpreadsheetAttributesObject *obj = (SpreadsheetAttributesObject *)self;
    PyObject *retval = PyInt_FromLong(obj->data->GetShowCurrentCellOutline()?1L:0L);
    return retval;
}

/*static*/ PyObject *
SpreadsheetAttributes_SetCurrentPickType(PyObject *self, PyObject *args)
{
    SpreadsheetAttributesObject *obj = (SpreadsheetAttributesObject *)self;

    int ival;
    if(!PyArg_ParseTuple(args, "i", &ival))
        return NULL;

    // Set the currentPickType in the object.
    obj->data->SetCurrentPickType((int)ival);

    Py_INCREF(Py_None);
    return Py_None;
}

/*static*/ PyObject *
SpreadsheetAttributes_GetCurrentPickType(PyObject *self, PyObject *args)
{
    SpreadsheetAttributesObject *obj = (SpreadsheetAttributesObject *)self;
    PyObject *retval = PyInt_FromLong(long(obj->data->GetCurrentPickType()));
    return retval;
}

/*static*/ PyObject *
SpreadsheetAttributes_SetCurrentPickLetter(PyObject *self, PyObject *args)
{
    SpreadsheetAttributesObject *obj = (SpreadsheetAttributesObject *)self;

    char *str;
    if(!PyArg_ParseTuple(args, "s", &str))
        return NULL;

    // Set the currentPickLetter in the object.
    obj->data->SetCurrentPickLetter(std::string(str));

    Py_INCREF(Py_None);
    return Py_None;
}

/*static*/ PyObject *
SpreadsheetAttributes_GetCurrentPickLetter(PyObject *self, PyObject *args)
{
    SpreadsheetAttributesObject *obj = (SpreadsheetAttributesObject *)self;
    PyObject *retval = PyString_FromString(obj->data->GetCurrentPickLetter().c_str());
    return retval;
}

/*static*/ PyObject *
SpreadsheetAttributes_SetPastPickLetters(PyObject *self, PyObject *args)
{
    SpreadsheetAttributesObject *obj = (SpreadsheetAttributesObject *)self;

    stringVector  &vec = obj->data->GetPastPickLetters();
    PyObject     *tuple;
    if(!PyArg_ParseTuple(args, "O", &tuple))
        return NULL;

    if(PyTuple_Check(tuple))
    {
        vec.resize(PyTuple_Size(tuple));
        for(int i = 0; i < PyTuple_Size(tuple); ++i)
        {
            PyObject *item = PyTuple_GET_ITEM(tuple, i);
            if(PyString_Check(item))
            {
                char *item_cstr = PyString_AsString(item);
                vec[i] = std::string(item_cstr);
                PyString_AsString_Cleanup(item_cstr);
            }
            else
                vec[i] = std::string("");
        }
    }
    else if(PyString_Check(tuple))
    {
        vec.resize(1);
        char *tuple_cstr = PyString_AsString(tuple);
        vec[0] = std::string(tuple_cstr);
        PyString_AsString_Cleanup(tuple_cstr);
    }
    else
        return NULL;

    // Mark the pastPickLetters in the object as modified.
    obj->data->SelectPastPickLetters();

    Py_INCREF(Py_None);
    return Py_None;
}

/*static*/ PyObject *
SpreadsheetAttributes_GetPastPickLetters(PyObject *self, PyObject *args)
{
    SpreadsheetAttributesObject *obj = (SpreadsheetAttributesObject *)self;
    // Allocate a tuple the with enough entries to hold the pastPickLetters.
    const stringVector &pastPickLetters = obj->data->GetPastPickLetters();
    PyObject *retval = PyTuple_New(pastPickLetters.size());
    for(size_t i = 0; i < pastPickLetters.size(); ++i)
        PyTuple_SET_ITEM(retval, i, PyString_FromString(pastPickLetters[i].c_str()));
    return retval;
}



PyMethodDef PySpreadsheetAttributes_methods[SPREADSHEETATTRIBUTES_NMETH] = {
    {"Notify", SpreadsheetAttributes_Notify, METH_VARARGS},
    {"SetSubsetName", SpreadsheetAttributes_SetSubsetName, METH_VARARGS},
    {"GetSubsetName", SpreadsheetAttributes_GetSubsetName, METH_VARARGS},
    {"SetFormatString", SpreadsheetAttributes_SetFormatString, METH_VARARGS},
    {"GetFormatString", SpreadsheetAttributes_GetFormatString, METH_VARARGS},
    {"SetUseColorTable", SpreadsheetAttributes_SetUseColorTable, METH_VARARGS},
    {"GetUseColorTable", SpreadsheetAttributes_GetUseColorTable, METH_VARARGS},
    {"SetColorTableName", SpreadsheetAttributes_SetColorTableName, METH_VARARGS},
    {"GetColorTableName", SpreadsheetAttributes_GetColorTableName, METH_VARARGS},
    {"SetShowTracerPlane", SpreadsheetAttributes_SetShowTracerPlane, METH_VARARGS},
    {"GetShowTracerPlane", SpreadsheetAttributes_GetShowTracerPlane, METH_VARARGS},
    {"SetTracerColor", SpreadsheetAttributes_SetTracerColor, METH_VARARGS},
    {"GetTracerColor", SpreadsheetAttributes_GetTracerColor, METH_VARARGS},
    {"SetNormal", SpreadsheetAttributes_SetNormal, METH_VARARGS},
    {"GetNormal", SpreadsheetAttributes_GetNormal, METH_VARARGS},
    {"SetSliceIndex", SpreadsheetAttributes_SetSliceIndex, METH_VARARGS},
    {"GetSliceIndex", SpreadsheetAttributes_GetSliceIndex, METH_VARARGS},
    {"SetSpreadsheetFont", SpreadsheetAttributes_SetSpreadsheetFont, METH_VARARGS},
    {"GetSpreadsheetFont", SpreadsheetAttributes_GetSpreadsheetFont, METH_VARARGS},
    {"SetShowPatchOutline", SpreadsheetAttributes_SetShowPatchOutline, METH_VARARGS},
    {"GetShowPatchOutline", SpreadsheetAttributes_GetShowPatchOutline, METH_VARARGS},
    {"SetShowCurrentCellOutline", SpreadsheetAttributes_SetShowCurrentCellOutline, METH_VARARGS},
    {"GetShowCurrentCellOutline", SpreadsheetAttributes_GetShowCurrentCellOutline, METH_VARARGS},
    {"SetCurrentPickType", SpreadsheetAttributes_SetCurrentPickType, METH_VARARGS},
    {"GetCurrentPickType", SpreadsheetAttributes_GetCurrentPickType, METH_VARARGS},
    {"SetCurrentPickLetter", SpreadsheetAttributes_SetCurrentPickLetter, METH_VARARGS},
    {"GetCurrentPickLetter", SpreadsheetAttributes_GetCurrentPickLetter, METH_VARARGS},
    {"SetPastPickLetters", SpreadsheetAttributes_SetPastPickLetters, METH_VARARGS},
    {"GetPastPickLetters", SpreadsheetAttributes_GetPastPickLetters, METH_VARARGS},
    {NULL, NULL}
};

//
// Type functions
//

static void
SpreadsheetAttributes_dealloc(PyObject *v)
{
   SpreadsheetAttributesObject *obj = (SpreadsheetAttributesObject *)v;
   if(obj->parent != 0)
       Py_DECREF(obj->parent);
   if(obj->owns)
       delete obj->data;
}

static PyObject *SpreadsheetAttributes_richcompare(PyObject *self, PyObject *other, int op);
PyObject *
PySpreadsheetAttributes_getattr(PyObject *self, char *name)
{
    if(strcmp(name, "subsetName") == 0)
        return SpreadsheetAttributes_GetSubsetName(self, NULL);
    if(strcmp(name, "formatString") == 0)
        return SpreadsheetAttributes_GetFormatString(self, NULL);
    if(strcmp(name, "useColorTable") == 0)
        return SpreadsheetAttributes_GetUseColorTable(self, NULL);
    if(strcmp(name, "colorTableName") == 0)
        return SpreadsheetAttributes_GetColorTableName(self, NULL);
    if(strcmp(name, "showTracerPlane") == 0)
        return SpreadsheetAttributes_GetShowTracerPlane(self, NULL);
    if(strcmp(name, "tracerColor") == 0)
        return SpreadsheetAttributes_GetTracerColor(self, NULL);
    if(strcmp(name, "normal") == 0)
        return SpreadsheetAttributes_GetNormal(self, NULL);
    if(strcmp(name, "X") == 0)
        return PyInt_FromLong(long(SpreadsheetAttributes::X));
    if(strcmp(name, "Y") == 0)
        return PyInt_FromLong(long(SpreadsheetAttributes::Y));
    if(strcmp(name, "Z") == 0)
        return PyInt_FromLong(long(SpreadsheetAttributes::Z));

    if(strcmp(name, "sliceIndex") == 0)
        return SpreadsheetAttributes_GetSliceIndex(self, NULL);
    if(strcmp(name, "spreadsheetFont") == 0)
        return SpreadsheetAttributes_GetSpreadsheetFont(self, NULL);
    if(strcmp(name, "showPatchOutline") == 0)
        return SpreadsheetAttributes_GetShowPatchOutline(self, NULL);
    if(strcmp(name, "showCurrentCellOutline") == 0)
        return SpreadsheetAttributes_GetShowCurrentCellOutline(self, NULL);
    if(strcmp(name, "currentPickType") == 0)
        return SpreadsheetAttributes_GetCurrentPickType(self, NULL);
    if(strcmp(name, "currentPickLetter") == 0)
        return SpreadsheetAttributes_GetCurrentPickLetter(self, NULL);
    if(strcmp(name, "pastPickLetters") == 0)
        return SpreadsheetAttributes_GetPastPickLetters(self, NULL);

    return Py_FindMethod(PySpreadsheetAttributes_methods, self, name);
}

int
PySpreadsheetAttributes_setattr(PyObject *self, char *name, PyObject *args)
{
    // Create a tuple to contain the arguments since all of the Set
    // functions expect a tuple.
    PyObject *tuple = PyTuple_New(1);
    PyTuple_SET_ITEM(tuple, 0, args);
    Py_INCREF(args);
    PyObject *obj = NULL;

    if(strcmp(name, "subsetName") == 0)
        obj = SpreadsheetAttributes_SetSubsetName(self, tuple);
    else if(strcmp(name, "formatString") == 0)
        obj = SpreadsheetAttributes_SetFormatString(self, tuple);
    else if(strcmp(name, "useColorTable") == 0)
        obj = SpreadsheetAttributes_SetUseColorTable(self, tuple);
    else if(strcmp(name, "colorTableName") == 0)
        obj = SpreadsheetAttributes_SetColorTableName(self, tuple);
    else if(strcmp(name, "showTracerPlane") == 0)
        obj = SpreadsheetAttributes_SetShowTracerPlane(self, tuple);
    else if(strcmp(name, "tracerColor") == 0)
        obj = SpreadsheetAttributes_SetTracerColor(self, tuple);
    else if(strcmp(name, "normal") == 0)
        obj = SpreadsheetAttributes_SetNormal(self, tuple);
    else if(strcmp(name, "sliceIndex") == 0)
        obj = SpreadsheetAttributes_SetSliceIndex(self, tuple);
    else if(strcmp(name, "spreadsheetFont") == 0)
        obj = SpreadsheetAttributes_SetSpreadsheetFont(self, tuple);
    else if(strcmp(name, "showPatchOutline") == 0)
        obj = SpreadsheetAttributes_SetShowPatchOutline(self, tuple);
    else if(strcmp(name, "showCurrentCellOutline") == 0)
        obj = SpreadsheetAttributes_SetShowCurrentCellOutline(self, tuple);
    else if(strcmp(name, "currentPickType") == 0)
        obj = SpreadsheetAttributes_SetCurrentPickType(self, tuple);
    else if(strcmp(name, "currentPickLetter") == 0)
        obj = SpreadsheetAttributes_SetCurrentPickLetter(self, tuple);
    else if(strcmp(name, "pastPickLetters") == 0)
        obj = SpreadsheetAttributes_SetPastPickLetters(self, tuple);

    if(obj != NULL)
        Py_DECREF(obj);

    Py_DECREF(tuple);
    if( obj == NULL)
        PyErr_Format(PyExc_RuntimeError, "Unable to set unknown attribute: '%s'", name);
    return (obj != NULL) ? 0 : -1;
}

static int
SpreadsheetAttributes_print(PyObject *v, FILE *fp, int flags)
{
    SpreadsheetAttributesObject *obj = (SpreadsheetAttributesObject *)v;
    fprintf(fp, "%s", PySpreadsheetAttributes_ToString(obj->data, "").c_str());
    return 0;
}

PyObject *
SpreadsheetAttributes_str(PyObject *v)
{
    SpreadsheetAttributesObject *obj = (SpreadsheetAttributesObject *)v;
    return PyString_FromString(PySpreadsheetAttributes_ToString(obj->data,"").c_str());
}

//
// The doc string for the class.
//
#if PY_MAJOR_VERSION > 2 || (PY_MAJOR_VERSION == 2 && PY_MINOR_VERSION >= 5)
static const char *SpreadsheetAttributes_Purpose = "Contains the attributes for the visual spreadsheet.";
#else
static char *SpreadsheetAttributes_Purpose = "Contains the attributes for the visual spreadsheet.";
#endif

//
// Python Type Struct Def Macro from Py2and3Support.h
//
//         VISIT_PY_TYPE_OBJ( VPY_TYPE,
//                            VPY_NAME,
//                            VPY_OBJECT,
//                            VPY_DEALLOC,
//                            VPY_PRINT,
//                            VPY_GETATTR,
//                            VPY_SETATTR,
//                            VPY_STR,
//                            VPY_PURPOSE,
//                            VPY_RICHCOMP,
//                            VPY_AS_NUMBER)

//
// The type description structure
//

VISIT_PY_TYPE_OBJ(SpreadsheetAttributesType,         \
                  "SpreadsheetAttributes",           \
                  SpreadsheetAttributesObject,       \
                  SpreadsheetAttributes_dealloc,     \
                  SpreadsheetAttributes_print,       \
                  PySpreadsheetAttributes_getattr,   \
                  PySpreadsheetAttributes_setattr,   \
                  SpreadsheetAttributes_str,         \
                  SpreadsheetAttributes_Purpose,     \
                  SpreadsheetAttributes_richcompare, \
                  0); /* as_number*/

//
// Helper function for comparing.
//
static PyObject *
SpreadsheetAttributes_richcompare(PyObject *self, PyObject *other, int op)
{
    // only compare against the same type 
    if ( Py_TYPE(self) == Py_TYPE(other) 
         && Py_TYPE(self) == &SpreadsheetAttributesType)
    {
        Py_INCREF(Py_NotImplemented);
        return Py_NotImplemented;
    }

    PyObject *res = NULL;
    SpreadsheetAttributes *a = ((SpreadsheetAttributesObject *)self)->data;
    SpreadsheetAttributes *b = ((SpreadsheetAttributesObject *)other)->data;

    switch (op)
    {
       case Py_EQ:
           res = (*a == *b) ? Py_True : Py_False;
           break;
       case Py_NE:
           res = (*a != *b) ? Py_True : Py_False;
           break;
       default:
           res = Py_NotImplemented;
           break;
    }

    Py_INCREF(res);
    return res;
}

//
// Helper functions for object allocation.
//

static SpreadsheetAttributes *defaultAtts = 0;
static SpreadsheetAttributes *currentAtts = 0;

static PyObject *
NewSpreadsheetAttributes(int useCurrent)
{
    SpreadsheetAttributesObject *newObject;
    newObject = PyObject_NEW(SpreadsheetAttributesObject, &SpreadsheetAttributesType);
    if(newObject == NULL)
        return NULL;
    if(useCurrent && currentAtts != 0)
        newObject->data = new SpreadsheetAttributes(*currentAtts);
    else if(defaultAtts != 0)
        newObject->data = new SpreadsheetAttributes(*defaultAtts);
    else
        newObject->data = new SpreadsheetAttributes;
    newObject->owns = true;
    newObject->parent = 0;
    return (PyObject *)newObject;
}

static PyObject *
WrapSpreadsheetAttributes(const SpreadsheetAttributes *attr)
{
    SpreadsheetAttributesObject *newObject;
    newObject = PyObject_NEW(SpreadsheetAttributesObject, &SpreadsheetAttributesType);
    if(newObject == NULL)
        return NULL;
    newObject->data = (SpreadsheetAttributes *)attr;
    newObject->owns = false;
    newObject->parent = 0;
    return (PyObject *)newObject;
}

///////////////////////////////////////////////////////////////////////////////
//
// Interface that is exposed to the VisIt module.
//
///////////////////////////////////////////////////////////////////////////////

PyObject *
SpreadsheetAttributes_new(PyObject *self, PyObject *args)
{
    int useCurrent = 0;
    if (!PyArg_ParseTuple(args, "i", &useCurrent))
    {
        if (!PyArg_ParseTuple(args, ""))
            return NULL;
        else
            PyErr_Clear();
    }

    return (PyObject *)NewSpreadsheetAttributes(useCurrent);
}

//
// Plugin method table. These methods are added to the visitmodule's methods.
//
static PyMethodDef SpreadsheetAttributesMethods[] = {
    {"SpreadsheetAttributes", SpreadsheetAttributes_new, METH_VARARGS},
    {NULL,      NULL}        /* Sentinel */
};

static Observer *SpreadsheetAttributesObserver = 0;

std::string
PySpreadsheetAttributes_GetLogString()
{
    std::string s("SpreadsheetAtts = SpreadsheetAttributes()\n");
    if(currentAtts != 0)
        s += PySpreadsheetAttributes_ToString(currentAtts, "SpreadsheetAtts.");
    return s;
}

static void
PySpreadsheetAttributes_CallLogRoutine(Subject *subj, void *data)
{
    typedef void (*logCallback)(const std::string &);
    logCallback cb = (logCallback)data;

    if(cb != 0)
    {
        std::string s("SpreadsheetAtts = SpreadsheetAttributes()\n");
        s += PySpreadsheetAttributes_ToString(currentAtts, "SpreadsheetAtts.");
        cb(s);
    }
}

void
PySpreadsheetAttributes_StartUp(SpreadsheetAttributes *subj, void *data)
{
    if(subj == 0)
        return;

    currentAtts = subj;
    PySpreadsheetAttributes_SetDefaults(subj);

    //
    // Create the observer that will be notified when the attributes change.
    //
    if(SpreadsheetAttributesObserver == 0)
    {
        SpreadsheetAttributesObserver = new ObserverToCallback(subj,
            PySpreadsheetAttributes_CallLogRoutine, (void *)data);
    }

}

void
PySpreadsheetAttributes_CloseDown()
{
    delete defaultAtts;
    defaultAtts = 0;
    delete SpreadsheetAttributesObserver;
    SpreadsheetAttributesObserver = 0;
}

PyMethodDef *
PySpreadsheetAttributes_GetMethodTable(int *nMethods)
{
    *nMethods = 1;
    return SpreadsheetAttributesMethods;
}

bool
PySpreadsheetAttributes_Check(PyObject *obj)
{
    return (obj->ob_type == &SpreadsheetAttributesType);
}

SpreadsheetAttributes *
PySpreadsheetAttributes_FromPyObject(PyObject *obj)
{
    SpreadsheetAttributesObject *obj2 = (SpreadsheetAttributesObject *)obj;
    return obj2->data;
}

PyObject *
PySpreadsheetAttributes_New()
{
    return NewSpreadsheetAttributes(0);
}

PyObject *
PySpreadsheetAttributes_Wrap(const SpreadsheetAttributes *attr)
{
    return WrapSpreadsheetAttributes(attr);
}

void
PySpreadsheetAttributes_SetParent(PyObject *obj, PyObject *parent)
{
    SpreadsheetAttributesObject *obj2 = (SpreadsheetAttributesObject *)obj;
    obj2->parent = parent;
}

void
PySpreadsheetAttributes_SetDefaults(const SpreadsheetAttributes *atts)
{
    if(defaultAtts)
        delete defaultAtts;

    defaultAtts = new SpreadsheetAttributes(*atts);
}

