#ifndef RIFT_VM_EXCEPTION_H
#define RIFT_VM_EXCEPTION_H

#define CHECK(condition, error, message)

#define CHECK_NULL(element)

struct StackTrace;
typedef struct StackTrace StackTrace;

struct VmException;
typedef struct VmException VmException;

StackTrace * StackTrace_new(const char* file, const char* function, const int lineNum);
void StackTrace_destroy(StackTrace * stackTrace);

VmException * VmException_new(const char* condition, const char* type, const char* message, const char* file, const char* function, const int lineNum);
void VmException_destroy(VmException * vmException);

void VmException_addTrace(VmException * vmException, const char* file, const char* function, const int lineNum);
void VmException_print(VmException * vmException);
void VmException_raise(VmException * vmException);

#endif