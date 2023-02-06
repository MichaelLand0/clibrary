#include <stdio.h>
#include <stdlib.h>
#include "include/fstrings.h"
#include <stdarg.h>
#include <string.h>



char lower(char c)
{
	
	if(c >=65 && c <=90)
	{
		c +=32;
		return c;
	}	
	else
		return c;
}

char upper(char c)
{
	if(c >=97 && c <=122)
	{
		c -=32;
		return c;
	}	
	else
		return c;
}
//converting datatypes to strings







void int_to_str(char * str, int num)
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



void float_to_str(char *str, double num)
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
		int_to_str(buffer,i);
		fstrcat(str,buffer);
	}	
	else
	{
		int ipart= (int)num;
		double fpart= num - (double)ipart;
		fpart = fpart*1000000;
		
		int intfpart= (int)fpart;
		int_to_str(buffer,ipart);
		int_to_str(buffer1, intfpart);
		str[0]='\0';
		fstrcat(str,buffer);	
		fstrcat(str,".");	
		fstrcat(str,buffer1);	
	}
}




//string comparisons



int fis_in_str(char *str1, char * str2)
{
	int match=0;
	int temp=0;
	int j=0;
	for(int i=0; str1[i]!='\0'; i++)
	{
		if(str1[i] == str2[j])
		{	
			match =1;
			temp=i;
			while(str2[j]!='\0')
			{
				if(str1[temp]!=str2[j])
				{
					match =0;
					break;
				}
				temp +=1;
				j+=1;
			}
		if(match==1)
			return 1;
		j=0;
		}
	
	}
	return 0;
}





//string manipulation


void reverse_string(char * string)
{
	int j,i,len;
	len = fstringlen(string);
	j =len -1;
	char temp;
	for(i=0; i < j; i++ )
	{
		temp =string[i];
		string[i] = string[j];
		string[j] = temp;
		j--;
	}
}



void strip_extra_whitespace(char * string)
{
	int i,j, len;
	
	len = fstringlen(string);

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



void fstrcopy(char * buf, const char *str)
{
	int i;
	for(i=0; str[i]!='\0'; i++)
		buf[i]=str[i];
	buf[i]='\0';
}


void fstrcat(char *string1, char *string2)
{
	int i=0;
	int len =fstringlen(string1);
		while(string2[i]!='\0')
		{
			string1[len + i]=string2[i];
		 i++;	
		}
		string1[len +i]='\0';
	return;
}


void fgetstring(char *buffer, int size)
{	
	char c;
	int i=0;
	while(i <size)
	{
		if((c=fgetchar())!='\n')
			buffer[i]=c;
		else
			break;	
	i++;
	}	
	buffer[i]='\0';
}




int fstringlen(const char *string)
{
		int i=0;
		for(i=0; string[i]!='\0'; i++);
		
		return i;
}

char fgetchar()
{
	char c=fgetc(stdin);
	return c;
}




