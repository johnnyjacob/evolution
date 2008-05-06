#include <pygobject.h>
 
void eplugin_register_classes (PyObject *d); 
extern PyMethodDef eplugin_functions[];
 
DL_EXPORT(void)
initeplugin(void)
{
    PyObject *m, *d;
 
    init_pygobject ();
 
    m = Py_InitModule ("eplugin", eplugin_functions);
    d = PyModule_GetDict (m);
 
    eplugin_register_classes (d);
 
    if (PyErr_Occurred ()) {
        Py_FatalError ("can't initialise module eplugin");
    }
}
