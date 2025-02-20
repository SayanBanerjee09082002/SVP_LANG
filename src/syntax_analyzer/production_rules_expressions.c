#include "production_rules.h"

void parse_localDecls()
{
    while (parser_tokens[parser_index].type == TOKEN_INT ||
           parser_tokens[parser_index].type == TOKEN_REAL ||
           parser_tokens[parser_index].type == TOKEN_STRING ||
           parser_tokens[parser_index].type == TOKEN_BOOL)
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
void parse_preOp()
{
    match(parser_tokens[parser_index].type);
    match(TOKEN_ID);
    match(TOKEN_SEMICOLON);
    parse_stmt();
}

void parse_postOp()
{
    match(TOKEN_ID);
    match(parser_tokens[parser_index].type);
    match(TOKEN_SEMICOLON);
    parse_stmt();
}

void parse_idOp()
{
    match(TOKEN_ID);

    // Check for array access (e.g., arr[5])
    if (parser_tokens[parser_index].type == TOKEN_LBRACKET)
    {
        match(TOKEN_LBRACKET);
        parse_exp(); // Parse the index expression
        match(TOKEN_RBRACKET);
    }

    // Check for assignment operators (=, +=, -=, *=, /=)
    if (parser_tokens[parser_index].type == TOKEN_EQUAL ||
        parser_tokens[parser_index].type == TOKEN_PLUSEQL ||
        parser_tokens[parser_index].type == TOKEN_MINUSEQL ||
        parser_tokens[parser_index].type == TOKEN_MULEQL ||
        parser_tokens[parser_index].type == TOKEN_DIVEQL)
    {

        // Match the assignment operator (e.g., '=', '+=', etc.)
        match(parser_tokens[parser_index].type);

        // Parse the right-hand side expression (e.g., 10 + 2)
        parse_exp();

        // Ensure semicolon terminates the statement
        match(TOKEN_SEMICOLON);
    }
    // Check for postfix increment/decrement (e.g., a++; b--;)
    else if (parser_tokens[parser_index].type == TOKEN_DUALPLUS ||
             parser_tokens[parser_index].type == TOKEN_DUALMINUS)
    {
        match(parser_tokens[parser_index].type); // Match '++' or '--'
        match(TOKEN_SEMICOLON);
    }
    // Handle function calls or other expressions (e.g., myFunc();)
    else
    {
        // If followed by '(', parse function arguments
        if (parser_tokens[parser_index].type == TOKEN_LPAREN)
        {
            parse_call(); // Assume parse_call() handles ID(args)
        }
        match(TOKEN_SEMICOLON);
    }
}

void parse_expStmt()
{
    if (parser_tokens[parser_index].type != TOKEN_SEMICOLON)
        parse_exp();
    match(TOKEN_SEMICOLON);
}

void parse_exp()
{
    parse_ternaryExp(); // Start with ternary expressions
}

void parse_ternaryExp()
{
    parse_logicalOrExp();
    if (parser_tokens[parser_index].type == TOKEN_QUESTION)
    {
        match(TOKEN_QUESTION);
        parse_exp();
        match(TOKEN_COLON);
        parse_ternaryExp();
    }
}

void parse_logicalOrExp()
{
    parse_logicalAndExp();
    while (parser_tokens[parser_index].type == TOKEN_OR)
    {
        match(TOKEN_OR);
        parse_logicalAndExp();
    }
}

void parse_logicalAndExp()
{
    parse_relExp();
    while (parser_tokens[parser_index].type == TOKEN_AND)
    {
        match(TOKEN_AND);
        parse_relExp();
    }
}

void parse_relExp()
{
    parse_sumExp();
    if (parser_tokens[parser_index].type == TOKEN_LESSER ||
        parser_tokens[parser_index].type == TOKEN_GREATER ||
        parser_tokens[parser_index].type == TOKEN_LESREQL ||
        parser_tokens[parser_index].type == TOKEN_GRTREQL ||
        parser_tokens[parser_index].type == TOKEN_EQUALITY ||
        parser_tokens[parser_index].type == TOKEN_NOTEQUAL)
    {
        match(parser_tokens[parser_index].type);
        parse_sumExp();
    }
}

void parse_sumExp()
{
    parse_mulExp();
    while (parser_tokens[parser_index].type == TOKEN_ADD ||
           parser_tokens[parser_index].type == TOKEN_MINUS)
    {
        match(parser_tokens[parser_index].type);
        parse_mulExp();
    }
}

void parse_mulExp()
{
    parse_powerExp();
    while (parser_tokens[parser_index].type == TOKEN_MULTIPLY ||
           parser_tokens[parser_index].type == TOKEN_DIVIDE ||
           parser_tokens[parser_index].type == TOKEN_MODULO)
    {
        match(parser_tokens[parser_index].type);
        parse_powerExp();
    }
}

void parse_powerExp()
{
    parse_unaryExp();
    if (parser_tokens[parser_index].type == TOKEN_POWER)
    {
        match(TOKEN_POWER);
        parse_powerExp();
    }
}

void parse_unaryExp()
{
    if (parser_tokens[parser_index].type == TOKEN_MINUS ||
        parser_tokens[parser_index].type == TOKEN_NOT)
    {
        match(parser_tokens[parser_index].type);
        parse_unaryExp();
    }
    else
        parse_factor();
}

void parse_factor()
{
    if (parser_tokens[parser_index].type == TOKEN_ID)
    {
        match(TOKEN_ID);
        if (parser_tokens[parser_index].type == TOKEN_LBRACKET)
        {
            match(TOKEN_LBRACKET);
            parse_exp();
            match(TOKEN_RBRACKET);
        }
        else if (parser_tokens[parser_index].type == TOKEN_LPAREN)
        {
            match(TOKEN_LPAREN);
            parse_args();
            match(TOKEN_RPAREN);
        }
    }
    else if (parser_tokens[parser_index].type == TOKEN_INTLTR ||
             parser_tokens[parser_index].type == TOKEN_REALLTR ||
             parser_tokens[parser_index].type == TOKEN_TRUE ||
             parser_tokens[parser_index].type == TOKEN_FALSE)
    {
        match(parser_tokens[parser_index].type);
    }
    else if (parser_tokens[parser_index].type == TOKEN_LPAREN)
    {
        match(TOKEN_LPAREN);
        parse_exp();
        match(TOKEN_RPAREN);
    }
    else
    {
        fprintf(stderr, "Syntax error: Expected factor (ID, constant, or expression), found %s\n",
                parser_tokens[parser_index].lexeme);
        exit(EXIT_FAILURE);
    }
}

void parse_call()
{
    match(TOKEN_LPAREN);
    parse_args();
    match(TOKEN_RPAREN);
}

void parse_args()
{
    if (parser_tokens[parser_index].type != TOKEN_RPAREN)
    {
        parse_exp();
        while (parser_tokens[parser_index].type == TOKEN_COMMA)
        {
            match(TOKEN_COMMA);
            parse_exp();
        }
    }
}