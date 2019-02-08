#ifndef RIFT_CLASS_H
#define RIFT_CLASS_H

#include "Object.h"

struct RiftClass
{
    const char* name;
    RiftObject* * superclasses;
    RiftObject* * innerClasses;
    RiftObjectNode * instances;

    RiftObject* * definedClassMethods;
    RiftObject* * definedClassVariables;
    RiftObject* * definedInstanceMethods;

    RiftObjectNode* * metaClassMethods;
    RiftObjectNode* * metaClassVariables;
    RiftObjectNode* * metaInstanceMethods;

    RiftVariable* * definedInstanceVariables; // Used when instantiating a new object
};

#endif