// Copyright (c) Lawrence Livermore National Security, LLC and other VisIt
// Project developers.  See the top-level LICENSE file for dates and other
// details.  No copyright assignment is required to contribute to VisIt.

#include <PyElevateAttributes.h>
#include <ObserverToCallback.h>
#include <stdio.h>
#include <Py2and3Support.h>

// ****************************************************************************
// Module: PyElevateAttributes
//
// Purpose:
//   Attributes for the elevate operator
//
// Note:       Autogenerated by xml2python. Do not modify by hand!
//
// Programmer: xml2python
// Creation:   omitted
//
// ****************************************************************************

//
// This struct contains the Python type information and a ElevateAttributes.
//
struct ElevateAttributesObject
{
    PyObject_HEAD
    ElevateAttributes *data;
    bool        owns;
    PyObject   *parent;
};

//
// Internal prototypes
//
static PyObject *NewElevateAttributes(int);
std::string
PyElevateAttributes_ToString(const ElevateAttributes *atts, const char *prefix)
{
    std::string str;
    char tmpStr[1000];

    const char *useXYLimits_names = "Never, Auto, Always";
    switch (atts->GetUseXYLimits())
    {
      case ElevateAttributes::Never:
          snprintf(tmpStr, 1000, "%suseXYLimits = %sNever  # %s\n", prefix, prefix, useXYLimits_names);
          str += tmpStr;
          break;
      case ElevateAttributes::Auto:
          snprintf(tmpStr, 1000, "%suseXYLimits = %sAuto  # %s\n", prefix, prefix, useXYLimits_names);
          str += tmpStr;
          break;
      case ElevateAttributes::Always:
          snprintf(tmpStr, 1000, "%suseXYLimits = %sAlways  # %s\n", prefix, prefix, useXYLimits_names);
          str += tmpStr;
          break;
      default:
          break;
    }

    const char *limitsMode_names = "OriginalData, CurrentPlot";
    switch (atts->GetLimitsMode())
    {
      case ElevateAttributes::OriginalData:
          snprintf(tmpStr, 1000, "%slimitsMode = %sOriginalData  # %s\n", prefix, prefix, limitsMode_names);
          str += tmpStr;
          break;
      case ElevateAttributes::CurrentPlot:
          snprintf(tmpStr, 1000, "%slimitsMode = %sCurrentPlot  # %s\n", prefix, prefix, limitsMode_names);
          str += tmpStr;
          break;
      default:
          break;
    }

    const char *scaling_names = "Linear, Log, Skew";
    switch (atts->GetScaling())
    {
      case ElevateAttributes::Linear:
          snprintf(tmpStr, 1000, "%sscaling = %sLinear  # %s\n", prefix, prefix, scaling_names);
          str += tmpStr;
          break;
      case ElevateAttributes::Log:
          snprintf(tmpStr, 1000, "%sscaling = %sLog  # %s\n", prefix, prefix, scaling_names);
          str += tmpStr;
          break;
      case ElevateAttributes::Skew:
          snprintf(tmpStr, 1000, "%sscaling = %sSkew  # %s\n", prefix, prefix, scaling_names);
          str += tmpStr;
          break;
      default:
          break;
    }

    snprintf(tmpStr, 1000, "%sskewFactor = %g\n", prefix, atts->GetSkewFactor());
    str += tmpStr;
    if(atts->GetMinFlag())
        snprintf(tmpStr, 1000, "%sminFlag = 1\n", prefix);
    else
        snprintf(tmpStr, 1000, "%sminFlag = 0\n", prefix);
    str += tmpStr;
    snprintf(tmpStr, 1000, "%smin = %g\n", prefix, atts->GetMin());
    str += tmpStr;
    if(atts->GetMaxFlag())
        snprintf(tmpStr, 1000, "%smaxFlag = 1\n", prefix);
    else
        snprintf(tmpStr, 1000, "%smaxFlag = 0\n", prefix);
    str += tmpStr;
    snprintf(tmpStr, 1000, "%smax = %g\n", prefix, atts->GetMax());
    str += tmpStr;
    if(atts->GetZeroFlag())
        snprintf(tmpStr, 1000, "%szeroFlag = 1\n", prefix);
    else
        snprintf(tmpStr, 1000, "%szeroFlag = 0\n", prefix);
    str += tmpStr;
    snprintf(tmpStr, 1000, "%svariable = \"%s\"\n", prefix, atts->GetVariable().c_str());
    str += tmpStr;
    return str;
}

