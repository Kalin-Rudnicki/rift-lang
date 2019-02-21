#ifndef RIFT_VM_EXCEPTION_H
#define RIFT_VM_EXCEPTION_H

#define CHECK(condition, error, message)\
	if (condition)\
	{\
		return VmException_new(#condition, error, message, __FILE__, __FUNCTION__, __LINE__);\
	}

#define CHECK_NULL(element) CHECK(element == NULL, "IllegalNull", #element " can not be NULL")

#define PASS(call)\
	{\
		VmException * exception = call;\
		if (exception)\
		{\
			VmException_addTrace(exception, __FILE__, __FUNCTION__, __LINE__);\
			return exception;\
		}\
	}

#define THROW(call)\
	{\
		VmException * exception = call;\
		if (exception)\
		{\
			VmException_raise(exception);\
		}\
	}

// --- Structs ---

struct VmException;
typedef struct VmException VmException;

// --- Functions ---

// VmException
VmException * VmException_new(const char* condition, const char* type, const char* message, const char* file, const char* function, const int lineNum);
void VmException_destroy(VmException * vmException);

void VmException_addTrace(VmException * vmException, const char* file, const char* function, const int lineNum);
void VmException_print(VmException * vmException);
void VmException_raise(VmException * vmException);

#endif