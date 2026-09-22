#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>

#include "parser.h"
#include "grammer.h"
#include "asserts.h"

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

typedef struct {
  Token type;
  Token id;
  Token expr;
} decleartion_stmt;

expression* create_expression(Parser *parser, int right_bp, TokenName stopAt);

Token peek_token(struct Parser *parser,int offset)  // front
{
  Token_node *temp = ((Parser *)parser)->m_buf;
  for (int i = offset; i != 0; i--){
    temp = next_Token_node(temp);
  }
  if(parser->m_buf == NULL) {
    printE("parser->m_buf is null");
    exit(-1);
  }
  return temp->val;
}

int peekFor_token(struct Parser *parser,int lookingFor,int offset)
{
  Token temp = parser->peek(parser,offset);
  return temp.tok == (TokenName) lookingFor || temp.type == (TokenType) lookingFor;
}

Token *consume_token(struct Parser *parser)    // advance
{
  if(parser->m_buf->val.tok == EOF_) {
    printE("end of tokens");
    // return &(parser->m_buf->val.tok); 
    return NULL;
  }
  Token *temp = &(parser->m_buf->val); 
  parser->m_buf = parser->m_buf->next_el;
  return temp;
}

Token *TryConsume_token(struct Parser *parser, int o)
{
  if(parser->peekFor(parser,o,0)) {
    // consume_token();
    return parser->consume(parser);
  }
  return NULL;
}

Token *TryConsume_err_token(struct Parser *parser, int o, String message) 
{
  Token *temp = parser->TryConsume(parser,o);
  if(temp != NULL) {
    return temp;
  } else {
    printE(message);
    exit(EXIT_FAILURE);
  }
  return NULL; 
}

binding_power RightAssociative(int p) 
{
  return (binding_power){p + 1, p};
}

binding_power LeftAssociative(int p) 
{
  return (binding_power){p - 1, p};
}

int prefix_bp_lookup(TokenName type) 
{
  switch(type) 
  {
    case PLS: return 300;
    case MNS: return 300;
    case NOT: return 300; 
    case BNT: return 300;
    default:  return 0;
  }
}

binding_power bp_lookup(TokenName type) 
{
  // Binding Power Table, Associativity can also be handled here by returning a second binding power
  // Larger for Left binding, lower for Right binding. E.g. (10, 11) - Left binding, (10, 9) - Right binding
  switch(type) 
  {
    // --- Infix ---
    case PLS:   return LeftAssociative(100);
    case MNS:   return LeftAssociative(100);
    case MUL:   return LeftAssociative(200);
    case DIV:   return LeftAssociative(200);

    case GT:    return LeftAssociative(50);
    case GTE:   return LeftAssociative(50);
    case LT:    return LeftAssociative(50);
    case LTE:   return LeftAssociative(50);
    case EQU:   return LeftAssociative(50);
    case NEQ:   return LeftAssociative(50);

                              // --- Postfix --- (Always Right Associative)
    case INC:   return RightAssociative(400);
    case DEC:   return RightAssociative(400);
    default:    return (binding_power){0,0};
  }
}

// evaluatint funcation with name of 
int variable_evaluate(expression* s) 
{
  variable_literal* self = (variable_literal*)s;
  // add logic 
  return 20;
}

int number_evaluate(expression* s) 
{
  number_literal* self = (number_literal*)s;
  // add logic 
  //number_literal
  return self->number.value.numral_value;
}

int prefix_expression_evaluate(expression* s) 
{
  prefix_expression* self = (prefix_expression*)s;

  int body_res = self->body->evaluate(self->body);

  switch(self->operator.tok) {
    case PLS: return 0 + body_res;
    case MNS: return 0 - body_res;
    case NOT: return !body_res; 
    case BNT: return ~body_res; 
    default: printE("prefix_oprator is not recongized");
  }
} 

int sub_expression_evaluate(expression* s) 
{
  sub_expression* self = (sub_expression*)s;
  return self->body->evaluate(self->body);
}

