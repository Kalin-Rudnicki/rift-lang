#ifndef RIFT_VARIABLE_H
#define RIFT_VARIABLE_H

#include "Object.h"

struct RiftVariable
{
    const char* name;
    RiftObject * type;
    RiftObject * value;
};
typedef struct RiftVariable RiftVariable;

Exception * RiftVariable_new(RiftVariable ** variableAddr, const char* name, RiftObject * type);
Exception * RiftVariable_destroy(RiftVariable * variable);

#endif