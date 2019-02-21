
#include "VmException.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

// --- Structs ---

struct VmStackTrace;
typedef struct VmStackTrace VmStackTrace;

struct VmStackTrace
{
	char* file;
	char* function;
	int lineNum;
	VmStackTrace * next;
};
struct VmException
{
	char* condition;
	char* type;
	char* message;
	
	VmStackTrace * head;
};

// --- Functions ---

// VmStackTrace
VmStackTrace * VmStackTrace_new(const char* file, const char* function, const int lineNum)
{
	VmStackTrace * stackTrace = malloc(sizeof(VmStackTrace));
	
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
void VmStackTrace_destroy(VmStackTrace * stackTrace)
{
	if (stackTrace == NULL)
	{
		return;
	}
	else
	{
		VmStackTrace_destroy(stackTrace->next);
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

// VmException
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
	vmException->head = VmStackTrace_new(file, function, lineNum);
	
	return vmException;
}
void VmException_destroy(VmException * vmException)
{
	if (vmException == NULL)
	{
		printf("You need to use VmException properly... (%s:%d)\n", __FILE__, __LINE__);
		exit(1);
	}
	VmStackTrace_destroy(vmException->head);
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
	VmStackTrace * newTrace = VmStackTrace_new(file, function, lineNum);
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
	
	int maxFile = 0;
	for (VmStackTrace * trace = vmException->head; trace != NULL; trace = trace->next)
	{
		int currentFile = strlen(trace->file);
		if (currentFile > maxFile)
		{
			maxFile = currentFile;
		}
	}
	
	printf("[\x1b[31mERROR\x1b[0m]: (%s) %s\n", vmException->type, vmException->message);
	printf("    %*s: \x1b[31m%s\x1b[0m\n", maxFile, "condition", vmException->condition);
	for (VmStackTrace * trace = vmException->head; trace != NULL; trace = trace->next)
	{
		printf("    \x1b[36m%*s\x1b[0m:\x1b[34m%-5d\x1b[0m %4s \x1b[32m%s\x1b[0m\n", maxFile, trace->file, trace->lineNum, trace->next == NULL ? "from" : "in", trace->function);
	}
}
void VmException_raise(VmException * vmException)
{
	VmException_print(vmException);
	printf("\n");
	exit(1);
}
