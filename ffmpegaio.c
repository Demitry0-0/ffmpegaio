#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <pthread.h>
#define GGIL_DECLARE  PyGILState_STATE ___save
#define GGIL_ENSURE  ___save = PyGILState_Ensure();
#define GGIL_RELEASE  PyGILState_Release(___save);

pthread_t thread;

void* some_work(void* arg)
{
    GGIL_DECLARE;

    GGIL_ENSURE;
    sleep(5);
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

    printf("6\n");
    PyObject_CallMethodOneArg(future, Py_BuildValue("s", "set_result"), value);

    printf("7\n");

    GGIL_RELEASE;
    printf("thread done\n");
    return NULL;
}

static PyObject *
get_result(PyObject *self, PyObject *args)
{
    //int size = PyTuple_Size(args);
    PyObject *item = PyTuple_GetItem(args, 0);
    printf("item %p\n", item);
    Py_INCREF(item);

    Py_INCREF(args);
    //some_work((void*)args);
    pthread_create(&thread, NULL, some_work, (void*)args);

	//pthread_join(thread, NULL);
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