#ifndef PARSER_H
#define PARSER_H
#include "asserts.h"
#include "lexer.h"
#include "grammer.h"

// Variable
typedef struct AST {
  Statement *list[4*1024];
  size_t size;
} ast;

LINKED_LIST(ast, ast_node);
LINKED_LIST(Statement, Statement_node);


typedef struct Parser {
  Token_node *m_buf;
  Arena_node *arena;
  Token (*peek)(struct Parser*,size_t);
  size_t (*peekFor)(struct Parser*, int, size_t);
  Token* (*consume)(struct Parser*);
  Token* (*TryConsume)(struct Parser*,size_t);
  Token* (*TryConsume_err)(struct Parser*, size_t, String);
  ast_node *m_res;
} Parser;

Token peek_token(Parser *,size_t);
size_t peekFor_token(Parser *,int, size_t);
Token *consume_token(Parser *);
Token *TryConsume_token(Parser *, size_t);
Token *TryConsume_err_token(Parser *, size_t, String);

expression* create_expression(Parser *parser, int right_bp, TokenName stopAt);

Statement *create_stm(Parser *parser);

void Parse(Parser *, int);

#endif // !PARSER_H
