#include "string_datatype.h"

string create_string(const char *initial_value)
{
    string new_str = (string)malloc(strlen(initial_value) + 1);
    if (new_str == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    strcpy(new_str, initial_value);
    return new_str;
}

string concat_string(string str1, const char *str2)
{
    size_t new_len = strlen(str1) + strlen(str2) + 1;
    string result = (string)realloc(str1, new_len);
    if (result == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    strcat(result, str2);
    return result;
}

string concat_character(string str1, char ch) {
    char temp[2] = {ch, '\0'};
    return concat_string(str1, temp);
}

size_t string_length(string str)
{
    return strlen(str);
}

void free_string(string str)
{
    free(str);
}