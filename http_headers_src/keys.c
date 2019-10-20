/* 
 * Allah, THE ONE and THE ONLY ONE. THE ALL MIGHTY
 */

/*
 * src/keys.c
 * Written by, Sohail Qayum Malik
 */

#include "keys.h"

static void keys_PyTypeObject_destructor(keys_object *self) {

   if (self->type_str != NULL)
      free((char *)self->type_str);

   PyObject_Del(self);	
}

static int keys_PyTypeObject_printfunc(keys_object *self, FILE *fp, int flags) {

   size_t i;

   for (i = 0; i < strlen(self->type_str); i++)
      fprintf(fp, "%c", self->type_str[i]); 	   

   return 0;	
}	

static int keys_PyTypeObject_compfunc(PyObject *a, PyObject *b) {

   return 1; 	
}	

static long keys_PyTypeObject_hashfunc(keys_object *self) {

   return 1;	
}

/*
static PyObject *keys_PyTypeObject_ternaryfunc(keys_object *self, \
					PyObject *args, PyObject *keywords) {

    return (PyObject *)self;

}
*/

static PyObject *keys_PyTypeObject_getiterfunc(keys_object *self) {


   Py_XINCREF(Py_None);
   return (PyObject *)Py_None;
}

static PyObject *keys_PyTypeObject_richcmpfunc(PyObject *a, PyObject *b, int num) {

   Py_XINCREF(Py_None);
   return (PyObject *)Py_None;
}	

static int keys_PyTypeObject_initproc(keys_object *self, PyObject *args, PyObject *keywords) {

 
   return 0;
}	

static PyObject *keys_PyTypeObject_newfunc(PyTypeObject *ptr_keys, \
					PyObject *args, PyObject *keywords) {

   keys_object *self;

   Py_XINCREF(Py_None);
   return (PyObject *)Py_None;
}

static void keys_PyTypeObject_freefunc(void *p) {

}

/* Include/object.h, Objects/typeobject.c */
/* A new class, this class will inherit from class object. The function 
 * PyType_Ready()(Objects/typeobject.c) will assign the address of 
 * PyBaseObject_Type(an instance of PyTypeObject Objects/typeobject.c) 
 * to PyTypeObject::tp_base. The PyTypeObject PyBaseObject { }; is our class
 * named object
 * The above detail can be summerised as following Python statements... 
 *    class argsv(object):
 *       def __init__(self):
 *          print "Hello World" */
PyTypeObject keys = {
   
   /* Include/object.h */	
   PyObject_HEAD_INIT(NULL)
   0,						/* ob_size */
   "regexpr.keys",                            	/* tp_name, module.typename */ 
   sizeof(keys_object),				/* sizeof(*self) */
   0,	  					/* tp_itemsize */
   /* Methods to implement standard operations(Include/object.h) */
   (destructor)keys_PyTypeObject_destructor,	/* tp_dealloc */
   (printfunc)keys_PyTypeObject_printfunc, 	/* tp_print */
   0, 						/* tp_getattr */
   0, 						/* tp_setattr */
   keys_PyTypeObject_compfunc,			/* tp_compare */
   0,						/* tp_repr */
   /* Methods suits for standard classes(Include/object.h) */ 
   0,						/* tp_as_number, \
						       PyNumberMethods* */
   0, 						/* tp_as_sequence, 
						       PySequenceMethods* */
   0,						/* tp_as_mapping, 
						       PyMappingMethods* */
   /*More standard operations(here for binary compatibility)(Include/object.h*/
   (hashfunc)keys_PyTypeObject_hashfunc,	/* tp_hash */
   (ternaryfunc)0/*keys_PyTypeObject_ternaryfunc*/, /* tp_call */
   (reprfunc)0,					/* tp_str */
   0,						/* tp_getattro */
   0,						/* tp_setattro */
   /* Functions to access object as input/output buffer(Include/object.h) */
   0,						/* tp_as_buffer, \
						        PyBufferProcs * */
   /*Flags to define presence of optional/expanded features(Include/object.h)*/
   Py_TPFLAGS_DEFAULT | Py_TPFLAGS_HAVE_CLASS | Py_TPFLAGS_HAVE_RICHCOMPARE,	/* tp_flags */
   keys_doc,					/* tp_doc, document string */
   /* Assigned meaning in 2.0 */
   /* a call function for all accessible objects(Include/object.h) */
   0,						/* tp_traverse */
   /* delete refrences to the contained objects(Include/object.h) */
   0,						/* tp_clear */
   /* Assigned meaning in release 2.1 */
   /* rich comparisons(Include/object.h) */
   keys_PyTypeObject_richcmpfunc,		/* tp_richcompare */
   /* weak reference enabler */
   0,						/* tp_weaklistoffset */
   /* Addes in release 2.2 */
   /* Iterators */
   (getiterfunc)keys_PyTypeObject_getiterfunc, /* tp_iter */
   (iternextfunc)0, 				  /* tp_iternext */
   /* Attribute descriptor and subclassing stuff */
   (PyMethodDef *)0,				/* tp_methods, PyMethodDef* */
   (PyMemberDef *)0,				/* tp_members, PyMemeberDef* */
   0,						/* tp_getset, PyGetSetDef* */
   0,						/* tp_base, _typeobject* */
   0,						/* tp_dict, PyObject */
   0,						/* tp_descr_get */
   0, 						/* tp_descr_set */
   0,						/* tp_dictoffset, Py_ssize_t */
   (initproc)keys_PyTypeObject_initproc,	/* tp_init */
   0,						/* tp_alloc */
   (newfunc)keys_PyTypeObject_newfunc,		/* tp_new */
   (freefunc)keys_PyTypeObject_freefunc,	/* tp_free, Low-Level \
						   free-memory routine */
   0,						/* tp_is_gc, For \
						   PyObject_IS_GC */
   0,						/* tp_bases, PyObject* */
   0,						/* tp_mro, method resolution \
						   order. PyObject* */
   0,						/* tp_cache, PyObject* */
   0,						/* tp_subclasses, PyObject* */
   0,						/* tp_weaklist, PyObject* */
   (destructor)0,				/* tp_del */  
};

