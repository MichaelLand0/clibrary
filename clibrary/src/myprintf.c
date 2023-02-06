#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>
#include <string.h>
#include "include/myprintf.h"

typedef struct
{
	char * str;
	unsigned int count;
	unsigned int size;
}buf;


void myputc(const char c)
{
	write(1,&c,1);
}
void myprint(const char * s)
{
	while(*s != '\0')
	{	
		myputc(*s);	
		s++;
	}
}


/*helper functions*/
void fint_to_str(char * str, int num)
{
	int i, len=0, rem, n;
	n= num;
	while(n!=0)
	{
		len++;
		n = n / 10;
	}
	for(i=0; i<len; i++)
	{
		rem = num % 10;
		num = num / 10;
		str[len -(i +1)] = rem +'0';
	}
	str[len]='\0';
}

void ffloat_to_str(char *str, double num)
{
	char buffer[400];
	char buffer1[400];
	double n = num;
	if(n <= 0.9)
	{ 
		str[0]='0';
		str[1]='.';
		str[2]='\0';
		n = n * 1000000;
		int i= (int) n;
		fint_to_str(buffer,i);
		strcat(str,buffer);
	}	
	else
	{
		int ipart= (int)num;
		double fpart= num - (double)ipart;
		fpart = fpart*1000000;
		int intfpart= (int)fpart;
		fint_to_str(buffer,ipart);
		fint_to_str(buffer1, intfpart);
		str[0]='\0';
		strcat(str,buffer);	
		strcat(str,".");	
		strcat(str,buffer1);	
	}
}

void resize(int i, buf*b)
{
	if(i ==1)
	{
		b->size = 50;
		b->count = 0;
		b->str = malloc(b->size *sizeof(char));
	}
	else
	{
		b->size *=2;
		b->str =realloc(b->str, b->size * sizeof(char));	
	}
}


/*append functions*/
void append(char c, buf*b)
{
	if(b->str ==NULL)
		resize(1,b);	
	else if(b->count == b->size-2)
		resize(0,b);	
	b->str[b->count] = c;
	b->count++;
}

void append_str(char * arg, buf *b)
{
	while(*arg != '\0')
	{
			append(*arg,b);	
			arg++;
	}
	return;
}

void append_int(int i, buf *b)
{
	char buf[200];
	fint_to_str(buf,i);
	append_str(buf,b);	
}

void append_double(double i, buf *b)
{
	char buf[200];
	ffloat_to_str(buf,i);
	append_str(buf,b);	
}


/*parse functions*/
void parse_arg(va_list list, buf *b,char c)
{
	void * arg;
	switch(c)
	{
					case 's':
					arg = va_arg(list,char*);
					append_str((char*)arg,b);	
					break;
					case 'i':
						int i = va_arg(list,int);
						append_int(i,b);
					break;
					case 'f':
						double j = va_arg(list,double);
						append_double(j,b);
					break;
					case '%':
						append(c,b);
					break;
	}
}

void parse(const char* format, va_list list, buf* b)
{
	while(*format != '\0')
	{
		if(*format == '%')
		{
			format++;
			parse_arg(list,b,*format);
		}
			else
			append(*format,b);	
	format++;
	}
	b->str[b->count] ='\0';
}


/*main function/init */
void mprintf(const char * format, ...)
{
	buf * b =malloc(sizeof(buf));
	void * arg;				
	va_list list;
	va_start(list, format);
	parse(format, list, b);
	myprint(b->str);
	va_end(list);
	free(b->str);
	free(b);
}


void msprintf(char *buff,int size, const char * format, ...)
{
	buf * b = malloc(sizeof(buf));
	void * arg;				
	va_list list;
	va_start(list, format);
	parse(format, list, b);
	
	if(strlen(b->str)> size)	
		myprint("error\n");
	else
		strcpy(buff,b->str);
	va_end(list);
	free(b->str);
	free(b);
}
