#ifndef LEXICAL_ANALYZER
#define LEXICAL_ANAYZER

#include <stdlib.h>
#include <stdbool.h>
#include "keyword_analyzer.h"
#include "operator_analyzer.h"
#include "../tokens.h"

Token get_next_token(FILE *input);
Token *lexical_analyzer(FILE *input);

#endif