static PyObject *
ElevateAttributes_Notify(PyObject *self, PyObject *args)
{
    ElevateAttributesObject *obj = (ElevateAttributesObject *)self;
    obj->data->Notify();
    Py_INCREF(Py_None);
    return Py_None;
}

/*static*/ PyObject *
ElevateAttributes_SetUseXYLimits(PyObject *self, PyObject *args)
{
    ElevateAttributesObject *obj = (ElevateAttributesObject *)self;

    int ival;
    if(!PyArg_ParseTuple(args, "i", &ival))
        return NULL;

    // Set the useXYLimits in the object.
    if(ival >= 0 && ival < 3)
        obj->data->SetUseXYLimits(ElevateAttributes::ScalingMode(ival));
    else
    {
        fprintf(stderr, "An invalid useXYLimits value was given. "
                        "Valid values are in the range of [0,2]. "
                        "You can also use the following names: "
                        "Never, Auto, Always.");
        return NULL;
    }

    Py_INCREF(Py_None);
    return Py_None;
}

/*static*/ PyObject *
ElevateAttributes_GetUseXYLimits(PyObject *self, PyObject *args)
{
    ElevateAttributesObject *obj = (ElevateAttributesObject *)self;
    PyObject *retval = PyInt_FromLong(long(obj->data->GetUseXYLimits()));
    return retval;
}

/*static*/ PyObject *
ElevateAttributes_SetLimitsMode(PyObject *self, PyObject *args)
{
    ElevateAttributesObject *obj = (ElevateAttributesObject *)self;

    int ival;
    if(!PyArg_ParseTuple(args, "i", &ival))
        return NULL;

    // Set the limitsMode in the object.
    if(ival >= 0 && ival < 2)
        obj->data->SetLimitsMode(ElevateAttributes::LimitsMode(ival));
    else
    {
        fprintf(stderr, "An invalid limitsMode value was given. "
                        "Valid values are in the range of [0,1]. "
                        "You can also use the following names: "
                        "OriginalData, CurrentPlot.");
        return NULL;
    }

    Py_INCREF(Py_None);
    return Py_None;
}

/*static*/ PyObject *
ElevateAttributes_GetLimitsMode(PyObject *self, PyObject *args)
{
    ElevateAttributesObject *obj = (ElevateAttributesObject *)self;
    PyObject *retval = PyInt_FromLong(long(obj->data->GetLimitsMode()));
    return retval;
}

/*static*/ PyObject *
ElevateAttributes_SetScaling(PyObject *self, PyObject *args)
{
    ElevateAttributesObject *obj = (ElevateAttributesObject *)self;

    int ival;
    if(!PyArg_ParseTuple(args, "i", &ival))
        return NULL;

    // Set the scaling in the object.
    if(ival >= 0 && ival < 3)
        obj->data->SetScaling(ElevateAttributes::Scaling(ival));
    else
    {
        fprintf(stderr, "An invalid scaling value was given. "
                        "Valid values are in the range of [0,2]. "
                        "You can also use the following names: "
                        "Linear, Log, Skew.");
        return NULL;
    }

    Py_INCREF(Py_None);
    return Py_None;
}

/*static*/ PyObject *
ElevateAttributes_GetScaling(PyObject *self, PyObject *args)
{
    ElevateAttributesObject *obj = (ElevateAttributesObject *)self;
    PyObject *retval = PyInt_FromLong(long(obj->data->GetScaling()));
    return retval;
}

/*static*/ PyObject *
ElevateAttributes_SetSkewFactor(PyObject *self, PyObject *args)
{
    ElevateAttributesObject *obj = (ElevateAttributesObject *)self;

    double dval;
    if(!PyArg_ParseTuple(args, "d", &dval))
        return NULL;

    // Set the skewFactor in the object.
    obj->data->SetSkewFactor(dval);

    Py_INCREF(Py_None);
    return Py_None;
}

/*static*/ PyObject *
ElevateAttributes_GetSkewFactor(PyObject *self, PyObject *args)
{
    ElevateAttributesObject *obj = (ElevateAttributesObject *)self;
    PyObject *retval = PyFloat_FromDouble(obj->data->GetSkewFactor());
    return retval;
}