int postfix_expression_evaluate(expression* s) 
{
  postfix_expression* self = (postfix_expression*)s;

  int body_res = self->body->evaluate(self->body);

  switch(self->operator.tok) 
  {
    case INC:   return body_res;  // increament body_res
    case DEC:   return body_res;
    default:    printE("Invaild posfix oprator");
  }
}
int infix_expression_evaluate(expression* s) 
{
  infix_expression* self = (infix_expression*)s;

  int lhs_res = self->lhs->evaluate(self->lhs);
  int rhs_res = self->rhs->evaluate(self->rhs);

  switch(self->operator.tok) 
  {
    case PLS:   return lhs_res + rhs_res;
    case MNS:   return lhs_res - rhs_res;
    case MUL:   return lhs_res * rhs_res;
    case DIV:   return lhs_res / rhs_res;

    case GT:    return (lhs_res > rhs_res);
    case LT:    return (lhs_res < rhs_res);
    case GTE:   return (lhs_res >= rhs_res);
    case LTE:   return (lhs_res <= rhs_res);
    case EQU:   return (lhs_res == rhs_res);
    case NEQ:   return (lhs_res != rhs_res);
    
    case AND:   return (lhs_res && rhs_res);
    case OR:    return (lhs_res || rhs_res);

    case BND:   return (lhs_res & rhs_res);
    case BOR:   return (lhs_res | rhs_res);
    case XOR:   return (lhs_res ^ rhs_res);
    case SHL:   return (lhs_res << rhs_res);
    case SHR:   return (lhs_res >> rhs_res);
    default:    printE("Operator doesn't recongized");
  }

}
/* 
 * AST creation fuctions
 */

expression* create_number_literal(Parser *parser) 
{
  number_literal* result = malloc(sizeof(number_literal));
  result->base.evaluate = &number_evaluate;

  result->number = *(parser->consume(parser));
  //advance();

  return (expression*)result;
}

expression* create_variable_literal(Parser *parser) 
{
  variable_literal* result = malloc(sizeof(variable_literal));
  result->base.evaluate = &variable_evaluate;

  result->var = *(parser->consume(parser));
  // advance();

  return (expression*)result;
}

expression* create_sub_expression(Parser *parser) 
{
  sub_expression* result = malloc(sizeof(sub_expression));
  result->base.evaluate = &sub_expression_evaluate;
  if (!parser->peekFor(parser,OCR,0)) {
    // Should do error handling!
    return (expression*)result;
  }
  parser->consume(parser);
  // advance();
  result->body = create_expression(parser,0, SMI);
  if (!parser->peekFor(parser,OCR,0)) {
    // Should do error handling!
    return (expression*)result;
  }
  parser->consume(parser);
//  advance();

  return (expression*)result;
}

expression* create_infix_expression(Parser *parser, expression* _lhs, int min_bp ) 
{
  infix_expression* result = malloc(sizeof(infix_expression));
  result->base.evaluate = &infix_expression_evaluate;

  result->lhs = _lhs;
  result->operator = *(parser->consume(parser));
  // advance();
  result->rhs = create_expression(parser, min_bp, SMI);    

  return(expression*)result;
}

expression* create_prefix_expression(Parser *parser, int min_bp ) 
{
  prefix_expression* result = malloc(sizeof(prefix_expression));
  result->base.evaluate = &prefix_expression_evaluate;
  result->operator = *(parser->consume(parser));
  result->body = create_expression(parser,min_bp, SMI);

  return(expression*)result;
}

expression* create_postfix_expression(Parser *parser, expression* _lhs, int min_bp ) 
{
  prefix_expression* result = malloc(sizeof(prefix_expression));
  result->base.evaluate = &postfix_expression_evaluate;

  result->body = _lhs;
  // if (parser->peek(0) )
  result->operator = *(parser->consume(parser));

  return(expression*)result;
}

