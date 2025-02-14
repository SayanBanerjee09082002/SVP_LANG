#ifndef STRING_DT
#define STRING_DT

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef char *string;

string create_string(const char *initial_value);
string concat_string(string str1, const char *str2);
string concat_character(string str1, char ch);
size_t string_length(string str);
void free_string(string str);

#endif