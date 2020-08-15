/* 
 * Allah, THE ONE and THE ONLY ONE. THE ALL MIGHTY
 */

/*
 * httpheaders.c
 * Written by, Sohail Qayum Malik [soni@sharingeconomy.pk]
 */

/*
 * Programmers just push the ugly around
 */

/* 
   Other than the usual HTTP/1.* header "key:value pair", the dictionary made here has three more key:value pairs. These three key:value pairs are the result of tokenizing the very first line of each HTTP/1.* request into three dictionary keys...
   METHOD, RESOURCE, VERSION
 */

#include "httpheaders.h"

/* External linkage */
extern PyTypeObject keys;
/* Forward declaration, internal linkage */
static PyTypeObject httpheaders;

static void httpheaders_PyTypeObject_destructor(httpheaders_object *self) {

   if (self->dict != NULL) {

      /* Remember dict has its own class, the destructor of its class will 
       * deallocte it(not us, httpheaders class) */	
      Py_XDECREF(self->dict);
   }

   PyObject_Del(self);	
}

static PyObject* httpheaders_PyTypeObject_getiterfunc(httpheaders_object *self)
{
    PyObject *ret = NULL;

    if (self->dict != NULL)
    {
        self->index = 0;
	//self->keys = (PyListObject*)PyDict_Keys(self->dict);

        Py_XINCREF(self); 
	    ret = (PyObject*)self;
    }

    return ret;
}

static PyObject* httpheaders_PyTypeObject_iternextfunc(httpheaders_object *self)
{

    PyObject *list = PyList_New(2);

    //printf("Listsize = %d, self->index = %d\n", PyList_Size((PyObject*)self->keys), self->index);
    
    /*if (!(PyList_Size((PyObject*)self->keys) > self->index))
    {
        printf("Yes....\n");
    }*/
    
    /*if (list == NULL || !(PyList_Size((PyObject*)self->keys) > self->index)) 
    {
        return (PyObject*)NULL;
    }*/

    //PyObject* key = PyList_GetItem((PyObject*)self->keys, self->index);

    //PyList_SetItem(list, 0, key);
    //Py_XINCREF(Py_None);
    //PyList_SetItem(list, 1, Py_None);

    //self->index = self->index + 1;

    Py_ssize_t pos = 0;
    PyObject *key = NULL, *value = NULL;

    if (self->dict == NULL)
    {
        return (PyObject*)NULL;
    }

    while (PyDict_Next(self->dict, &pos, &key, &value))  
    {
        if (((keys_object*)key)->index == self->index)
	{
            //printf("---> %s\n", ((keys_object*)key)->type_str);
	    PyObject *type_str = PyUnicode_FromString(((keys_object*)key)->type_str);
	    if (type_str == NULL)
	    {
	        return (PyObject*)NULL;
	    }

            PyList_SetItem(list, 0, type_str);
	    //Py_XINCREF(Py_None);
	    PyList_SetItem(list, 1, value);

	    self->index = self->index + 1;

	    return (PyObject*)list;
	}
    }

    //Py_XINCREF(Py_None);
    //return Py_None;
    //return list;
    return (PyObject*)NULL;
}

static PyObject *httpheaders_PyTypeObject_ternaryfunc(httpheaders_object *self, PyObject *args, PyObject *keywords) 
{
   char *field, *starts, *ends;
   Py_ssize_t pos = 0, index = 0;
   PyObject *key, *value = NULL;

   /*if (!PyArg_ParseTuple(args, "s", &field)) 
   {
       return NULL;
   }*/

   if (PyArg_ParseTuple(args, "s", &field)) 
   {
       while(PyDict_Next(self->dict, &pos, &key, &value))
       {
           //printf("%s -> %s\n", ((keys_object*)key)->type_str/*PyString_AsString(((keys_object*)key)->type_str)*/, PyString_AsString(value));

           if (strcmp(((keys_object*)key)->type_str, field) == 0)
           {
               value = PyDict_GetItem(self->dict, key);
	       break;
           }
       }
   }
   
   /*value = PyDict_GetItemString(self->dict, field);*/
   if (value == NULL) {

      Py_XINCREF(Py_None);
      value = Py_None;
   }	   

/*
   while ((starts=strstr(self->header + index, field))) {

      if (*(ends = strchrnul(starts, 0x09)) == 0x09) {

      }	      

      index = ends - starts;
   }
*/   

   return value;	
}