/*static*/ PyObject *
ElevateAttributes_SetMinFlag(PyObject *self, PyObject *args)
{
    ElevateAttributesObject *obj = (ElevateAttributesObject *)self;

    int ival;
    if(!PyArg_ParseTuple(args, "i", &ival))
        return NULL;

    // Set the minFlag in the object.
    obj->data->SetMinFlag(ival != 0);

    Py_INCREF(Py_None);
    return Py_None;
}

/*static*/ PyObject *
ElevateAttributes_GetMinFlag(PyObject *self, PyObject *args)
{
    ElevateAttributesObject *obj = (ElevateAttributesObject *)self;
    PyObject *retval = PyInt_FromLong(obj->data->GetMinFlag()?1L:0L);
    return retval;
}

/*static*/ PyObject *
ElevateAttributes_SetMin(PyObject *self, PyObject *args)
{
    ElevateAttributesObject *obj = (ElevateAttributesObject *)self;

    double dval;
    if(!PyArg_ParseTuple(args, "d", &dval))
        return NULL;

    // Set the min in the object.
    obj->data->SetMin(dval);

    Py_INCREF(Py_None);
    return Py_None;
}

/*static*/ PyObject *
ElevateAttributes_GetMin(PyObject *self, PyObject *args)
{
    ElevateAttributesObject *obj = (ElevateAttributesObject *)self;
    PyObject *retval = PyFloat_FromDouble(obj->data->GetMin());
    return retval;
}

/*static*/ PyObject *
ElevateAttributes_SetMaxFlag(PyObject *self, PyObject *args)
{
    ElevateAttributesObject *obj = (ElevateAttributesObject *)self;

    int ival;
    if(!PyArg_ParseTuple(args, "i", &ival))
        return NULL;

    // Set the maxFlag in the object.
    obj->data->SetMaxFlag(ival != 0);

    Py_INCREF(Py_None);
    return Py_None;
}

/*static*/ PyObject *
ElevateAttributes_GetMaxFlag(PyObject *self, PyObject *args)
{
    ElevateAttributesObject *obj = (ElevateAttributesObject *)self;
    PyObject *retval = PyInt_FromLong(obj->data->GetMaxFlag()?1L:0L);
    return retval;
}

/*static*/ PyObject *
ElevateAttributes_SetMax(PyObject *self, PyObject *args)
{
    ElevateAttributesObject *obj = (ElevateAttributesObject *)self;

    double dval;
    if(!PyArg_ParseTuple(args, "d", &dval))
        return NULL;

    // Set the max in the object.
    obj->data->SetMax(dval);

    Py_INCREF(Py_None);
    return Py_None;
}

/*static*/ PyObject *
ElevateAttributes_GetMax(PyObject *self, PyObject *args)
{
    ElevateAttributesObject *obj = (ElevateAttributesObject *)self;
    PyObject *retval = PyFloat_FromDouble(obj->data->GetMax());
    return retval;
}

/*static*/ PyObject *
ElevateAttributes_SetZeroFlag(PyObject *self, PyObject *args)
{
    ElevateAttributesObject *obj = (ElevateAttributesObject *)self;

    int ival;
    if(!PyArg_ParseTuple(args, "i", &ival))
        return NULL;

    // Set the zeroFlag in the object.
    obj->data->SetZeroFlag(ival != 0);

    Py_INCREF(Py_None);
    return Py_None;
}

/*static*/ PyObject *
ElevateAttributes_GetZeroFlag(PyObject *self, PyObject *args)
{
    ElevateAttributesObject *obj = (ElevateAttributesObject *)self;
    PyObject *retval = PyInt_FromLong(obj->data->GetZeroFlag()?1L:0L);
    return retval;
}

/*static*/ PyObject *
ElevateAttributes_SetVariable(PyObject *self, PyObject *args)
{
    ElevateAttributesObject *obj = (ElevateAttributesObject *)self;

    char *str;
    if(!PyArg_ParseTuple(args, "s", &str))
        return NULL;

    // Set the variable in the object.
    obj->data->SetVariable(std::string(str));

    Py_INCREF(Py_None);
    return Py_None;
}

/*static*/ PyObject *
ElevateAttributes_GetVariable(PyObject *self, PyObject *args)
{
    ElevateAttributesObject *obj = (ElevateAttributesObject *)self;
    PyObject *retval = PyString_FromString(obj->data->GetVariable().c_str());
    return retval;
}



