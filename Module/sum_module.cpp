#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <chrono>

static PyObject* sum_array_capi(PyObject* self, PyObject* args) {
    PyObject* listObj;
    if (!PyArg_ParseTuple(args, "O!", &PyList_Type, &listObj)) {
        return NULL;
    }

    Py_ssize_t size = PyList_Size(listObj);
    long long total = 0;

    auto start = std::chrono::high_resolution_clock::now();

    for (Py_ssize_t i = 0; i < size; ++i) {
        PyObject* item = PyList_GetItem(listObj, i);
        total += PyLong_AsLongLong(item);
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    double time_taken = elapsed.count();

    return Py_BuildValue("(Ld)", total, time_taken);
}

static PyMethodDef SumMethods[] = {
    {"sum_array", sum_array_capi, METH_VARARGS, "Calculate sum and return time."},
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef summodule = {
    PyModuleDef_HEAD_INIT,
    "sum_module",
    NULL,
    -1,
    SumMethods
};

PyMODINIT_FUNC PyInit_sum_module(void) {
    return PyModule_Create(&summodule);
}