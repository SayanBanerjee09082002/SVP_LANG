#ifndef KEYWORD_ANALYZER
#define KEYWORD_ANALYZER

#include <stdlib.h>
#include "../tokens.h"

#define KEYWORD_TABLE_SIZE 32

typedef struct KeywordEntry {
    const char *keyword;
    TokenType type;
    struct KeywordEntry *next;
} KeywordEntry;

extern KeywordEntry *keyword_table[KEYWORD_TABLE_SIZE];

void initialize_keyword_table();
Token keyword_analyzer(FILE *input, char first_char);

#endif