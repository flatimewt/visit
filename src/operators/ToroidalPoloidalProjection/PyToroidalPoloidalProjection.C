// Copyright (c) Lawrence Livermore National Security, LLC and other VisIt
// Project developers.  See the top-level LICENSE file for dates and other
// details.  No copyright assignment is required to contribute to VisIt.

#include <PyToroidalPoloidalProjection.h>
#include <ObserverToCallback.h>
#include <stdio.h>
#include <Py2and3Support.h>

// ****************************************************************************
// Module: PyToroidalPoloidalProjection
//
// Purpose:
//   Projects Exterior of Torus from 3D to ToroidalPoloidal mapping in 2D
//
// Note:       Autogenerated by xml2python. Do not modify by hand!
//
// Programmer: xml2python
// Creation:   omitted
//
// ****************************************************************************

//
// This struct contains the Python type information and a ToroidalPoloidalProjection.
//
struct ToroidalPoloidalProjectionObject
{
    PyObject_HEAD
    ToroidalPoloidalProjection *data;
    bool        owns;
    PyObject   *parent;
};

//
// Internal prototypes
//
static PyObject *NewToroidalPoloidalProjection(int);
std::string
PyToroidalPoloidalProjection_ToString(const ToroidalPoloidalProjection *atts, const char *prefix)
{
    std::string str;
    char tmpStr[1000];

    snprintf(tmpStr, 1000, "%sR0 = %g\n", prefix, atts->GetR0());
    str += tmpStr;
    snprintf(tmpStr, 1000, "%sr = %g\n", prefix, atts->GetR());
    str += tmpStr;
    const char *centroidSource_names = "Manual, Auto";
    switch (atts->GetCentroidSource())
    {
      case ToroidalPoloidalProjection::Manual:
          snprintf(tmpStr, 1000, "%scentroidSource = %sManual  # %s\n", prefix, prefix, centroidSource_names);
          str += tmpStr;
          break;
      case ToroidalPoloidalProjection::Auto:
          snprintf(tmpStr, 1000, "%scentroidSource = %sAuto  # %s\n", prefix, prefix, centroidSource_names);
          str += tmpStr;
          break;
      default:
          break;
    }

    {   const double *centroid = atts->GetCentroid();
        snprintf(tmpStr, 1000, "%scentroid = (", prefix);
        str += tmpStr;
        for(int i = 0; i < 3; ++i)
        {
            snprintf(tmpStr, 1000, "%g", centroid[i]);
            str += tmpStr;
            if(i < 2)
            {
                snprintf(tmpStr, 1000, ", ");
                str += tmpStr;
            }
        }
        snprintf(tmpStr, 1000, ")\n");
        str += tmpStr;
    }
    if(atts->GetProject2D())
        snprintf(tmpStr, 1000, "%sproject2D = 1\n", prefix);
    else
        snprintf(tmpStr, 1000, "%sproject2D = 0\n", prefix);
    str += tmpStr;
    return str;
}

static PyObject *
ToroidalPoloidalProjection_Notify(PyObject *self, PyObject *args)
{
    ToroidalPoloidalProjectionObject *obj = (ToroidalPoloidalProjectionObject *)self;
    obj->data->Notify();
    Py_INCREF(Py_None);
    return Py_None;
}

/*static*/ PyObject *
ToroidalPoloidalProjection_SetR0(PyObject *self, PyObject *args)
{
    ToroidalPoloidalProjectionObject *obj = (ToroidalPoloidalProjectionObject *)self;

    double dval;
    if(!PyArg_ParseTuple(args, "d", &dval))
        return NULL;

    // Set the R0 in the object.
    obj->data->SetR0(dval);

    Py_INCREF(Py_None);
    return Py_None;
}

/*static*/ PyObject *
ToroidalPoloidalProjection_GetR0(PyObject *self, PyObject *args)
{
    ToroidalPoloidalProjectionObject *obj = (ToroidalPoloidalProjectionObject *)self;
    PyObject *retval = PyFloat_FromDouble(obj->data->GetR0());
    return retval;
}

