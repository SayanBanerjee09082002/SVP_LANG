#include "production_rules.h"

const char *token_name_array[] = {
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

void match(TokenType expected)
{
    if (parser_tokens[parser_index].type == expected)
        parser_index++;
    else
    {
        fprintf(stderr, "Syntax error at token %d: Expected %s, found %s\n",
                parser_index, token_name_array[expected], token_name_array[parser_tokens[parser_index].type]);
        exit(EXIT_FAILURE);
    }
}

void parse_declList()
{
    while (parser_tokens[parser_index].type != TOKEN_EOF)
        parse_decl();
}

void parse_decl()
{
    if (parser_tokens[parser_index].type == TOKEN_INT ||
        parser_tokens[parser_index].type == TOKEN_REAL ||
        parser_tokens[parser_index].type == TOKEN_STRING ||
        parser_tokens[parser_index].type == TOKEN_BOOL)
    {
        TokenType type = parser_tokens[parser_index].type;
        match(type);
        match(TOKEN_ID);

        if (parser_tokens[parser_index].type == TOKEN_LPAREN)
            parse_funDecl();
        else
            parse_varDecl();
    }
    else
    {
        fprintf(stderr, "Syntax error: Expected declaration %s\n", token_name_array[parser_tokens[parser_index].type]);
        exit(EXIT_FAILURE);
    }
}

void parse_typeSpec()
{
    if (parser_tokens[parser_index].type == TOKEN_INT ||
        parser_tokens[parser_index].type == TOKEN_REAL ||
        parser_tokens[parser_index].type == TOKEN_STRING ||
        parser_tokens[parser_index].type == TOKEN_BOOL)
        match(parser_tokens[parser_index].type);
    else
    {
        fprintf(stderr, "Syntax error: Expected type specifier, found %d\n", parser_tokens[parser_index].type);
        exit(EXIT_FAILURE);
    }
}