// TODO, Written in hurry. Missed checks for NULLs and for other errors set by called functions
PyObject* httpheaders_PyTypeObject_reprfunc(httpheaders_object *self)
{
    Py_ssize_t pos = 0;
    PyObject *key = NULL, *value = NULL;

    //printf("Hello World");

    if (self->dict != NULL)
    {
        while (PyDict_Next(self->dict, &pos, &key, &value))
	    {
	        //PyObject* type_str = PyUnicode_FromString(((keys_object*)key)->type_str);
            //PyObject* type_str = ((keys_object*)key)->type_str;

            if (((keys_object*)key)->type_str != NULL)
            {
                if (strcmp(((keys_object*)key)->type_str, CONTENT_LENGTH) == 0)
                {
                    //printf("--> %d\n", atoi(PyBytes_AsString(PyUnicode_AsASCIIString(value))));
                    //printf ("---> \n");
                    Py_ssize_t content_length = atoi(PyBytes_AsString(PyUnicode_AsASCIIString(value)));
                    //printf("--> %d\n", content_length);

                    char* ptr = malloc(content_length + 1);

		            strncpy(ptr, self->message_body, content_length);

		            *(ptr + content_length) = '\0';

                    return PyUnicode_FromFormat("%s", ptr);
                }
            }
	        /* if (type_str != NULL)
	        {
	            if (strcmp(PyBytes_AsString(type_str), CONTENT_LENGTH) == 0)
		        {
		            Py_ssize_t content_length = atoi(PyBytes_AsString(value));

		            char* ptr = malloc(content_length + 1);

		            strncpy(ptr, self->message_body, content_length);

		            *(ptr + content_length) = '\0';

                    //printf ("----> %s", ptr);

                    //PyObject * body = Py_BuildValue("s", ptr);

                    //return Py_BuildValue("s", ptr);
                    return PyUnicode_FromFormat("%s", ptr);

                    //return body;                     
		        }
	        } */
	    }   
    }

    Py_XINCREF(Py_None);
    return (PyObject*)Py_None;
}

PyObject* httpheaders_PyTypeObject_reprfunc_tp_str(httpheaders_object *self)
{
    Py_ssize_t pos = 0;
    PyObject *key = NULL, *value = NULL;

    if (self->dict != NULL)
    {
        while (PyDict_Next(self->dict, &pos, &key, &value))
	    {
	        PyObject* type_str = PyBytes_FromString(((keys_object*)key)->type_str);

	        if (type_str != NULL)
	        {
	            if (strcmp(PyBytes_AsString(type_str), CONTENT_LENGTH) == 0)
		        {
		            Py_ssize_t content_length = atoi(PyBytes_AsString(value));

		            char* ptr = malloc(content_length + 1);

		            strncpy(ptr, self->message_body, content_length);

		            *(ptr + content_length) = '\0';

                    //printf ("----> %s", ptr);

                    //PyObject * body = Py_BuildValue("s", ptr);

                    //return Py_BuildValue("s", ptr);
                    //return PyUnicode_FromFormat("%s", ptr);
                    //return PyUnicode_FromString(ptr);
                    //printf("Helo World");
                    return PyUnicode_FromStringAndSize(ptr, content_length);

                    //return body;                     
		        }
	        }
	    }   
    }

    Py_XINCREF(Py_None);
    return (PyObject*)Py_None;
}