/*static*/ PyObject *
ToroidalPoloidalProjection_SetR(PyObject *self, PyObject *args)
{
    ToroidalPoloidalProjectionObject *obj = (ToroidalPoloidalProjectionObject *)self;

    double dval;
    if(!PyArg_ParseTuple(args, "d", &dval))
        return NULL;

    // Set the r in the object.
    obj->data->SetR(dval);

    Py_INCREF(Py_None);
    return Py_None;
}

/*static*/ PyObject *
ToroidalPoloidalProjection_GetR(PyObject *self, PyObject *args)
{
    ToroidalPoloidalProjectionObject *obj = (ToroidalPoloidalProjectionObject *)self;
    PyObject *retval = PyFloat_FromDouble(obj->data->GetR());
    return retval;
}

/*static*/ PyObject *
ToroidalPoloidalProjection_SetCentroidSource(PyObject *self, PyObject *args)
{
    ToroidalPoloidalProjectionObject *obj = (ToroidalPoloidalProjectionObject *)self;

    int ival;
    if(!PyArg_ParseTuple(args, "i", &ival))
        return NULL;

    // Set the centroidSource in the object.
    if(ival >= 0 && ival < 2)
        obj->data->SetCentroidSource(ToroidalPoloidalProjection::CentroidSource(ival));
    else
    {
        fprintf(stderr, "An invalid centroidSource value was given. "
                        "Valid values are in the range of [0,1]. "
                        "You can also use the following names: "
                        "Manual, Auto.");
        return NULL;
    }

    Py_INCREF(Py_None);
    return Py_None;
}

/*static*/ PyObject *
ToroidalPoloidalProjection_GetCentroidSource(PyObject *self, PyObject *args)
{
    ToroidalPoloidalProjectionObject *obj = (ToroidalPoloidalProjectionObject *)self;
    PyObject *retval = PyInt_FromLong(long(obj->data->GetCentroidSource()));
    return retval;
}

/*static*/ PyObject *
ToroidalPoloidalProjection_SetCentroid(PyObject *self, PyObject *args)
{
    ToroidalPoloidalProjectionObject *obj = (ToroidalPoloidalProjectionObject *)self;

    double *dvals = obj->data->GetCentroid();
    if(!PyArg_ParseTuple(args, "ddd", &dvals[0], &dvals[1], &dvals[2]))
    {
        PyObject     *tuple;
        if(!PyArg_ParseTuple(args, "O", &tuple))
            return NULL;

        if(PyTuple_Check(tuple))
        {
            if(PyTuple_Size(tuple) != 3)
                return NULL;

            PyErr_Clear();
            for(int i = 0; i < PyTuple_Size(tuple); ++i)
            {
                PyObject *item = PyTuple_GET_ITEM(tuple, i);
                if(PyFloat_Check(item))
                    dvals[i] = PyFloat_AS_DOUBLE(item);
                else if(PyInt_Check(item))
                    dvals[i] = double(PyInt_AS_LONG(item));
                else if(PyLong_Check(item))
                    dvals[i] = PyLong_AsDouble(item);
                else
                    dvals[i] = 0.;
            }
        }
        else
            return NULL;
    }

    // Mark the centroid in the object as modified.
    obj->data->SelectCentroid();

    Py_INCREF(Py_None);
    return Py_None;
}

/*static*/ PyObject *
ToroidalPoloidalProjection_GetCentroid(PyObject *self, PyObject *args)
{
    ToroidalPoloidalProjectionObject *obj = (ToroidalPoloidalProjectionObject *)self;
    // Allocate a tuple the with enough entries to hold the centroid.
    PyObject *retval = PyTuple_New(3);
    const double *centroid = obj->data->GetCentroid();
    for(int i = 0; i < 3; ++i)
        PyTuple_SET_ITEM(retval, i, PyFloat_FromDouble(centroid[i]));
    return retval;
}