expression* create_expression(Parser *parser, int right_bp, TokenName stopAt) 
{
  expression* result = NULL;

  // Check to see if this is a prefix or a valid infix left-hand-side.
  if (parser->peekFor(parser,(int)INT, 0)) 
  {
    result = create_number_literal(parser);
  } else if (parser->peekFor(parser,ID,0)) 
  {
    result = create_variable_literal(parser);
  } else if (parser->peekFor(parser,OCR,0)) 
  {
    result = create_sub_expression(parser);
    // --- Prefix Operators ---
  } else if (parser->peekFor(parser,OP_UNARY,0)) 
  {
    if(parser->m_buf == NULL){
      printE("error of null");
    }
    result = create_prefix_expression( parser, prefix_bp_lookup( parser->peek(parser,0).tok ) );
  }

  // Check the next token, if its a valid infix token. Plus the LHS we've just parsed down the AST
  // and into the infix AST node.
  while(
      !(parser->peekFor(parser,(int) stopAt,0) ) && 
      right_bp < bp_lookup( parser->peek(parser,0).tok ).lp
  ) 
  {
    if(parser->peekFor(parser,INC,0) || parser->peekFor(parser,DEC,0)) 
    {
      result = create_postfix_expression(parser, result, bp_lookup( parser->peek(parser,0).tok ).rp);
    } 
    else 
    {
      result = create_infix_expression(parser, result, bp_lookup( parser->peek(parser,0).tok).rp );
    } 
  }
  // Check we didn't mess up
  assert(result != NULL);
  return result;
}

void prattParse(Parser *parser, TokenName stopAt) 
{
  printf("token - %d\n " ,next_Token_node( next_Token_node(parser->m_buf) )->val.tok);
  expression* ast = create_expression(parser, 0, stopAt);       
  printf("result = %d\n", ast->evaluate(ast));
}

void parse_declear_stmt(Parser *parser)
{
  decleartion_stmt *stmt = (decleartion_stmt *) malloc(sizeof(decleartion_stmt));
  stmt->type = *(parser->TryConsume(parser,TYPE));
  parser->TryConsume_err(parser,ID, "expected IDENTIFER in declear_stmt ");
  /*if(parser->peekFor(parser,ID,0)) {
    stmt->id = *(parser->consume(parser));
  }
  else {
    printE("expect a IDENTIFER");
  }*/
  if(parser->peekFor(parser, OP_ASSIGN, 0)) {
    parser->consume(parser);
    prattParse(parser, SMI);
  }
  parser->TryConsume_err(parser,SMI, "forget ';' in declear_stmt"); 
}


Statement *create_stm(Parser *parser)
{
  switch (parser->peek(parser,0).type) {
    case TYPE:
      // decleartion 
      parse_declear_stmt(parser);
      break;
    case KEYWORD:
      /*
       */
      switch (parser->peek(parser,0).tok) {
        case IMP:
          // import statement
          break;
        case FUN:
          // Fucntion decleartion
          break;
        case LOP:
          // Loop statement
          break;
        case FEL:
          // for each loop statement
        case LST:
          // list decleartion
        case STC:
          // Struct decleartion
        case ENM:
          // Enum decleartion
        case CLS:
          // class decleartion
        case IF:
          // if elif else statement
        case RET:
          // return statement
        default:
          printE("invaaild statement");
          printf("token = %d\n", parser->peek(parser,0).tok);
          exit(EXIT_FAILURE);
      }
      break;
    case PUNCTATION:
      /*
       */
      // do-while loop
      break;
    case IDENTIFER:
      // 
      // assignment statement
      //*function call */ 
      break;

    case EOF_:
      return NULL;
    default:
      printf("tokentype = %d\n", parser->peek(parser,0).type);
      printf("token = %d\n", parser->peek(parser,0).tok);
  }
  // int lenght = 0;
  // // Token_2Dnode *temp_ptr = (Token_2Dnode *) malloc(sizeof(Token_2Dnode));
  // Token_2Dnode *Ast_list;
  // Token_node **temp_ptr = &(parser->m_buf);
  // /*
  //  * (*temp_ptr)->val->tok != SEMI || !parser->peekFor(parser,KEYWORD)
  //  **/
  // for (int i = 0; parser->peekFor(parser,EOF_,0); i++)
  // {
  //   if(parser->peekFor(parser,SMI, 0) || parser->peekFor(parser, KEYWORD, 1))
  //   {
  //
  //   } 
  //   else 
  //   {
  //     printE("Error");
  //   }
  // } 
}

void Parse(Parser *parser) 
{
  for (int i= 0; !parser->peekFor(parser, EOF_, 0); i++) 
  {
    Statement *stm = create_stm(parser);
  }
}



