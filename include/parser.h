#ifndef PARSER_H
#define PARSER_H
#include "asserts.h"
#include "lexer.h"
#include "grammer.h"
// Variable
typedef struct Parser {
  Token_node *m_buf;
  Token (*peek)(struct Parser*,int);
  int (*peekFor)(struct Parser*, int, int);
  Token* (*consume)(struct Parser*);
  Token* (*TryConsume)(struct Parser*,int);
  Token* (*TryConsume_err)(struct Parser*, int, String);
  Program *m_res;
} Parser;


Token peek_token(Parser *,int);
int peekFor_token(Parser *,int, int);
Token *consume_token(Parser *);
Token *TryConsume_token(Parser *, int);
Token *TryConsume_err_token(Parser *, int, String);

expression* create_expression(Parser *parser, int right_bp, TokenName stopAt);

void Parse(Parser *);

#endif // !PARSER_H