/*static*/ PyObject *
ToroidalPoloidalProjection_SetProject2D(PyObject *self, PyObject *args)
{
    ToroidalPoloidalProjectionObject *obj = (ToroidalPoloidalProjectionObject *)self;

    int ival;
    if(!PyArg_ParseTuple(args, "i", &ival))
        return NULL;

    // Set the project2D in the object.
    obj->data->SetProject2D(ival != 0);

    Py_INCREF(Py_None);
    return Py_None;
}

/*static*/ PyObject *
ToroidalPoloidalProjection_GetProject2D(PyObject *self, PyObject *args)
{
    ToroidalPoloidalProjectionObject *obj = (ToroidalPoloidalProjectionObject *)self;
    PyObject *retval = PyInt_FromLong(obj->data->GetProject2D()?1L:0L);
    return retval;
}



PyMethodDef PyToroidalPoloidalProjection_methods[TOROIDALPOLOIDALPROJECTION_NMETH] = {
    {"Notify", ToroidalPoloidalProjection_Notify, METH_VARARGS},
    {"SetR0", ToroidalPoloidalProjection_SetR0, METH_VARARGS},
    {"GetR0", ToroidalPoloidalProjection_GetR0, METH_VARARGS},
    {"SetR", ToroidalPoloidalProjection_SetR, METH_VARARGS},
    {"GetR", ToroidalPoloidalProjection_GetR, METH_VARARGS},
    {"SetCentroidSource", ToroidalPoloidalProjection_SetCentroidSource, METH_VARARGS},
    {"GetCentroidSource", ToroidalPoloidalProjection_GetCentroidSource, METH_VARARGS},
    {"SetCentroid", ToroidalPoloidalProjection_SetCentroid, METH_VARARGS},
    {"GetCentroid", ToroidalPoloidalProjection_GetCentroid, METH_VARARGS},
    {"SetProject2D", ToroidalPoloidalProjection_SetProject2D, METH_VARARGS},
    {"GetProject2D", ToroidalPoloidalProjection_GetProject2D, METH_VARARGS},
    {NULL, NULL}
};

//
// Type functions
//

static void
ToroidalPoloidalProjection_dealloc(PyObject *v)
{
   ToroidalPoloidalProjectionObject *obj = (ToroidalPoloidalProjectionObject *)v;
   if(obj->parent != 0)
       Py_DECREF(obj->parent);
   if(obj->owns)
       delete obj->data;
}

static PyObject *ToroidalPoloidalProjection_richcompare(PyObject *self, PyObject *other, int op);
PyObject *
PyToroidalPoloidalProjection_getattr(PyObject *self, char *name)
{
    if(strcmp(name, "R0") == 0)
        return ToroidalPoloidalProjection_GetR0(self, NULL);
    if(strcmp(name, "r") == 0)
        return ToroidalPoloidalProjection_GetR(self, NULL);
    if(strcmp(name, "centroidSource") == 0)
        return ToroidalPoloidalProjection_GetCentroidSource(self, NULL);
    if(strcmp(name, "Manual") == 0)
        return PyInt_FromLong(long(ToroidalPoloidalProjection::Manual));
    if(strcmp(name, "Auto") == 0)
        return PyInt_FromLong(long(ToroidalPoloidalProjection::Auto));

    if(strcmp(name, "centroid") == 0)
        return ToroidalPoloidalProjection_GetCentroid(self, NULL);
    if(strcmp(name, "project2D") == 0)
        return ToroidalPoloidalProjection_GetProject2D(self, NULL);

    return Py_FindMethod(PyToroidalPoloidalProjection_methods, self, name);
}

int
PyToroidalPoloidalProjection_setattr(PyObject *self, char *name, PyObject *args)
{
    // Create a tuple to contain the arguments since all of the Set
    // functions expect a tuple.
    PyObject *tuple = PyTuple_New(1);
    PyTuple_SET_ITEM(tuple, 0, args);
    Py_INCREF(args);
    PyObject *obj = NULL;

    if(strcmp(name, "R0") == 0)
        obj = ToroidalPoloidalProjection_SetR0(self, tuple);
    else if(strcmp(name, "r") == 0)
        obj = ToroidalPoloidalProjection_SetR(self, tuple);
    else if(strcmp(name, "centroidSource") == 0)
        obj = ToroidalPoloidalProjection_SetCentroidSource(self, tuple);
    else if(strcmp(name, "centroid") == 0)
        obj = ToroidalPoloidalProjection_SetCentroid(self, tuple);
    else if(strcmp(name, "project2D") == 0)
        obj = ToroidalPoloidalProjection_SetProject2D(self, tuple);

    if(obj != NULL)
        Py_DECREF(obj);

    Py_DECREF(tuple);
    if( obj == NULL)
        PyErr_Format(PyExc_RuntimeError, "Unable to set unknown attribute: '%s'", name);
    return (obj != NULL) ? 0 : -1;
}

