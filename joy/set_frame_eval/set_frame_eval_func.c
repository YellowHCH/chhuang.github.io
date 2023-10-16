#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <code.h>
#include <frameobject.h>
#define Py_BUILD_CORE
#include <internal/pycore_pystate.h>

#if PY_VERSION_HEX >= 0x03090000
static PyObject *custom_frame_eval(PyThreadState *state, PyFrameObject *frame,
                                   int throwflag) {
#else
static PyObject *custom_frame_eval(PyFrameObject *frame, int throwflag) {
#endif
  // Do something here.
  printf("Do something here ...\n");
  printf("Current function name: %s\n",
         PyUnicode_AsUTF8(frame->f_code->co_name));
  // Return to default eval frame function.
#if PY_VERSION_HEX >= 0x03090000
  return _PyEval_EvalFrameDefault(state, frame, throwflag);
#else
  return _PyEval_EvalFrameDefault(frame, throwflag);
#endif
}

static PyObject *set_frame_eval() {
  PyThreadState *state = PyThreadState_Get();
#if PY_VERSION_HEX >= 0x03090000
  _PyInterpreterState_SetEvalFrameFunc(state->interp, &custom_frame_eval);
#else
  state->interp->eval_frame = &custom_frame_eval;
#endif
  Py_RETURN_NONE;
}

static PyMethodDef MyMethods[] = {
    {"set_frame_eval", set_frame_eval, METH_NOARGS,
     "Modify frame eval to custom logic."},
    {NULL, NULL, 0, NULL} /* Sentinel */
};

static struct PyModuleDef use_custom_frame_eval = {
    PyModuleDef_HEAD_INIT, "use_custom_frame_eval", /* name of module */
    NULL, /* module documentation, may be NULL */
    -1,   /* size of per-interpreter state of the module, or -1 if the module
             keeps state in global variables. */
    MyMethods};

PyMODINIT_FUNC PyInit_use_custom_frame_eval(void) {
  return PyModule_Create(&use_custom_frame_eval);
}
