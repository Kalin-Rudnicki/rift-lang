#ifndef RIFT_SCOPE_H
#define RIFT_SCOPE_H

struct RiftScope
{
    const char* name;
    RiftObject * parent;
    RiftObjectNode* * childNamespaces;

    RiftObject* * definedClasses;
    RiftObject* * definedMethods;
    RiftObject* * definedVariables;
};

#endif