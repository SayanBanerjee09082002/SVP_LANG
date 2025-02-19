#include <stdio.h>
#include <stdlib.h>
#include "comment_remover.h"
#include "lexical_analyzer/lexical_analyzer.h"
#include "syntax_analyzer/syntax_analyzer.h"
#include "tokens.h"

// extern const char* token_name_array[] = {
//     "LBRACKET",   // TOKEN_LBRACKET
//     "RBRACKET",   // TOKEN_RBRACKET
//     "LPAREN",     // TOKEN_LPAREN
//     "RPAREN",     // TOKEN_RPAREN
//     "LBRACE",     // TOKEN_LBRACE
//     "RBRACE",     // TOKEN_RBRACE
//     "COMMA",      // TOKEN_COMMA
//     "COLON",      // TOKEN_COLON
//     "QUESTION",    // TOKEN_QUESTION
//     "SEMICOLON",  // TOKEN_SEMICOLON
//     "ADD",        // TOKEN_ADD
//     "MINUS",      // TOKEN_MINUS
//     "MULTIPLY",   // TOKEN_MULTIPLY
//     "DIVIDE",     // TOKEN_DIVIDE
//     "POWER",      // TOKEN_POWER
//     "MODULO",     // TOKEN_MODULO
//     "EQUAL",      // TOKEN_EQUAL
//     "DUALPLUS",   // TOKEN_DUALPLUS
//     "DUALMINUS",  // TOKEN_DUALMINUS
//     "GREATER",    // TOKEN_GREATER
//     "LESSER",     // TOKEN_LESSER
//     "EQUALITY",   // TOKEN_EQUALITY
//     "NOT",        // TOKEN_NOT
//     "GRTREQL",    // TOKEN_GRTREQL
//     "LESREQL",    // TOKEN_LESREQL
//     "NOTEQUAL",   // TOKEN_NOTEQUAL
//     "AND",        // TOKEN_AND
//     "OR",         // TOKEN_OR
//     "PLUSEQL",    // TOKEN_PLUSEQL
//     "MINUSEQL",   // TOKEN_MINUSEQL
//     "MULEQL",     // TOKEN_MULEQL
//     "DIVEQL",     // TOKEN_DIVEQL
//     "HASH",       // TOKEN_HASH
//     "DOT",        // TOKEN_DOT
//     "TILDE",      // TOKEN_TILDE
//     "BOOL",       // TOKEN_BOOL
//     "CASE",       // TOKEN_CASE
//     "CONTINUE",   // TOKEN_CONTINUE
//     "DEFAULT",    // TOKEN_DEFAULT
//     "DEFINE",     // TOKEN_DEFINE
//     "DO",         // TOKEN_DO
//     "ELSE",       // TOKEN_ELSE
//     "FOR",        // TOKEN_FOR
//     "IF",         // TOKEN_IF
//     "INCLUDE",    // TOKEN_INCLUDE
//     "INT",        // TOKEN_INT
//     "REAL",       // TOKEN_REAL
//     "RECORD",     // TOKEN_RECORD
//     "RETURN",     // TOKEN_RETURN
//     "STRING",     // TOKEN_STRING
//     "VOID",       // TOKEN_VOID
//     "WHILE",      // TOKEN_WHILE
//     "TRUE",       // TOKEN_TRUE
//     "FALSE",      // TOKEN_FALSE
//     "INTLTR",     // TOKEN_INTLTR
//     "REALLTR",    // TOKEN_REALLTR
//     "STRLTR",     // TOKEN_STRLTR
//     "ID",         // TOKEN_ID
//     "EOF",        // TOKEN_EOF
//     "ERROR"       // TOKEN_ERROR
// };

int main() {
    // Open the file for reading ("r" mode is appropriate for input files)
    FILE *file = fopen("test.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    file = comment_remover(file);

    // Get the tokens from the lexical analyzer.
    Token *tokens = lexical_analyzer(file);
    fclose(file);

    // Iterate over the tokens until the TOKEN_EOF is encountered.
    // int i = 0;
    // while (tokens[i].type != TOKEN_EOF) {
    //     // Print token index, token type (as string) and lexeme.
    //     printf("Token %d: Type: %s, Lexeme: %s\n", i, token_name_array[tokens[i].type], tokens[i].lexeme);
    //     i++;
    // }
    // // Optionally print the EOF token as well.
    // printf("Token %d: Type: %s, Lexeme: %s\n", i, token_name_array[tokens[i].type], tokens[i].lexeme);

    syntax_analyzer(tokens);

    // Clean up allocated memory.
    free(tokens);

    return EXIT_SUCCESS;
}
