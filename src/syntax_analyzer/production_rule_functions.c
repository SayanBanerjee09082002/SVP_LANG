#include "production_rule_functions.h"

void parse_funDecl()
{
    match(TOKEN_LPAREN);
    parse_parms();
    match(TOKEN_RPAREN);
    match(TOKEN_LBRACE);
    parse_stmtList();
    match(TOKEN_RBRACE);
}

void parse_parms()
{
    if (parser_tokens[parser_index].type == TOKEN_INT ||
        parser_tokens[parser_index].type == TOKEN_REAL ||
        parser_tokens[parser_index].type == TOKEN_STRING ||
        parser_tokens[parser_index].type == TOKEN_BOOL)
        parse_parmList();
}

void parse_parmList()
{
    do
    {
        parse_parmTypeList();
        if (parser_tokens[parser_index].type == TOKEN_COMMA)
            match(TOKEN_COMMA);
    } while (parser_tokens[parser_index].type != TOKEN_RPAREN);
}

void parse_parmTypeList()
{
    parse_typeSpec();
    parse_parmIdList();
}

void parse_parmIdList()
{
    while (1)
    {
        match(TOKEN_ID);
        if (parser_tokens[parser_index].type == TOKEN_COMMA)
            match(TOKEN_COMMA);
        else
            break;
    }
}