static int
ToroidalPoloidalProjection_print(PyObject *v, FILE *fp, int flags)
{
    ToroidalPoloidalProjectionObject *obj = (ToroidalPoloidalProjectionObject *)v;
    fprintf(fp, "%s", PyToroidalPoloidalProjection_ToString(obj->data, "").c_str());
    return 0;
}

PyObject *
ToroidalPoloidalProjection_str(PyObject *v)
{
    ToroidalPoloidalProjectionObject *obj = (ToroidalPoloidalProjectionObject *)v;
    return PyString_FromString(PyToroidalPoloidalProjection_ToString(obj->data,"").c_str());
}

//
// The doc string for the class.
//
#if PY_MAJOR_VERSION > 2 || (PY_MAJOR_VERSION == 2 && PY_MINOR_VERSION >= 5)
static const char *ToroidalPoloidalProjection_Purpose = "Projects Exterior of Torus from 3D to ToroidalPoloidal mapping in 2D";
#else
static char *ToroidalPoloidalProjection_Purpose = "Projects Exterior of Torus from 3D to ToroidalPoloidal mapping in 2D";
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

VISIT_PY_TYPE_OBJ(ToroidalPoloidalProjectionType,         \
                  "ToroidalPoloidalProjection",           \
                  ToroidalPoloidalProjectionObject,       \
                  ToroidalPoloidalProjection_dealloc,     \
                  ToroidalPoloidalProjection_print,       \
                  PyToroidalPoloidalProjection_getattr,   \
                  PyToroidalPoloidalProjection_setattr,   \
                  ToroidalPoloidalProjection_str,         \
                  ToroidalPoloidalProjection_Purpose,     \
                  ToroidalPoloidalProjection_richcompare, \
                  0); /* as_number*/

