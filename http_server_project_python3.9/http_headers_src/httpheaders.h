/* 
 * Allah, THE ONE and THE ONLY ONE. THE ALL MIGHTY
 */

/*
 * httpheaders.h
 * Written by, Sohail Qayum Malik [soni@sharingeconomy.pk]
 */

#include <Python.h>
#include <windows.h>
#include <mmsystem.h>

#include "structmember.h"

#include "keys.h"

#define		NEW_LINE	0x0a
#define		CARRIAGE_RETURN	0x0d
#define		SPACE_BAR	0x20
#define		COLON		0x3a

/* Py_XDECREF and Py_DECREF, Py_XDECREF is called when refernced object could be NULL. When reference is not NULL it then apply the macro Py_DECREF on the
 refered to object, see file Include/object.h */

/* A Python module initialization function. Module init functions outside the 
 * Python core must be exported(they should've external linkage) */
#ifndef		PyMODINIT_FUNC		
#define		PyMODINIT_FUNC		void
#endif

#define		HTTPHEADERS_VERSION_DOC	"Version 0.1-Alpha - A very raw HTTP header parser.\nWritten by, Sohail Qayum Malik"

PyDoc_STRVAR(httpheaders_doc, "httpheaders\n");

/* Instance which deligates to the class(PyObjectType *ob_type) */
typedef struct 
{
   /* 
    * Macro PyObject_HEAD expands into...
    * struct _object *_ob_next;
    * struct _object *_ob_prev;
    * Py_ssize_t ob_refcnt;
    * struct _typeobject *ob_type;
    *
    * And the PyObject is declared as...
    *    typedef struct {   
    *       PyObject_HEAD
    *    }PyObject;   
    */	
   PyObject_HEAD

   /* Type specific members go here */
   char *header;
   char *message_body;
   /* This is just the maximum size of the buffer */
   Py_ssize_t size;
   /* It is just assigned a value which is never used */
   Py_ssize_t message_body_size;

   size_t index;
   //PyListObject* keys;
   PyObject *dict;
   	   		   
}httpheaders_object;	
