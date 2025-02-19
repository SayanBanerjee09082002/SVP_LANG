#include "production_rules_statements.h"

void parse_stmtList()
{
    while (parser_tokens[parser_index].type != TOKEN_RBRACE)
        parse_stmt();
}

void parse_stmt()
{
    if (parser_tokens[parser_index].type == TOKEN_RETURN)
        parse_returnStmt();
    else if (parser_tokens[parser_index].type == TOKEN_LBRACE)
        parse_compoundStmt();
    else if (parser_tokens[parser_index].type == TOKEN_IF)
        parse_selectStmt();
    else if (parser_tokens[parser_index].type == TOKEN_WHILE ||
             parser_tokens[parser_index].type == TOKEN_FOR)
        parse_iterStmt();
    else if (parser_tokens[parser_index].type == TOKEN_INT ||
             parser_tokens[parser_index].type == TOKEN_REAL ||
             parser_tokens[parser_index].type == TOKEN_STRING)
    {
        match(parser_tokens[parser_index].type);
        match(TOKEN_ID);
        if (parser_tokens[parser_index].type == TOKEN_EQUAL)
        {
            match(TOKEN_EQUAL);
            parse_expStmt();
        }
        else
            match(TOKEN_SEMICOLON);
    }
    else
        parse_expStmt();
}

void parse_returnStmt()
{
    match(TOKEN_RETURN);
    if (parser_tokens[parser_index].type != TOKEN_SEMICOLON)
        parse_exp();
    match(TOKEN_SEMICOLON);
}

void parse_compoundStmt()
{
    match(TOKEN_LBRACE);
    parse_localDecls();
    parse_stmtList();
    match(TOKEN_RBRACE);
}

void parse_localDecls()
{
    while (parser_tokens[parser_index].type == TOKEN_INT ||
           parser_tokens[parser_index].type == TOKEN_REAL ||
           parser_tokens[parser_index].type == TOKEN_STRING)
    {
        parse_scopedVarDecl();
    }
}

void parse_scopedVarDecl()
{
    if (parser_tokens[parser_index].type == TOKEN_STATIC)
        match(TOKEN_STATIC);
    parse_typeSpec();
    parse_varDeclList();
    match(TOKEN_SEMICOLON);
}

void parse_selectStmt()
{
    match(TOKEN_IF);
    match(TOKEN_LPAREN);
    parse_exp();
    match(TOKEN_RPAREN);
    parse_stmt();
    if (parser_tokens[parser_index].type == TOKEN_ELSE)
    {
        match(TOKEN_ELSE);
        parse_stmt();
    }
}

void parse_iterStmt()
{
    if (parser_tokens[parser_index].type == TOKEN_WHILE)
    {
        match(TOKEN_WHILE);
        match(TOKEN_LPAREN);
        parse_exp();
        match(TOKEN_RPAREN);
        parse_stmt();
    }
    else if (parser_tokens[parser_index].type == TOKEN_FOR)
    {
        match(TOKEN_FOR);
        match(TOKEN_LPAREN);
        parse_expStmt();
        parse_exp();
        match(TOKEN_SEMICOLON);
        parse_expStmt();
        match(TOKEN_RPAREN);
        parse_stmt();
    }
}