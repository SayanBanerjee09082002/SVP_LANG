#include "keyword_analyzer.h"

KeywordEntry *keyword_table[KEYWORD_TABLE_SIZE] = {NULL};

unsigned int hash(const char *str)
{
    unsigned int hash = 5381;
    char character;
    while ((character = *str++))
        hash = ((hash << 5) + hash) + character;
    return hash % KEYWORD_TABLE_SIZE;
}

void insert_keyword(const char *keyword, TokenType type)
{
    unsigned int index = hash(keyword);
    KeywordEntry *entry = malloc(sizeof(KeywordEntry));
    entry->keyword = keyword;
    entry->type = type;
    entry->next = keyword_table[index];
    keyword_table[index] = entry;
}

void initialize_keyword_table()
{
    insert_keyword("bool", TOKEN_BOOL);
    insert_keyword("case", TOKEN_CASE);
    insert_keyword("continue", TOKEN_CONTINUE);
    insert_keyword("default", TOKEN_DEFAULT);
    insert_keyword("do", TOKEN_DO);
    insert_keyword("else", TOKEN_ELSE);
    insert_keyword("for", TOKEN_FOR);
    insert_keyword("if", TOKEN_IF);
    insert_keyword("int", TOKEN_INT);
    insert_keyword("real", TOKEN_REAL);
    insert_keyword("record", TOKEN_RECORD);
    insert_keyword("return", TOKEN_RETURN);
    insert_keyword("static", TOKEN_STATIC);
    insert_keyword("string", TOKEN_STRING);
    insert_keyword("void", TOKEN_VOID);
    insert_keyword("while", TOKEN_WHILE);
    insert_keyword("true", TOKEN_TRUE);
    insert_keyword("false", TOKEN_FALSE);
}

Token keyword_analyzer(FILE *input, char first_char)
{
    Token token;
    string lexeme = create_string("");
    lexeme = concat_character(lexeme, first_char);
    char character;

    while ((character = fgetc(input)) != EOF && (isalnum(character) || character == '_'))
        lexeme = concat_character(lexeme, character);

    ungetc(character, input);

    unsigned int index = hash(lexeme);
    KeywordEntry *entry = keyword_table[index];

    while (entry != NULL)
    {
        if (strcmp(entry->keyword, lexeme) == 0)
        {
            token.type = entry->type;
            token.lexeme = lexeme;
            return token;
        }
        entry = entry->next;
    }

    token.type = TOKEN_ID;
    token.lexeme = lexeme;
    return token;
}