/* 
 * The message body start after a line 
 * \r\n
 * message body
 * This function does not deal with the message body
 */
/*
 * \n = 0x0a, \r = 0x0d, ' ' = 0x20
 * Get / HTTP/1.1
 * Connection: Keep-Alive \r\n
 * ---------------------------------
 * begin_ptr will be at 'C'(In the case of above line), end_ptr will be at '\n'
 * In the case of an empty line the begin_ptr is at '\r' and end_ptr is at
 * '\n' and end_ptr - begin_ptr will always be 1 
 * -------------------------------------------------------------------------
 */
static PyObject *httpheaders_PyTypeObject_descrgetfunc(httpheaders_object *self, PyObject *instance, PyObject *instance_type) 
{
   PyObject* value;
   keys_object* key;

   size_t len, i = 0;
   char *begin_ptr = self->header, *end_ptr = begin_ptr, *colon_ptr;

   /* 
      The very first line of request is not in "key:value pair" form. The very first line has this form... 
      METHOD / HTTP/1.*\r\n 
      This line is made into three key:value pairs, as such that...
      METHOD:METHOD
      RESOURCE:/
      VERSION:1.*
      PAYLOAD:(the content)
    */ 

   /* Turn header into key-value pairs and build dictionary */

   while(end_ptr - self->header < self->size) {

      end_ptr = strchr(begin_ptr, NEW_LINE);

      if (end_ptr && end_ptr[-1] == CARRIAGE_RETURN && end_ptr - begin_ptr > 1) {

         colon_ptr = strchr(begin_ptr, COLON);

	 if (colon_ptr) {

            if (colon_ptr < end_ptr) {

               if (colon_ptr[1] == SPACE_BAR)  {

		  /* The key is being made into a string(the COLON is now 
		   * a null character) */     
                  *colon_ptr = '\0';

		  key = PyObject_New(keys_object, &keys);
          
          if (key != NULL)
		  {                           
		      len = strlen(begin_ptr);
		      key->index = i;
		      key->type = 0;
		      key->type_str = malloc(len + 1);

		      if (key->type_str != NULL)
		      {
		          strcpy(key->type_str, begin_ptr);
			      *(key->type_str + len) = '\0';
			      value = PyUnicode_FromStringAndSize(colon_ptr + 2, (end_ptr - 1) - (colon_ptr + 2));
			      if (value != NULL)
			      {
			          Py_XINCREF(key);
			          Py_XINCREF(value);
                              
			          if (PyDict_SetItem(self->dict, (PyObject*)key, (PyObject*)value) < 0)
			          {
			          Py_XDECREF(key);
				  Py_XDECREF(value);
				  PyErr_Clear();
			      }

			  }
			  else
			  {
			      PyErr_Clear();
			  }
		      }
		      else
		      {
		          PyErr_Clear();
		      }
		  }
		  else
		  {
		       PyErr_Clear();		
		  }

		  //PyDict_SetItemString(self->dict, begin_ptr, PyString_FromStringAndSize(colon_ptr + 2, (end_ptr - 1) - (colon_ptr + 2)));
		  *colon_ptr = COLON;

		  i = i + 1;
	       } 
            }
	    else {
	       /* Connection: Keep-Alive\r\n 
		  In the above line, the colon was not found. 
		  Try to find the SPACE_BAR, if it is found then, try to 
		  make the three key:value pairs out of it. */
               /* GET / HTTP/1.1\r\n
		  We are here because of this above mentined header line */
               /* Create two key:value pairs  
		  METHOD:GET
		  RESOURCE:/ HTTP/1.1
		  VERSION:HTTP/1.1
		*/		  
               colon_ptr = strchr(begin_ptr, SPACE_BAR);
               if (colon_ptr && colon_ptr < end_ptr) {

	          char *foo;
		  /* The key is being made into a string(the SPACE_BAR is now a null character */     
                  /* *colon_ptr = '\0'; */

                  key = PyObject_New(keys_object, &keys);
		  if (key != NULL)
		  {
		      len = strlen("METHOD");
		      key->index = i;
		      key->type = 0;
		      key->type_str = malloc(len + 1);
                      if (key->type_str != NULL)
		      {
		          strcpy(key->type_str, "METHOD");
			  *(key->type_str + len) = '\0';
			  value = PyUnicode_FromStringAndSize(begin_ptr, colon_ptr - begin_ptr);
			  if (value != NULL)
			  {
			      Py_XINCREF(key);
			      Py_XINCREF(value);
			      if (PyDict_SetItem(self->dict, (PyObject*)key, value) < 0)
			      {
			          Py_XDECREF(key);
				  Py_XDECREF(value);
				  PyErr_Clear();
			      }
			  }
			  else
			  {
			      PyErr_Clear();
			  }
		      }
		  }
		  else
		  {
		      PyErr_Clear();
		  }
		  //PyDict_SetItemString(self->dict, "METHOD", PyString_FromStringAndSize(begin_ptr, colon_ptr - begin_ptr));
		  i = i + 1;
		  /* Now find the resource */
		  colon_ptr += 1;
		  foo = strchr(colon_ptr, SPACE_BAR);
		  if (foo && foo < end_ptr) 
		  {
		      key = PyObject_New(keys_object, &keys);
		      if (key != NULL)
		      {
		          len = strlen("RESOURCE");
			  key->index = i;
			  key->type = 0;
			  key->type_str = malloc(len + 1);
			  if (key->type_str != NULL)
			  {
			      strcpy(key->type_str, "RESOURCE");
			      *(key->type_str + len) = '\0';
			      value = PyUnicode_FromStringAndSize(colon_ptr, foo - colon_ptr);
			      if (value != NULL)
			      {
			          Py_XINCREF(key);
				  Py_XINCREF(value);

				  if (PyDict_SetItem(self->dict, (PyObject*)key, value) < 0)
				  {
				      Py_XDECREF(key);
				      Py_XDECREF(value);
				      PyErr_Clear();
				  }
			      }
			      else
			      {
			          PyErr_Clear();
			      }
			  }
		      }
		      else
		      {
		          PyErr_Clear();
		      }
		     //PyDict_SetItemString(self->dict, "RESOURCE", PyString_FromStringAndSize(colon_ptr, foo - colon_ptr));
		     
                     i = i + 1;

		     colon_ptr = foo + 1;
                     foo = strchr(colon_ptr, CARRIAGE_RETURN);
		     if (foo && foo < end_ptr)
		     {
                         key = PyObject_New(keys_object, &keys);
			 if (key != NULL)
			 {
			     len = strlen("VERSION");
			     key->index = i;
			     key->type = 0;
			     key->type_str = malloc(len + 1);
			     if (key->type_str != NULL)
			     {
			         strcpy(key->type_str, "VERSION");
				 *(key->type_str + len) = '\0';
				 value = PyUnicode_FromStringAndSize(colon_ptr, foo - colon_ptr);
				 if (value != NULL)
				 {
				     Py_XINCREF(key);
				     Py_XINCREF(value);

				     if (PyDict_SetItem(self->dict, (PyObject*)key, value) < 0)
				     {
				         Py_XDECREF(key);
					 Py_XDECREF(value);
					 PyErr_Clear();
				     }
				 }
				 else
				 {
				     PyErr_Clear(); 
				 }
			     }
			 }
			 else
			 {
			     PyErr_Clear();
			 }

		        //PyDict_SetItemString(self->dict, "VERSION", PyString_FromStringAndSize(colon_ptr, foo - colon_ptr)); 
			i = i + 1;
		     }
 		  }
		  /* *colon_ptr = SPACE_BAR; */
		  //i = i + 1;
               }		  
            }		     		    
         }	    
         
         end_ptr++;
	 begin_ptr = end_ptr;
      }
      else {

	 /* Just made the end_ptr and begin_ptr point at the first 
	  * character of the message body */
	 end_ptr++;
	 begin_ptr = end_ptr;

	 /* It points at the content, the Content-Length entity has the size */
	 self->message_body = begin_ptr;
	 /* HTTP request/reply is headers describing the content and the content  it self, deduct the size of the headers from the size of the reply and you get the size of the content */
	 /* IT IS NEVER USED ANY WHERE IN THE CODE */
	 self->message_body_size = self->size - (self->message_body - self->header); 
         /* We'll now end the "while loop", end of header compilation */
         break;
      }
   } /* end of while */

   /* The dict can not have two values with same key value, but the still bigger question is a HTTP header allowed to have two fields with the same name? lack of HTTP knowledge. The following statement is attempt at introducing a redundant Connection entity to the dictionary(collection of key/value pairs */
/*   
   PyDict_SetItemString(self->dict, "Connection", PyString_FromStringAndSize("Keep-Dead", 9));
*/   

   Py_INCREF(self->dict);
   return (PyObject *)self->dict;	
}

