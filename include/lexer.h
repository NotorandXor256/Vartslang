#ifndef LEXER_H 
#define LEXER_H 
#include "asserts.h"

char peek_char(lexer *src, int offset);

char consume_char(lexer *src);

Token to_token(const String token_src);

void tokenize(lexer *src);
#endif