//
// Helper function for comparing.
//
static PyObject *
ToroidalPoloidalProjection_richcompare(PyObject *self, PyObject *other, int op)
{
    // only compare against the same type 
    if ( Py_TYPE(self) == Py_TYPE(other) 
         && Py_TYPE(self) == &ToroidalPoloidalProjectionType)
    {
        Py_INCREF(Py_NotImplemented);
        return Py_NotImplemented;
    }

    PyObject *res = NULL;
    ToroidalPoloidalProjection *a = ((ToroidalPoloidalProjectionObject *)self)->data;
    ToroidalPoloidalProjection *b = ((ToroidalPoloidalProjectionObject *)other)->data;

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

static ToroidalPoloidalProjection *defaultAtts = 0;
static ToroidalPoloidalProjection *currentAtts = 0;

static PyObject *
NewToroidalPoloidalProjection(int useCurrent)
{
    ToroidalPoloidalProjectionObject *newObject;
    newObject = PyObject_NEW(ToroidalPoloidalProjectionObject, &ToroidalPoloidalProjectionType);
    if(newObject == NULL)
        return NULL;
    if(useCurrent && currentAtts != 0)
        newObject->data = new ToroidalPoloidalProjection(*currentAtts);
    else if(defaultAtts != 0)
        newObject->data = new ToroidalPoloidalProjection(*defaultAtts);
    else
        newObject->data = new ToroidalPoloidalProjection;
    newObject->owns = true;
    newObject->parent = 0;
    return (PyObject *)newObject;
}

static PyObject *
WrapToroidalPoloidalProjection(const ToroidalPoloidalProjection *attr)
{
    ToroidalPoloidalProjectionObject *newObject;
    newObject = PyObject_NEW(ToroidalPoloidalProjectionObject, &ToroidalPoloidalProjectionType);
    if(newObject == NULL)
        return NULL;
    newObject->data = (ToroidalPoloidalProjection *)attr;
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
ToroidalPoloidalProjection_new(PyObject *self, PyObject *args)
{
    int useCurrent = 0;
    if (!PyArg_ParseTuple(args, "i", &useCurrent))
    {
        if (!PyArg_ParseTuple(args, ""))
            return NULL;
        else
            PyErr_Clear();
    }

    return (PyObject *)NewToroidalPoloidalProjection(useCurrent);
}

//
// Plugin method table. These methods are added to the visitmodule's methods.
//
static PyMethodDef ToroidalPoloidalProjectionMethods[] = {
    {"ToroidalPoloidalProjection", ToroidalPoloidalProjection_new, METH_VARARGS},
    {NULL,      NULL}        /* Sentinel */
};

static Observer *ToroidalPoloidalProjectionObserver = 0;

std::string
PyToroidalPoloidalProjection_GetLogString()
{
    std::string s("ToroidalPoloidalProjection = ToroidalPoloidalProjection()\n");
    if(currentAtts != 0)
        s += PyToroidalPoloidalProjection_ToString(currentAtts, "ToroidalPoloidalProjection.");
    return s;
}

static void
PyToroidalPoloidalProjection_CallLogRoutine(Subject *subj, void *data)
{
    typedef void (*logCallback)(const std::string &);
    logCallback cb = (logCallback)data;

    if(cb != 0)
    {
        std::string s("ToroidalPoloidalProjection = ToroidalPoloidalProjection()\n");
        s += PyToroidalPoloidalProjection_ToString(currentAtts, "ToroidalPoloidalProjection.");
        cb(s);
    }
}

void
PyToroidalPoloidalProjection_StartUp(ToroidalPoloidalProjection *subj, void *data)
{
    if(subj == 0)
        return;

    currentAtts = subj;
    PyToroidalPoloidalProjection_SetDefaults(subj);

    //
    // Create the observer that will be notified when the attributes change.
    //
    if(ToroidalPoloidalProjectionObserver == 0)
    {
        ToroidalPoloidalProjectionObserver = new ObserverToCallback(subj,
            PyToroidalPoloidalProjection_CallLogRoutine, (void *)data);
    }

}

void
PyToroidalPoloidalProjection_CloseDown()
{
    delete defaultAtts;
    defaultAtts = 0;
    delete ToroidalPoloidalProjectionObserver;
    ToroidalPoloidalProjectionObserver = 0;
}

PyMethodDef *
PyToroidalPoloidalProjection_GetMethodTable(int *nMethods)
{
    *nMethods = 1;
    return ToroidalPoloidalProjectionMethods;
}

bool
PyToroidalPoloidalProjection_Check(PyObject *obj)
{
    return (obj->ob_type == &ToroidalPoloidalProjectionType);
}

ToroidalPoloidalProjection *
PyToroidalPoloidalProjection_FromPyObject(PyObject *obj)
{
    ToroidalPoloidalProjectionObject *obj2 = (ToroidalPoloidalProjectionObject *)obj;
    return obj2->data;
}

PyObject *
PyToroidalPoloidalProjection_New()
{
    return NewToroidalPoloidalProjection(0);
}

PyObject *
PyToroidalPoloidalProjection_Wrap(const ToroidalPoloidalProjection *attr)
{
    return WrapToroidalPoloidalProjection(attr);
}

void
PyToroidalPoloidalProjection_SetParent(PyObject *obj, PyObject *parent)
{
    ToroidalPoloidalProjectionObject *obj2 = (ToroidalPoloidalProjectionObject *)obj;
    obj2->parent = parent;
}

void
PyToroidalPoloidalProjection_SetDefaults(const ToroidalPoloidalProjection *atts)
{
    if(defaultAtts)
        delete defaultAtts;

    defaultAtts = new ToroidalPoloidalProjection(*atts);
}