static int httpheaders_PyTypeObject_initproc(httpheaders_object *self, PyObject *args, PyObject *keywords) 
{
   int ret = 0;  	

   if (!PyArg_ParseTuple(args, "si", &(self->header), &(self->size))) {
	   
      Py_XDECREF(self);	   
      ret = -1;	   
   }
   else 
   {
     
     //printf("%s\n", self->header);

      /*(void *)self->ob_type->tp_descr_get((PyObject *)self, (PyObject *)NULL, (PyObject *)NULL);*/
      Py_TYPE(self)->tp_descr_get((PyObject *)self, (PyObject *)NULL, (PyObject *)NULL);
   }

   return ret;	
}	

static PyObject *httpheaders_PyTypeObject_newfunc(PyTypeObject *ptr_httpheaders, PyObject *args, PyObject *keywords) 
{
   httpheaders_object *self;

  /*  
     PyType_Ready(PyTypeObject *) does lot of things and lot it does not do, 
     one of the later things is not initializing tp_new and tp_init. If you 
     explicitly not do that then a runtime exception will be thrown at this 
     next statement. 
     The exception statement is... cannot create 'module.class' instance 
     'module.class' is taken from PyTypeObject::tp_name 
   */     
   self = PyObject_New(httpheaders_object, &httpheaders);

   if (self == NULL)
      return NULL;

   self->dict = PyDict_New();

   if (self->dict == NULL) 
      goto fail; /* I most of the time go there too; its sad but true */
   
   self->index = 0;
   //self->keys = (PyListObject*)NULL;
    
   return (PyObject *)self;

fail:
   Py_XDECREF(self);
   return NULL;
}

