#ifndef RIFT_CLASS_H
#define RIFT_CLASS_H

#include "RiftObject.h"
#include "../lib/String.h"

struct RiftClass
{
	String * name;
	
	RiftObject* * superClasses;
	
};

#endif