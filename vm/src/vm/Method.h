#ifndef RIFT_METHOD_H
#define RIFT_METHOD_H

struct RiftMethod
{
    int type; // native or not
    union methodLoc
    {
        Exception * (*nativeMethod)(int, RiftObject* *, int, RiftObject*, int RiftObject*);
        Instruction * riftInstruction;
    }
};
typedef struct RiftMethod RiftMethod;

#endif