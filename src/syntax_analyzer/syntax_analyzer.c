#include "syntax_analyzer.h"

Token *parser_tokens;
int parser_index = 0; 


void syntax_analyzer(Token *tokens) {
    parser_tokens = tokens;
    parse_declList();
    match(TOKEN_EOF);
}