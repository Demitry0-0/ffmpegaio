#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <pthread.h>
//#define attr_name "set_result"

typedef struct {
    PyObject* func;
    PyObject* args;
} PyFuncArgs;

pthread_t thread, thread2;
static const char* attr_name = "set_result";

void* some_work(void* arg)
{

    printf("1\n");

    PyObject *args = (PyObject *)arg;
    printf("2\n");
    PyObject *future = PyTuple_GetItem(args, 0);
    printf("3\n");
    Py_INCREF(future);
    printf("4\n");
    PyObject *value = PyTuple_GetItem(args, 1);
    printf("5\n");
    Py_INCREF(value);

    printf("6.1\n");
    printf("%p %p\n", future, attr_name);
    printf("123123 sdf sdf\n");
    //PyObject_HasAttrString(future, attr_name);
    printf("6.2\n");
    PyObject *set_result_method = PyObject_GetAttrString(future, attr_name);
    printf("7\n");
    Py_INCREF(set_result_method);

    printf("8\n");
    PyObject_CallOneArg(set_result_method, value);
    printf("9\n");
    return NULL;
}

static PyObject *
get_result(PyObject *self, PyObject *args)
{
    //int size = PyTuple_Size(args);
    PyObject *item = PyTuple_GetItem(args, 0);
    printf("item %p %p\n", item, attr_name);
    Py_INCREF(item);

    Py_INCREF(args);
    //some_work((void*)args);

    pthread_create(&thread, NULL, some_work, (void*)args);

	pthread_join(thread, NULL);

    return item;
}

// Определение коллекции методов, вызываемых из модуля
static PyMethodDef PyFFmpegMethods[] = {
  {"get_result", get_result, METH_VARARGS, " "}
};

// Определение модуля
static struct PyModuleDef ffmpegaio_moduledef = {
  PyModuleDef_HEAD_INIT,
  "ffmpegaio",
  "This module await ffmpeg",
  //-1,
  .m_methods = PyFFmpegMethods
};

PyMODINIT_FUNC PyInit_ffmpegaio(void) {
    return PyModuleDef_Init(&ffmpegaio_moduledef);
}