#ifndef SYNTAX_ANALYZER
#define SYNTAX_ANALYZER

#include "../lexical_analyzer/lexical_analyzer.h"
#include "production_rules.h"

extern Token *parser_tokens;
extern int parser_index;

void syntax_analyzer(Token *tokens);

#endif