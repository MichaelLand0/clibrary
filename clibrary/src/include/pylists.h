#ifndef pylists_h
#define pylists_h


typedef struct pyobject
{
	char type;
	char * string;
	char character;
	int intiger;
	double floatf;
}pyobject;

typedef struct pylist
{
	pyobject * items;
	int count;
	int copasity;
}pylist;


void test_pylists();





#endif
