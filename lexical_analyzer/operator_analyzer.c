#include "operator_analyzer.h"

Token operator_analyzer(FILE *input, char character)
{
    Token token;
    string op = create_string("");

    switch (character)
    {
    // +, ++, +=
    case '+':
    {
        op = concat_character(op, '+');
        int next_char = fgetc(input);
        if (next_char == '+')
        {
            op = concat_character(op, '+');
            token.type = TOKEN_DUALPLUS;
        }
        else if (next_char == '=')
        {
            op = concat_character(op, '=');
            token.type = TOKEN_PLUSEQL;
        }
        else
        {
            ungetc(next_char, input);
            token.type = TOKEN_ADD;
        }
        token.lexeme = op;
        break;
    }

    // -, --, -=
    case '-':
    {
        op = concat_character(op, '-');
        int next_char = fgetc(input);
        if (next_char == '-')
        {
            op = concat_character(op, '-');
            token.type = TOKEN_DUALMINUS;
        }
        else if (next_char == '=')
        {
            op = concat_character(op, '=');
            token.type = TOKEN_MINUSEQL;
        }
        else
        {
            ungetc(next_char, input);
            token.type = TOKEN_MINUS;
        }
        token.lexeme = op;
        break;
    }

    // *, *=
    case '*':
    {
        op = concat_character(op, '*');
        int next_char = fgetc(input);
        if (next_char == '=')
        {
            op = concat_character(op, '=');
            token.type = TOKEN_MULEQL;
        }
        else
        {
            ungetc(next_char, input);
            token.type = TOKEN_MULTIPLY;
        }
        token.lexeme = op;
        break;
    }

    // /, /=
    case '/':
    {
        op = concat_character(op, '/');
        int next_char = fgetc(input);
        if (next_char == '=')
        {
            op = concat_character(op, '=');
            token.type = TOKEN_DIVEQL;
        }
        else
        {
            ungetc(next_char, input);
            token.type = TOKEN_DIVIDE;
        }
        token.lexeme = op;
        break;
    }

    // <, <=
    case '<':
    {
        op = concat_character(op, '<');
        int next_char = fgetc(input);
        if (next_char == '=')
        {
            op = concat_character(op, '=');
            token.type = TOKEN_LESREQL;
        }
        else
        {
            ungetc(next_char, input);
            token.type = TOKEN_LESSER;
        }
        token.lexeme = op;
        break;
    }

    // >, >=
    case '>':
    {
        op = concat_character(op, '>');
        int next_char = fgetc(input);
        if (next_char == '=')
        {
            op = concat_character(op, '=');
            token.type = TOKEN_GRTREQL;
        }
        else
        {
            ungetc(next_char, input);
            token.type = TOKEN_GREATER;
        }
        token.lexeme = op;
        break;
    }

    // !, !=
    case '!':
    {
        op = concat_character(op, '!');
        int next_char = fgetc(input);
        if (next_char == '=')
        {
            op = concat_character(op, '=');
            token.type = TOKEN_NOTEQUAL;
        }
        else
        {
            ungetc(next_char, input);
            token.type = TOKEN_NOT;
        }
        token.lexeme = op;
        break;
    }

    // =, ==
    case '=':
    {
        op = concat_character(op, '=');
        int next_char = fgetc(input);
        if (next_char == '=')
        {
            op = concat_character(op, '=');
            token.type = TOKEN_EQUALITY;
        }
        else
        {
            ungetc(next_char, input);
            token.type = TOKEN_EQUAL;
        }
        token.lexeme = op;
        break;
    }

    default:
        token.lexeme = create_string("");
        token.type = TOKEN_ERROR;
        break;
    }

    return token;
}