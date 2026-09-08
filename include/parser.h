#ifndef PARSER_H
#define PARSER_H
#include "asserts.h"
#include "lexer.h"
#include "grammer.h"
// Variable
typedef struct 
{
  expression base;
  Token var;
} variable_literal;

typedef struct 
{
  expression base;
  Token number;
} number_literal;

typedef struct 
{
  expression base;
  expression* body;
} sub_expression;

typedef struct 
{
  expression base;
  expression* lhs;
  Token operator;
  expression* rhs;
} infix_expression;

typedef struct {
  expression base;
  Token operator;
  expression* body;
} prefix_expression;
//  <body:expression> <opeartor>
typedef struct 
{
  expression base;
  Token operator;
  expression* body;
} postfix_expression;

typedef struct 
{
  int lp;
  int rp;
} binding_power;

typedef struct Parser {
  Token_node *m_buf;
  Token (*peek)(struct Parser*,int);
  int (*peekFor)(struct Parser*, int);
  Token (*consume)(struct Parser*);
  int (*TryConsume)(struct Parser*,int);
  Block *m_res;
} Parser;


Token peek_token(Parser *,int);
int peekFor_token(Parser *,int);
Token consume_token(Parser *);
int TryConsume_token(Parser *, int);
expression* create_expression(Parser *parser, int right_bp, TokenName stopAt);

void Parse(Parser *);

#endif // !PARSER_H