PyMethodDef PyElevateAttributes_methods[ELEVATEATTRIBUTES_NMETH] = {
    {"Notify", ElevateAttributes_Notify, METH_VARARGS},
    {"SetUseXYLimits", ElevateAttributes_SetUseXYLimits, METH_VARARGS},
    {"GetUseXYLimits", ElevateAttributes_GetUseXYLimits, METH_VARARGS},
    {"SetLimitsMode", ElevateAttributes_SetLimitsMode, METH_VARARGS},
    {"GetLimitsMode", ElevateAttributes_GetLimitsMode, METH_VARARGS},
    {"SetScaling", ElevateAttributes_SetScaling, METH_VARARGS},
    {"GetScaling", ElevateAttributes_GetScaling, METH_VARARGS},
    {"SetSkewFactor", ElevateAttributes_SetSkewFactor, METH_VARARGS},
    {"GetSkewFactor", ElevateAttributes_GetSkewFactor, METH_VARARGS},
    {"SetMinFlag", ElevateAttributes_SetMinFlag, METH_VARARGS},
    {"GetMinFlag", ElevateAttributes_GetMinFlag, METH_VARARGS},
    {"SetMin", ElevateAttributes_SetMin, METH_VARARGS},
    {"GetMin", ElevateAttributes_GetMin, METH_VARARGS},
    {"SetMaxFlag", ElevateAttributes_SetMaxFlag, METH_VARARGS},
    {"GetMaxFlag", ElevateAttributes_GetMaxFlag, METH_VARARGS},
    {"SetMax", ElevateAttributes_SetMax, METH_VARARGS},
    {"GetMax", ElevateAttributes_GetMax, METH_VARARGS},
    {"SetZeroFlag", ElevateAttributes_SetZeroFlag, METH_VARARGS},
    {"GetZeroFlag", ElevateAttributes_GetZeroFlag, METH_VARARGS},
    {"SetVariable", ElevateAttributes_SetVariable, METH_VARARGS},
    {"GetVariable", ElevateAttributes_GetVariable, METH_VARARGS},
    {NULL, NULL}
};

//
// Type functions
//

static void
ElevateAttributes_dealloc(PyObject *v)
{
   ElevateAttributesObject *obj = (ElevateAttributesObject *)v;
   if(obj->parent != 0)
       Py_DECREF(obj->parent);
   if(obj->owns)
       delete obj->data;
}

static PyObject *ElevateAttributes_richcompare(PyObject *self, PyObject *other, int op);
PyObject *
PyElevateAttributes_getattr(PyObject *self, char *name)
{
    if(strcmp(name, "useXYLimits") == 0)
        return ElevateAttributes_GetUseXYLimits(self, NULL);
    if(strcmp(name, "Never") == 0)
        return PyInt_FromLong(long(ElevateAttributes::Never));
    if(strcmp(name, "Auto") == 0)
        return PyInt_FromLong(long(ElevateAttributes::Auto));
    if(strcmp(name, "Always") == 0)
        return PyInt_FromLong(long(ElevateAttributes::Always));

    if(strcmp(name, "limitsMode") == 0)
        return ElevateAttributes_GetLimitsMode(self, NULL);
    if(strcmp(name, "OriginalData") == 0)
        return PyInt_FromLong(long(ElevateAttributes::OriginalData));
    if(strcmp(name, "CurrentPlot") == 0)
        return PyInt_FromLong(long(ElevateAttributes::CurrentPlot));

    if(strcmp(name, "scaling") == 0)
        return ElevateAttributes_GetScaling(self, NULL);
    if(strcmp(name, "Linear") == 0)
        return PyInt_FromLong(long(ElevateAttributes::Linear));
    if(strcmp(name, "Log") == 0)
        return PyInt_FromLong(long(ElevateAttributes::Log));
    if(strcmp(name, "Skew") == 0)
        return PyInt_FromLong(long(ElevateAttributes::Skew));

    if(strcmp(name, "skewFactor") == 0)
        return ElevateAttributes_GetSkewFactor(self, NULL);
    if(strcmp(name, "minFlag") == 0)
        return ElevateAttributes_GetMinFlag(self, NULL);
    if(strcmp(name, "min") == 0)
        return ElevateAttributes_GetMin(self, NULL);
    if(strcmp(name, "maxFlag") == 0)
        return ElevateAttributes_GetMaxFlag(self, NULL);
    if(strcmp(name, "max") == 0)
        return ElevateAttributes_GetMax(self, NULL);
    if(strcmp(name, "zeroFlag") == 0)
        return ElevateAttributes_GetZeroFlag(self, NULL);
    if(strcmp(name, "variable") == 0)
        return ElevateAttributes_GetVariable(self, NULL);

    return Py_FindMethod(PyElevateAttributes_methods, self, name);
}

