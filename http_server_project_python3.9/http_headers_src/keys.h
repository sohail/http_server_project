/* src/keys.h 
   Written by, Sohail Qayum Malik */

#include <Python.h>
#include <windows.h>
#include <mmsystem.h>

#include <structmember.h>

#ifndef 	REGEDIT_KEYS_H
#define	REGEDIT_KEYS_H

/* Will go in keys_object::type. The numeric equivalent of what ever is in keys_object::type_str */
#define 	ORDINARY_CHARACTER_N	1

/* Will go/(be copied) in keys_object::type_str and its numeric equivalent is in keys_object::type */
#define		ORDINARY_CHARACTER	"ordinary_character"

/* The syntactic sugar "print str(httheaders_obj)" returns and print the request/reply body. Internally(implementation of str()) it uses this(the one in the following macro) request/reply entity to get the size of message body.
Change the name of this macro as per the version of HTTP being used */
#define		CONTENT_LENGTH		"Content-Length"

PyDoc_STRVAR(keys_doc, "keys\n");

typedef struct {

   PyObject_HEAD

   /* type specific members go here */
   /* size_t, unsigned int, signed counter part is ssize_t, [-Wformat=] */
   /*Py_ssize_t*/ size_t index; /* Dict is unorderd, we need an order and we need dict. We'll keep the order by evaluating a key the lower idx means the value should be used earlier than any other value which comes later in terms of idx. Programmers we just push the ugly around */
   /*const*/ int type; /* Type of the key in number */
   /*const*/ char *type_str; /* Name of the key */

} keys_object;

#endif
