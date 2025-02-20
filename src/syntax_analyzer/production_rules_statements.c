#include "production_rules.h"

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
             parser_tokens[parser_index].type == TOKEN_STRING ||
             parser_tokens[parser_index].type == TOKEN_BOOL)
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
    else if (parser_tokens[parser_index].type == TOKEN_DUALPLUS ||
             parser_tokens[parser_index].type == TOKEN_DUALMINUS)
        parse_preOp();
    else if (parser_tokens[parser_index].type == TOKEN_ID)
        parse_idOp();
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

// void parse_idOp()
// {
//     match(TOKEN_ID);
//     if (parser_tokens[parser_index].type == TOKEN_LBRACKET)
//     {
//         match(TOKEN_LBRACKET);
//         parse_exp();
//         match(TOKEN_RBRACKET);
//     }

//     if (parser_tokens[parser_index].type == TOKEN_EQUAL ||
//         parser_tokens[parser_index].type == TOKEN_PLUSEQL ||
//         parser_tokens[parser_index].type == TOKEN_MINUSEQL ||
//         parser_tokens[parser_index].type == TOKEN_MULEQL ||
//         parser_tokens[parser_index].type == TOKEN_DIVEQL)
//     {

//         match(parser_tokens[parser_index].type);
//         parse_exp();
//         match(TOKEN_SEMICOLON);
//     }
//     else if (parser_tokens[parser_index].type == TOKEN_DUALPLUS ||
//              parser_tokens[parser_index].type == TOKEN_DUALMINUS)
//     {
//         match(parser_tokens[parser_index].type); // Match '++' or '--'
//         match(TOKEN_SEMICOLON);
//     }
//     else
//     {
//         if (parser_tokens[parser_index].type == TOKEN_LPAREN)
//             parse_call();
//         match(TOKEN_SEMICOLON);
//     }
// }