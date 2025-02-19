#include "production_rules_varaibles.h"

const char *token_name_array_prb[] = {
    "LBRACKET",  // TOKEN_LBRACKET
    "RBRACKET",  // TOKEN_RBRACKET
    "LPAREN",    // TOKEN_LPAREN
    "RPAREN",    // TOKEN_RPAREN
    "LBRACE",    // TOKEN_LBRACE
    "RBRACE",    // TOKEN_RBRACE
    "COMMA",     // TOKEN_COMMA
    "COLON",     // TOKEN_COLON
    "QUESTION",  // TOKEN_QUESTION
    "SEMICOLON", // TOKEN_SEMICOLON
    "ADD",       // TOKEN_ADD
    "MINUS",     // TOKEN_MINUS
    "MULTIPLY",  // TOKEN_MULTIPLY
    "DIVIDE",    // TOKEN_DIVIDE
    "POWER",     // TOKEN_POWER
    "MODULO",    // TOKEN_MODULO
    "EQUAL",     // TOKEN_EQUAL
    "DUALPLUS",  // TOKEN_DUALPLUS
    "DUALMINUS", // TOKEN_DUALMINUS
    "GREATER",   // TOKEN_GREATER
    "LESSER",    // TOKEN_LESSER
    "EQUALITY",  // TOKEN_EQUALITY
    "NOT",       // TOKEN_NOT
    "GRTREQL",   // TOKEN_GRTREQL
    "LESREQL",   // TOKEN_LESREQL
    "NOTEQUAL",  // TOKEN_NOTEQUAL
    "AND",       // TOKEN_AND
    "OR",        // TOKEN_OR
    "PLUSEQL",   // TOKEN_PLUSEQL
    "MINUSEQL",  // TOKEN_MINUSEQL
    "MULEQL",    // TOKEN_MULEQL
    "DIVEQL",    // TOKEN_DIVEQL
    "HASH",      // TOKEN_HASH
    "DOT",       // TOKEN_DOT
    "TILDE",     // TOKEN_TILDE
    "BOOL",      // TOKEN_BOOL
    "CASE",      // TOKEN_CASE
    "CONTINUE",  // TOKEN_CONTINUE
    "DEFAULT",   // TOKEN_DEFAULT
    "DEFINE",    // TOKEN_DEFINE
    "DO",        // TOKEN_DO
    "ELSE",      // TOKEN_ELSE
    "FOR",       // TOKEN_FOR
    "IF",        // TOKEN_IF
    "INCLUDE",   // TOKEN_INCLUDE
    "INT",       // TOKEN_INT
    "REAL",      // TOKEN_REAL
    "RECORD",    // TOKEN_RECORD
    "RETURN",    // TOKEN_RETURN
    "STATIC",    // TOKEN_STATTIC
    "STRING",    // TOKEN_STRING
    "VOID",      // TOKEN_VOID
    "WHILE",     // TOKEN_WHILE
    "TRUE",      // TOKEN_TRUE
    "FALSE",     // TOKEN_FALSE
    "INTLTR",    // TOKEN_INTLTR
    "REALLTR",   // TOKEN_REALLTR
    "STRLTR",    // TOKEN_STRLTR
    "ID",        // TOKEN_ID
    "EOF",       // TOKEN_EOF
    "ERROR"      // TOKEN_ERROR
};

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
                        token_name_array_prb[parser_tokens[parser_index].type]);
                exit(EXIT_FAILURE);
            }
            match(TOKEN_RBRACKET);
        }
    }
    else
    {
        fprintf(stderr, "Syntax error: Expected identifier in variable declaration, found %s\n",
                token_name_array_prb[parser_tokens[parser_index].type]);
        exit(EXIT_FAILURE);
    }
}