#ifndef TOKENS_H
#define TOKENS_H

#include "../string_datatype.h"

typedef enum
{
    TOKEN_LBRACKET,  // [
    TOKEN_RBRACKET,  // ]
    TOKEN_LPAREN,    // (
    TOKEN_RPAREN,    // )
    TOKEN_LBRACE,    // {
    TOKEN_RBRACE,    // }
    TOKEN_COMMA,     // ,
    TOKEN_COLON,     // :
    TOKEN_QUESTION,  // ?
    TOKEN_SEMICOLON, // ;
    TOKEN_ADD,       // +
    TOKEN_MINUS,     // -
    TOKEN_MULTIPLY,  // *
    TOKEN_DIVIDE,    // /
    TOKEN_POWER,     // ^
    TOKEN_MODULO,    // %
    TOKEN_EQUAL,     // =
    TOKEN_DUALPLUS,  // ++
    TOKEN_DUALMINUS, // --
    TOKEN_GREATER,   // >
    TOKEN_LESSER,    // <
    TOKEN_EQUALITY,  // ==
    TOKEN_NOT,       // !
    TOKEN_GRTREQL,   // >=
    TOKEN_LESREQL,   // <=
    TOKEN_NOTEQUAL,  // !=
    TOKEN_AND,       // &&
    TOKEN_OR,        // ||
    TOKEN_PLUSEQL,   // +=
    TOKEN_MINUSEQL,  // -=
    TOKEN_MULEQL,    // *=
    TOKEN_DIVEQL,    // /=
    TOKEN_HASH,      // #
    TOKEN_DOT,       // .
    TOKEN_TILDE,     // ~
    TOKEN_BOOL,      // bool
    TOKEN_CASE,      // case
    TOKEN_CONTINUE,  // continue
    TOKEN_DEFAULT,   // default
    TOKEN_DEFINE,    // define
    TOKEN_DO,        // do
    TOKEN_ELSE,      // else
    TOKEN_FOR,       // for
    TOKEN_IF,        // if
    TOKEN_INCLUDE,   // include
    TOKEN_INT,       // int
    TOKEN_REAL,      // real: float/double literals (e.g., 3.14)
    TOKEN_RECORD,    // record
    TOKEN_RETURN,    // return
    TOKEN_STRING,    // string literals (e.g., "hello")
    TOKEN_VOID,      // void
    TOKEN_WHILE,     // while
    TOKEN_TRUE,      // True literal
    TOKEN_FALSE,     // False literal
    TOKEN_INTLTR,    // Int literals
    TOKEN_REALLTR,   // Real literals
    TOKEN_STRLTR,    // String literals
    TOKEN_ID,        // identifier (e.g., variable names)
    TOKEN_EOF,       // end of input
    TOKEN_ERROR,     // error
} TokenType;

typedef struct
{
    TokenType type;
    string lexeme;
} Token;

#endif