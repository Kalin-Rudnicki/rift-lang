
#include "struct2.c"

// Circular loop?
/*
Object.class = Class
Class.superclass = [Object]
*/

static Class * _ObjectClass = malloc(sizeof(Class));
_ObjectClass->name = "Object";

static Class * _ClassClass = malloc(sizeof(Class));
_ClassClass->name = "Class";
_ClassClass->superclasses = malloc(sizeof(Object *) * 2);


static Object * _Class = malloc(sizeof(Object));
_Class->klass = _Class;
_Class->generics = malloc(sizeof(Object *));
_Class->generics[0] = NULL;
_Class->referencedCount = -1;
