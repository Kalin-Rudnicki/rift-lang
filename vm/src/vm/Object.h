#ifndef RIFT_OBJECT_H
#define RIFT_OBJECT_H

// --- Structs ---
struct RiftObjectNode;
typedef struct RiftObjectNode RiftObjectNode;

struct RiftObject;
typedef struct RiftObject RiftObject;

struct RiftObjectNode
{
    RiftObject * object;
    RiftObjectNode * next;
};

struct RiftObject
{

    RiftObject * klass;

    RiftObject* * generics;

    unsigned int referencedCount;

    void * internal;

    // All definedInstanceVariables must also be in metaInstanceVariables
    RiftObject* * definedInstanceVariables;
    unsigned int metaInstanceVariablesSize;
    RiftObjectNode* * metaInstanceVariables;

};

// --- Functions ---

// RiftObjectNode
Exception * RiftObjectNode_new(RiftObjectNode ** objectNodeAddr, RiftObject * object);
Exception * RiftObjectNode_destroy(RiftObjectNode * objectNode);

// RiftObject
Exception * RiftObject_new(RiftObject ** objectAddr);
Exception * RiftObject_destroy(RiftObject * object);

#endif