int
PyElevateAttributes_setattr(PyObject *self, char *name, PyObject *args)
{
    // Create a tuple to contain the arguments since all of the Set
    // functions expect a tuple.
    PyObject *tuple = PyTuple_New(1);
    PyTuple_SET_ITEM(tuple, 0, args);
    Py_INCREF(args);
    PyObject *obj = NULL;

    if(strcmp(name, "useXYLimits") == 0)
        obj = ElevateAttributes_SetUseXYLimits(self, tuple);
    else if(strcmp(name, "limitsMode") == 0)
        obj = ElevateAttributes_SetLimitsMode(self, tuple);
    else if(strcmp(name, "scaling") == 0)
        obj = ElevateAttributes_SetScaling(self, tuple);
    else if(strcmp(name, "skewFactor") == 0)
        obj = ElevateAttributes_SetSkewFactor(self, tuple);
    else if(strcmp(name, "minFlag") == 0)
        obj = ElevateAttributes_SetMinFlag(self, tuple);
    else if(strcmp(name, "min") == 0)
        obj = ElevateAttributes_SetMin(self, tuple);
    else if(strcmp(name, "maxFlag") == 0)
        obj = ElevateAttributes_SetMaxFlag(self, tuple);
    else if(strcmp(name, "max") == 0)
        obj = ElevateAttributes_SetMax(self, tuple);
    else if(strcmp(name, "zeroFlag") == 0)
        obj = ElevateAttributes_SetZeroFlag(self, tuple);
    else if(strcmp(name, "variable") == 0)
        obj = ElevateAttributes_SetVariable(self, tuple);

    if(obj != NULL)
        Py_DECREF(obj);

    Py_DECREF(tuple);
    if( obj == NULL)
        PyErr_Format(PyExc_RuntimeError, "Unable to set unknown attribute: '%s'", name);
    return (obj != NULL) ? 0 : -1;
}

static int
ElevateAttributes_print(PyObject *v, FILE *fp, int flags)
{
    ElevateAttributesObject *obj = (ElevateAttributesObject *)v;
    fprintf(fp, "%s", PyElevateAttributes_ToString(obj->data, "").c_str());
    return 0;
}

PyObject *
ElevateAttributes_str(PyObject *v)
{
    ElevateAttributesObject *obj = (ElevateAttributesObject *)v;
    return PyString_FromString(PyElevateAttributes_ToString(obj->data,"").c_str());
}

//
// The doc string for the class.
//
#if PY_MAJOR_VERSION > 2 || (PY_MAJOR_VERSION == 2 && PY_MINOR_VERSION >= 5)
static const char *ElevateAttributes_Purpose = "Attributes for the elevate operator";
#else
static char *ElevateAttributes_Purpose = "Attributes for the elevate operator";
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

VISIT_PY_TYPE_OBJ(ElevateAttributesType,         \
                  "ElevateAttributes",           \
                  ElevateAttributesObject,       \
                  ElevateAttributes_dealloc,     \
                  ElevateAttributes_print,       \
                  PyElevateAttributes_getattr,   \
                  PyElevateAttributes_setattr,   \
                  ElevateAttributes_str,         \
                  ElevateAttributes_Purpose,     \
                  ElevateAttributes_richcompare, \
                  0); /* as_number*/

