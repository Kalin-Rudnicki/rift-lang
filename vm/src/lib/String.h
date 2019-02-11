
struct String
{
	unsigned int length;
	const char* chars;
}

struct StringBuilderNode
{
	String * string;
	struct StringBuilderNode * next;
}

struct StringBuilder
{
	unsigned int length;
	StringBuilderNode head;
	StringBuilderNode tail;
}

String * String_new(const char* chars);
String * String_copy(String * string);
void String_destroy(String * string);


