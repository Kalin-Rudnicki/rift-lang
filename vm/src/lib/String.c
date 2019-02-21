
#include "String.h"
#include <stdlib.h>

// --- Structs ---

struct StringBuilderNode;
typedef struct StringBuilderNode StringBuilderNode;

struct StringBuilderNode
{
	String * string;
	StringBuilderNode * next;
};

struct StringBuilder
{
	unsigned int totalLength;
	StringBuilderNode * head;
	StringBuilderNode * tail;
};

// --- Functions ---

// String
VmException * String_new(String ** stringAddr, const char* chars)
{
	CHECK_NULL(stringAddr)
	
	if (chars)
	{
		String * string = malloc(sizeof(String));
		string->length = 0;
		
		while (chars[string->length] != '\0')
		{
			(string->length)++;
		}
		
		string->chars = malloc(sizeof(char) * ((string->length) + 1));
		for (int i = 0; i < string->length; i++)
		{
			string->chars[i] = chars[i];
		}
		string->chars[string->length] = '\0';
		
		*stringAddr = string;
	}
	else
	{
		*stringAddr = NULL;
	}
	
	return NULL;
}
VmException * String_destroy(String * string)
{
	CHECK_NULL(string)
	
	free(string->chars);
	free(string);
	
	return NULL;
}

VmException * String_copy(String ** stringAddr, String * string)
{
	CHECK_NULL(stringAddr)
	
	if (string)
	{
		String * newString = malloc(sizeof(String));
		
		newString->length = string->length;
		newString->chars = malloc(sizeof(char) * ((string->length) + 1));
		for (int i = 0; i < string->length; i++)
		{
			newString->chars[i] = string->chars[i];
		}
		newString->chars[newString->length] = '\0';
		
		*stringAddr = newString;
	}
	else
	{
		*stringAddr = NULL;
	}
	
	return NULL;
}

VmException * String_hash(String * string, unsigned int * hashAddr)
{
	CHECK_NULL(hashAddr)
	
	int hash = 0;
	if (string)
	{
		for (int i = 0; i < string->length; i++)
		{
			hash = hash * 31 + string->chars[i];
		}
	}
	*hashAddr = hash;
	
	return NULL;
}

// StringBuilderNode
VmException * StringBuilderNode_new(StringBuilderNode ** nodeAddr, String * string)
{
	CHECK_NULL(nodeAddr)
	CHECK_NULL(string)
	
	StringBuilderNode * node = malloc(sizeof(StringBuilderNode));
	PASS(String_copy(&(node->string), string))
	node->next = NULL;
	
	*nodeAddr = node;
	
	return NULL;
}
VmException * StringBuilderNode_destroy(StringBuilderNode * node)
{
	CHECK_NULL(node)
	
	if (node->next)
	{
		PASS(StringBuilderNode_destroy(node->next))
	}
	if (node->string)
	{
		PASS(String_destroy(node->string))
	}
	free(node);
	
	return NULL;
}

// StringBuilder
VmException * StringBuilder_new(StringBuilder ** builderAddr)
{
	CHECK_NULL(builderAddr)
	
	StringBuilder * builder = malloc(sizeof(StringBuilder));
	
	builder->totalLength = 0;
	PASS(StringBuilderNode_new(&(builder->head), NULL))
	PASS(StringBuilderNode_new(&(builder->tail), NULL))
	builder->tail->next = builder->head;
	
	*builderAddr = builder;
	
	return NULL;
}
VmException * StringBuilder_destroy(StringBuilder * builder)
{
	CHECK_NULL(builder)
	
	builder->tail->next = NULL;
	PASS(StringBuilderNode_destroy(builder->head))
	PASS(StringBuilderNode_destroy(builder->tail))
	free(builder);
	
	return NULL;
}

VmException * StringBuilder_prepend(StringBuilder * builder, String * string)
{
	CHECK_NULL(builder)
	CHECK_NULL(string)
	
	StringBuilderNode * node;
	PASS(StringBuilderNode_new(&node, string))
	
	node->next = builder->head->next;
	builder->head->next = node;
	if (builder->tail->next == builder->head)
	{
		builder->tail->next = node;
	}
	(builder->totalLength) += string->length;
	
	return NULL;
}
VmException * StringBuilder_prependChars(StringBuilder * builder, const char* chars)
{
	String * string;
	PASS(String_new(&string, chars))
	PASS(StringBuilder_prepend(builder, string));
	
	return NULL;
}
VmException * StringBuilder_append(StringBuilder * builder, String * string)
{
	CHECK_NULL(builder)
	CHECK_NULL(string)
	
	StringBuilderNode * node;
	PASS(StringBuilderNode_new(&node, string))
	
	builder->tail->next->next = node;
	builder->tail->next = node;
	(builder->totalLength) += string->length;
	
	return NULL;
}
VmException * StringBuilder_appendChars(StringBuilder * builder, const char* chars)
{
	String * string;
	PASS(String_new(&string, chars))
	PASS(StringBuilder_append(builder, string));
	
	return NULL;
}

VmException * StringBuilder_build(String ** stringAddr, StringBuilder * builder)
{
	CHECK_NULL(stringAddr)
	CHECK_NULL(builder)
	
	String * string;
	string->length = builder->totalLength;
	string->chars = malloc(sizeof(char) * ((string->length) + 1));
	int idx = 0;
	for (StringBuilderNode * node = builder->head->next; node != NULL; node = node->next)
	{
		for (int i = 0; i < node->string->length; i++)
		{
			string->chars[idx + i] = node->string->chars[i];
		}
		idx += node->string->length;
	}
	string->chars[string->length] = '\0';
	
	return NULL;
}
