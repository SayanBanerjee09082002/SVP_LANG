#include "production_rules_expressions.h"

void parse_expStmt()
{
    if (parser_tokens[parser_index].type != TOKEN_SEMICOLON)
        parse_exp();
    match(TOKEN_SEMICOLON);
}

void parse_exp()
{
    parse_term();
    parse_exp_prime();
}

void parse_term()
{
    parse_factor();
    parse_term_prime();
}

void parse_factor()
{
    if (parser_tokens[parser_index].type == TOKEN_ID ||
        parser_tokens[parser_index].type == TOKEN_INTLTR ||
        parser_tokens[parser_index].type == TOKEN_REALLTR)
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
        fprintf(stderr, "Syntax error: Invalid factor\n");
        exit(EXIT_FAILURE);
    }
}

void parse_term_prime()
{
    if (parser_tokens[parser_index].type == TOKEN_MULTIPLY)
    {
        match(TOKEN_MULTIPLY);
        parse_factor();
        parse_term_prime();
    }
}

void parse_exp_prime()
{
    if (parser_tokens[parser_index].type == TOKEN_ADD)
    {
        match(TOKEN_ADD);
        parse_term();
        parse_exp_prime();
    }
}