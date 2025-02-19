#ifndef PRODUCTION_RULES
#define PRODUCTION_RULES

#include "syntax_analyzer.h"
#include "production_rules_varaibles.h"
#include "production_rules_expressions.h"
#include "production_rule_functions.h"
#include "production_rules_statements.h"

void match(TokenType expected);
void parse_declList();
void parse_decl();
void parse_typeSpec();

#endif