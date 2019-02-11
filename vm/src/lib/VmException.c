
#include "VmException.h"
#include <string.h>
#include <stdlib.h>

struct StackTrace
{
	const char* file;
	const char* function;
	const int lineNum;
	StackTrace * next;
}
struct VmException
{
	const char* condition;
	const char* type;
	const char* message;
	
	StackTrace * head;
}

StackTrace * StackTrace_new(const char* file, const char* function, const int lineNum)
{
	StackTrace * stackTrace = malloc(sizeof(StackTrace));
	
	if (file)
	{
		stackTrace->file = strdup(file);
	}
	else
	{
		stackTrace->file = NULL;
	}
	if (function)
	{
		stackTrace->function = strdup(function);
	}
	else
	{
		stackTrace->function = NULL;
	}
	stackTrace->lineNum = lineNum;
	stackTrace->next = NULL;
	
	return stackTrace;
}
void StackTrace_destroy(StackTrace * stackTrace)
{
	if (stackTrace == NULL)
	{
		return;
	}
	else
	{
		StackTrace_destroy(stackTrace->next);
	}
	
	if (stackTrace->file)
	{
		free(stackTrace->file);
	}
	if (stackTrace->function)
	{
		free(stackTrace->function);
	}
	free(stackTrace);
}

VmException * VmException_new(const char* condition, const char* type, const char* message, const char* file, const char* function, const int lineNum)
{
	VmException * vmException = malloc(sizeof(VmException));
	
	if (condition)
	{
		vmException->condition = strdup(condition);
	}
	else
	{
		vmException->condition = NULL;
	}
	if (type)
	{
		vmException->type = strdup(type);
	}
	else
	{
		vmException->type = NULL;
	}
	if (message)
	{
		vmException->message = strdup(message);
 	}
	else
	{
		vmException->message = NULL;
	}
	vmException->head = StackTrace_new(file, function, lineNum);
	
	return vmException;
}
void VmException_destroy(VmException * vmException)
{
	if (vmException == NULL)
	{
		printf("You need to use VmException properly... (%s:%d)\n", __FILE__, __LINE__);
		exit(1);
	}
	StackTrace_destroy(vmException->head);
	if (vmException->condition)
	{
		free(vmException->condition);
	}
	if (vmException->type)
	{
		free(vmException->type);
	}
	if (vmException->message)
	{
		free(vmException->message);
	}
	free(vmException);
}

void VmException_addTrace(VmException * vmException, const char* file, const char* function, const int lineNum)
{
	if (vmException == NULL)
	{
		printf("You need to use VmException properly... (%s:%d)\n", __FILE__, __LINE__);
		exit(1);
	}
	StackTrace * newTrace = StackTrace_new(file, function, lineNum);
	newTrace->next = vmException->head;
	vmException->head = newTrace;
}
void VmException_print(VmException * vmException)
{
	if (vmException == NULL)
	{
		printf("You need to use VmException properly... (%s:%d)\n", __FILE__, __LINE__);
		exit(1);
	}
	printf("TO-DO...\n");
}
void VmException_raise(VmException * vmException)
{
	VmException_print(vmException);
	printf("\n");
	exit(1);
}