static void httpheaders_PyTypeObject_freefunc(void *p) {

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
static PyTypeObject httpheaders = {
   
   /* Include/object.h */	
   /*PyObject_HEAD_INIT(NULL)*/
   PyVarObject_HEAD_INIT(NULL, 0)
   /*0,*/						/* ob_size */
   "httpheaders.httpheaders",                   /* tp_name, module.typename */ 
   sizeof(httpheaders_object),			/* sizeof(*self) */
   0,	  					/* tp_itemsize */
   /* Methods to implement standard operations(Include/object.h) */
   (destructor)httpheaders_PyTypeObject_destructor,	/* tp_dealloc */
   (printfunc)0, 				/* tp_print */
   0,				        	/* tp_getattr */
   0,				         	/* tp_setattr */
   0,						/* tp_compare */
   (reprfunc)httpheaders_PyTypeObject_reprfunc,						/* tp_repr */
   /* Methods suits for standard classes(Include/object.h) */ 
   0,						/* tp_as_number, \
						       PyNumberMethods* */
   0, 						/* tp_as_sequence, 
						       PySequenceMethods* */
   0,						/* tp_as_mapping, 
						       PyMappingMethods* */
   /*More standard operations(here for binary compatibility)(Include/object.h*/
   0,						/* tp_hash */

   // https://docs.python.org/3/c-api/typeobj.html#c.PyTypeObject.tp_str
   (ternaryfunc)httpheaders_PyTypeObject_ternaryfunc, /* tp_call */ // Called by the str() which is eventually called by the print
   
   (reprfunc)0/*httpheaders_PyTypeObject_reprfunc_tp_str*/, /*httpheaders_PyTypeObject_reprfunc,*/	      /* tp_str */
   0,						/* tp_getattro */ /* o is obj */
   0,						/* tp_setattro */ /* o is obj */
   /* Functions to access object as input/output buffer(Include/object.h) */
   0,						/* tp_as_buffer, \
						        PyBufferProcs * */
   /*Flags to define presence of optional/expanded features(Include/object.h)*/
   Py_TPFLAGS_DEFAULT /*| Py_TPFLAGS_HAVE_CLASS*/,	/* tp_flags */
   httpheaders_doc,			        /* tp_doc, document string */
   /* Assigned meaning in 2.0 */
   /* a call function for all accessible objects(Include/object.h) */
   0,						/* tp_traverse */
   /* delete refrences to the contained objects(Include/object.h) */
   0,						/* tp_clear */
   /* Assigned meaning in release 2.1 */
   /* rich comparisons(Include/object.h) */
   0,						/* tp_richcompare */
   /* weak reference enabler */
   0,						/* tp_weaklistoffset */
   /* Addes in release 2.2 */
   /* Iterators */
   (getiterfunc)httpheaders_PyTypeObject_getiterfunc, /* tp_iter */
   (iternextfunc)httpheaders_PyTypeObject_iternextfunc, /* tp_iternext */
   /* Attribute descriptor and subclassing stuff */
   0,						/* tp_methods, PyMethodDef* */
   0,						/* tp_members, PyMemeberDef* */
   0,						/* tp_getset, PyGetSetDef* */
   0,						/* tp_base, _typeobject* */
   0,						/* tp_dict, PyObject */
   (descrgetfunc)httpheaders_PyTypeObject_descrgetfunc,	/* tp_descr_get */
   0, 						/* tp_descr_set */
   offsetof(httpheaders_object, dict),		/* tp_dictoffset, Py_ssize_t */
   (initproc)httpheaders_PyTypeObject_initproc,	/* tp_init */
   0,						/* tp_alloc */
   httpheaders_PyTypeObject_newfunc,		/* tp_new */
   httpheaders_PyTypeObject_freefunc,		/* tp_free, Low-Level \
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

static PyObject* httpheaders_methods_body(httpheaders_object *self) 
{
    printf("Hola....\n");
    return (PyObject*)NULL;
}

static PyMethodDef httpheadersMethods[] = { 
                                              {"body", (PyCFunction)httpheaders_methods_body, METH_VARARGS, NULL}, 
                    					      {NULL, NULL, 0, NULL}
					                      };   

static struct PyModuleDef httpheadersmodule = {
    PyModuleDef_HEAD_INIT,
    "httpheaders",
    httpheaders_doc, 
    -1, 
    httpheadersMethods,
    NULL,
    NULL,
    NULL,
    NULL    
};


PyMODINIT_FUNC PyInit_httpheaders(void) 
{
   PyObject *module_httpheaders;

   if (PyType_Ready(&httpheaders) < 0)
   {
       return NULL;
   }
    
   /*module_httpheaders = Py_InitModule3("httpheaders", h ttpheadersMethods, HTTPHEADERS_VERSION_DOC);*/
   module_httpheaders = PyModule_Create(&httpheadersmodule);

   if (module_httpheaders == NULL)
   {
       return NULL;
   }

   PyModule_AddObject(module_httpheaders, "httpheaders", (PyObject *)&httpheaders);

   return module_httpheaders;
}	
