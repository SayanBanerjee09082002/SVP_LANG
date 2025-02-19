#include "lexical_analyzer.h"

Token get_next_token(FILE *input)
{
    Token token;
    char character = fgetc(input);

    while (isspace(character))
        character = fgetc(input);

    if (character == EOF)
    {
        token.type = TOKEN_EOF;
        token.lexeme = create_string("EOF");
        return token;
    }

    switch (character)
    {
    case '[':
        token.lexeme = create_string("[");
        token.type = TOKEN_LBRACKET;
        break;
    case ']':
        token.lexeme = create_string("]");
        token.type = TOKEN_RBRACKET;
        break;
    case '(':
        token.lexeme = create_string("(");
        token.type = TOKEN_LPAREN;
        break;
    case ')':
        token.lexeme = create_string(")");
        token.type = TOKEN_RPAREN;
        break;
    case '{':
        token.lexeme = create_string("{");
        token.type = TOKEN_LBRACE;
        break;
    case '}':
        token.lexeme = create_string("}");
        token.type = TOKEN_RBRACE;
        break;
    case ',':
        token.lexeme = create_string(",");
        token.type = TOKEN_COMMA;
        break;
    case ':':
        token.lexeme = create_string(":");
        token.type = TOKEN_COLON;
        break;
    case '?':
        token.lexeme = create_string("?");
        token.type = TOKEN_QUESTION;
        break;
    case ';':
        token.lexeme = create_string(";");
        token.type = TOKEN_SEMICOLON;
        break;
    case '+':
        token = operator_analyzer(input, character);
        break;
    case '-':
        token = operator_analyzer(input, character);
        break;
    case '*':
        token = operator_analyzer(input, character);
        break;
    case '/':
        token = operator_analyzer(input, character);
        break;
    case '<':
        token = operator_analyzer(input, character);
        break;
    case '>':
        token = operator_analyzer(input, character);
        break;
    case '=':
        token = operator_analyzer(input, character);
        break;
    case '!':
        token = operator_analyzer(input, character);
        break;
    case '&':
        token.lexeme = create_string("&");
        token.type = TOKEN_ADD;
        break;
    case '|':
        token.lexeme = create_string("|");
        token.type = TOKEN_OR;
        break;
    case '#':
        token.lexeme = create_string("#");
        token.type = TOKEN_HASH;
        break;
    case '.':
        token.lexeme = create_string(".");
        token.type = TOKEN_DOT;
        break;
    case '~':
        token.lexeme = create_string("~");
        token.type = TOKEN_TILDE;
        break;
    // String literal
    case '"':
    {
        string literal = create_string("");
        literal = concat_character(literal, '"');
        while ((character = fgetc(input)) != '"' && character != EOF)
            literal = concat_character(literal, character);
        if (character == '"')
            literal = concat_character(literal, '"');
        token.lexeme = literal;
        token.type = TOKEN_STRLTR;
    }
    break;
    case '\'':
    {
        string literal = create_string("");
        literal = concat_character(literal, '\'');
        while ((character = fgetc(input)) != '\'' && character != EOF)
            literal = concat_character(literal, character);
        if (character == '\'')
            literal = concat_character(literal, '\'');
        token.lexeme = literal;
        token.type = TOKEN_STRLTR;
    }
    break;
    default:
    {
        // Keywords and ID
        if (isalpha(character) || character == '_')
            token = keyword_analyzer(input, character);
        else if (isdigit(character))
        // Integer and Real literal
        {
            string number = create_string("");
            number = concat_character(number, character);
            bool is_real = false;

            while ((character = fgetc(input)) != EOF && (isdigit(character) || character == '.'))
            {
                if (character == '.')
                {
                    if (is_real)
                        break;
                    is_real = true;
                }
                number = concat_character(number, character);
            }

            ungetc(character, input);
            token.lexeme = number;
            token.type = is_real ? TOKEN_REALLTR : TOKEN_INTLTR;
        }
        else
        { // Invalid token
            token.lexeme = create_string("");
            token.type = TOKEN_ERROR;
        }
    }
    }

    return token;
}

Token *lexical_analyzer(FILE *input)
{
    Token *tokens = NULL;
    Token token;
    int count = 0;

    initialize_keyword_table();

    do
    {
        token = get_next_token(input);
        tokens = (Token *)realloc(tokens, (count + 1) * sizeof(Token));
        if (tokens == NULL)
        {
            fprintf(stderr, "Memory allocation failed\n");
            exit(1);
        }
        tokens[count] = token;
        count++;
        if (token.type == TOKEN_ERROR) {
            printf("ERROR: INVALID TOKEN\n");
            exit(EXIT_FAILURE);
        }
    } while (token.type != TOKEN_EOF);

    return tokens;
}