//
// Helper function for comparing.
//
static PyObject *
ElevateAttributes_richcompare(PyObject *self, PyObject *other, int op)
{
    // only compare against the same type 
    if ( Py_TYPE(self) == Py_TYPE(other) 
         && Py_TYPE(self) == &ElevateAttributesType)
    {
        Py_INCREF(Py_NotImplemented);
        return Py_NotImplemented;
    }

    PyObject *res = NULL;
    ElevateAttributes *a = ((ElevateAttributesObject *)self)->data;
    ElevateAttributes *b = ((ElevateAttributesObject *)other)->data;

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

static ElevateAttributes *defaultAtts = 0;
static ElevateAttributes *currentAtts = 0;

static PyObject *
NewElevateAttributes(int useCurrent)
{
    ElevateAttributesObject *newObject;
    newObject = PyObject_NEW(ElevateAttributesObject, &ElevateAttributesType);
    if(newObject == NULL)
        return NULL;
    if(useCurrent && currentAtts != 0)
        newObject->data = new ElevateAttributes(*currentAtts);
    else if(defaultAtts != 0)
        newObject->data = new ElevateAttributes(*defaultAtts);
    else
        newObject->data = new ElevateAttributes;
    newObject->owns = true;
    newObject->parent = 0;
    return (PyObject *)newObject;
}

static PyObject *
WrapElevateAttributes(const ElevateAttributes *attr)
{
    ElevateAttributesObject *newObject;
    newObject = PyObject_NEW(ElevateAttributesObject, &ElevateAttributesType);
    if(newObject == NULL)
        return NULL;
    newObject->data = (ElevateAttributes *)attr;
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
ElevateAttributes_new(PyObject *self, PyObject *args)
{
    int useCurrent = 0;
    if (!PyArg_ParseTuple(args, "i", &useCurrent))
    {
        if (!PyArg_ParseTuple(args, ""))
            return NULL;
        else
            PyErr_Clear();
    }

    return (PyObject *)NewElevateAttributes(useCurrent);
}

//
// Plugin method table. These methods are added to the visitmodule's methods.
//
static PyMethodDef ElevateAttributesMethods[] = {
    {"ElevateAttributes", ElevateAttributes_new, METH_VARARGS},
    {NULL,      NULL}        /* Sentinel */
};

static Observer *ElevateAttributesObserver = 0;

std::string
PyElevateAttributes_GetLogString()
{
    std::string s("ElevateAtts = ElevateAttributes()\n");
    if(currentAtts != 0)
        s += PyElevateAttributes_ToString(currentAtts, "ElevateAtts.");
    return s;
}

static void
PyElevateAttributes_CallLogRoutine(Subject *subj, void *data)
{
    typedef void (*logCallback)(const std::string &);
    logCallback cb = (logCallback)data;

    if(cb != 0)
    {
        std::string s("ElevateAtts = ElevateAttributes()\n");
        s += PyElevateAttributes_ToString(currentAtts, "ElevateAtts.");
        cb(s);
    }
}

void
PyElevateAttributes_StartUp(ElevateAttributes *subj, void *data)
{
    if(subj == 0)
        return;

    currentAtts = subj;
    PyElevateAttributes_SetDefaults(subj);

    //
    // Create the observer that will be notified when the attributes change.
    //
    if(ElevateAttributesObserver == 0)
    {
        ElevateAttributesObserver = new ObserverToCallback(subj,
            PyElevateAttributes_CallLogRoutine, (void *)data);
    }

}

void
PyElevateAttributes_CloseDown()
{
    delete defaultAtts;
    defaultAtts = 0;
    delete ElevateAttributesObserver;
    ElevateAttributesObserver = 0;
}

PyMethodDef *
PyElevateAttributes_GetMethodTable(int *nMethods)
{
    *nMethods = 1;
    return ElevateAttributesMethods;
}

bool
PyElevateAttributes_Check(PyObject *obj)
{
    return (obj->ob_type == &ElevateAttributesType);
}

ElevateAttributes *
PyElevateAttributes_FromPyObject(PyObject *obj)
{
    ElevateAttributesObject *obj2 = (ElevateAttributesObject *)obj;
    return obj2->data;
}

PyObject *
PyElevateAttributes_New()
{
    return NewElevateAttributes(0);
}

PyObject *
PyElevateAttributes_Wrap(const ElevateAttributes *attr)
{
    return WrapElevateAttributes(attr);
}

void
PyElevateAttributes_SetParent(PyObject *obj, PyObject *parent)
{
    ElevateAttributesObject *obj2 = (ElevateAttributesObject *)obj;
    obj2->parent = parent;
}

void
PyElevateAttributes_SetDefaults(const ElevateAttributes *atts)
{
    if(defaultAtts)
        delete defaultAtts;

    defaultAtts = new ElevateAttributes(*atts);
}

