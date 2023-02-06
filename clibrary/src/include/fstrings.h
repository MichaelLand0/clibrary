#ifndef fstrings_h
#define fstrings_h


//how to pass multidementinol arrays? 
void test_strings();



char upper(char c);
char lower(char c);


//conversions
void float_to_str(char *str, double num);
void int_to_str(char * str, int num);


//string manipulation

void reverse_string(char * string);

void strip_extra_whitespace(char * str);

void fstrcopy(char * buf, const char *str);

int fis_in_str(char *str1, char * str2);

void fstrcat(char *string1, char *string2);

void fgetstring(char *buffer, int size);

int fstringlen(const char *string);

char fgetchar();

#endif



