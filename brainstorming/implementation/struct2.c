
struct Class;
typedef struct Class Class;

struct Object;
typedef struct Object Object;

struct ObjectNode;
typedef struct ObjectNode ObjectNode;

// Nodes
struct ObjectNode
{
	Object * object;
	ObjectNode * prev;
	ObjectNode * next;
}

// Other
struct Namespace
{
	const char* name;
	Object * parent;
	ObjectNode * children;
	
	Object* * definedClasses;
	Object* * definedVariables;
	Object* * definedMethods;
	
	ObjectNode* * metaClasses;
	ObjectNode* * metaVariables;
	ObjectNode* * metaMethods;
}

struct Class
{
	const char* name;
	Object* * superclasses;
	ObjectNode * instances;
	
	Object* * definedClassVariables;
	Object* * definedClassMethods;
	Object* * definedInstanceMethods;
	
	// Probably end up making these a hash, default size 1 (much more of a linked list),
	// then if say (3-5) get added, actually start increasing the size
	ObjectNode* * metaClassVariables;
	ObjectNode* * metaClassMethods;
	ObjectNode* * metaInstanceMethods;
}

struct Object
{
	Object * klass;
	Object* * generics;
	int referencedCount;
	void * internal;
	
	Object* definedInstanceVariables;
	ObjectNode* * metaInstanceVariables;
}
