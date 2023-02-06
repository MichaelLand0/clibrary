#include "include/pylists.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


void fstrip_extra_whitespace(char * string)
{
	int i,j, len;
	
	len = strlen(string);

	for(i=0; i<len; i++)
	{
		if(string[i]==' ' && string[i+1] ==' ')
		{
			for(j=i; j< len-1; j++)
			{
				string[j] = string[j+1];
			}
			len--;
			string[len] = '\0';
			i = 0;
		}
	}	
}

void resize_list(pylist * list)
{
	list->copasity *=2;
	list->items = realloc(list->items, list->copasity * sizeof(pyobject));
}



void list_append_str(pylist * list, char * string) 
{	
	
	if(list->count == list->copasity-2)
		resize_list(list);	
	int i= list->count;
	list->items[i].type='s';
	list->items[i].string = malloc(strlen(string)* sizeof(char));
	strcpy(list->items[i].string, string);
	list->count++;
}

void list_append_char(pylist * list, char charf)
{	
	if(list->count == list->copasity-2)
		resize_list(list);	
	int i= list->count;
	list->items[i].type='c';
	list->items[i].character = charf;
	list->count++;
}
void list_append_int(pylist * list, int input)
{	
	if(list->count == list->copasity-2)
		resize_list(list);	
	int i= list->count;
	list->items[i].type='i';
	list->items[i].intiger = input;
	list->count++;
}

void list_append_float(pylist * list, double input)
{	
	if(list->count == list->copasity-2)
		resize_list(list);	
	int i= list->count;
	list->items[i].type='f';
	list->items[i].floatf = input;
	list->count++;
}





int split_string(pylist *list, char * string)
{
	int f = strlen(string);	
	char stringbuf[f];
	strcpy(stringbuf,string);
	fstrip_extra_whitespace(stringbuf);
	int i,j=0;
	char buffer[400];
	for(i =0; stringbuf[i] !='\0'; i++)
	{
		if(stringbuf[i] ==' ')
			continue;
		else
		{
				buffer[j]=stringbuf[i];
				j++;
				if(stringbuf[i+1] ==' ' || stringbuf[i+1] =='\0')
				{
					buffer[j]='\0';
					list_append_str(list, buffer);
					j=0;
				}
		}
	}
}






void end_pylist(pylist * list)
{
	int i;
	for(i=0; i<list->count; i++)
	{
		if(list->items[i].type='s')
			free(list->items[i].string);
	}	
	free(list->items);
	free(list);
}


pylist * init_list()
{
	pylist *temp =NULL; temp = malloc(sizeof(pylist));
	temp->copasity=20;
	temp->count=0;
	temp->items = (pyobject*) malloc(temp->copasity * sizeof(pyobject));
	if( temp->items != (void*)0 )
	{
		return temp;
	}
	else
		printf("error");	
	return temp;
}



void print_pylist(pylist * list)
{
	printf("[");			
	for(int i =0; i < list->count ; i++)
	{
		if(list->items[i].type == 's')
			printf("\'%s\'",list->items[i].string);
		if(list->items[i].type == 'i')
			printf("%i",list->items[i].intiger);
		if(list->items[i].type == 'f')
			printf("%f",list->items[i].floatf);
		if(list->items[i].type == 'c')
			printf("\'%c\'",list->items[i].character);
		if(i !=list->count -1) 
			printf(", ");			
	}
	printf("]\n");			
	return;
}






