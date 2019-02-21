#ifndef VM_STRING_H
#define VM_STRING_H

#include "VmException.h"

// Structs

struct String
{
	unsigned int length;
	char* chars;
};
typedef struct String String;

struct StringBuilder;
typedef struct StringBuilder StringBuilder;

// Functions

// String
VmException * String_new(String ** stringAddr, const char* chars);
VmException * String_destroy(String * string);

VmException * String_copy(String ** stringAddr, String * string);
VmException * String_hash(String * string, int * hashAddr);

// StringBuilder
VmException * StringBuilder_new(StringBuilder ** builderAddr);
VmException * StringBuilder_destroy(StringBuilder * builder);

VmException * StringBuilder_prepend(StringBuilder * builder, String * string);
VmException * StringBuilder_prependChars(StringBuilder * builder, const char* chars);
VmException * StringBuilder_append(StringBuilder * builder, String * string);
VmException * StringBuilder_appendChars(StringBuilder * builder, const char* chars);

VmException * StringBuilder_build(String ** stringAddr, StringBuilder * builder);

#endif