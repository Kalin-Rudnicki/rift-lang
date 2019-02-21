#ifndef RIFT_OBJECT_H
#define RIFT_OBJECT_H

#include "../lib/String.h"
#include "RiftClass.h"

// --- Structs ---

struct RiftObject;
typedef struct RiftObject RiftObject;

struct RiftObject
{
	RiftObject * klass;
	
	void * internal;
	
	
};

#endif