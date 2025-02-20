#include "production_rules.h"

void parse_varDecl()
{
    parse_typeSpec();
    parse_varDeclList();
    match(TOKEN_SEMICOLON);
}

void parse_varDeclList()
{
    do
    {
        parse_varDeclInit();
        if (parser_tokens[parser_index].type == TOKEN_COMMA)
            match(TOKEN_COMMA);
        else
            break;
    } while (1);
}

void parse_varDeclInit()
{
    parse_varDeclId();
    if (parser_tokens[parser_index].type == TOKEN_EQUAL)
    {
        match(TOKEN_EQUAL);
        parse_exp();
    }
}

void parse_varDeclId()
{
    if (parser_tokens[parser_index].type == TOKEN_ID)
    {
        match(TOKEN_ID);
        if (parser_tokens[parser_index].type == TOKEN_LBRACKET)
        {
            match(TOKEN_LBRACKET);
            if (parser_tokens[parser_index].type == TOKEN_INTLTR)
                match(TOKEN_INTLTR);
            else
            {
                fprintf(stderr, "Syntax error: Expected numeric constant inside array declaration, found %s\n",
                        parser_tokens[parser_index].lexeme);
                exit(EXIT_FAILURE);
            }
            match(TOKEN_RBRACKET);
        }
    }
    else
    {
        fprintf(stderr, "Syntax error: Expected identifier in variable declaration, found %s\n",
                parser_tokens[parser_index].lexeme);
        exit(EXIT_FAILURE);
    }
}