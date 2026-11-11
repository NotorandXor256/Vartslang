#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>

#include "parser.h"
#include "grammer.h"
#include "asserts.h"



expression* create_expression(Parser *parser, int right_bp, TokenName stopAt);

Token peek_token(struct Parser *parser,size_t offset)  // front
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

size_t peekFor_token(struct Parser *parser,int lookingFor,size_t offset)
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
  printL("token: %d", temp->tok);
  return temp;
}

Token *TryConsume_token(struct Parser *parser, size_t o)
{
  if(parser->peekFor(parser,o,0)) {
    // consume_token();
    return parser->consume(parser);
  }
  return NULL;
}

Token *TryConsume_err_token(struct Parser *parser, size_t o, String message) 
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

void push_ast(Parser *parser, Statement *statment){

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
    default:    
      printE("Invaild posfix oprator");
      exit(-1);
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
    default:    
      printE("Operator doesn't recongized");
      exit(EXIT_FAILURE);
  }

}
/* 
 * AST creation fuctions
 */

expression* create_number_literal(Parser *parser) 
{
  number_literal* result = (number_literal *) allocate(parser->arena,sizeof(number_literal));
  result->base.evaluate = &number_evaluate;

  result->number = *(parser->consume(parser));
  //advance();

  return (expression*)result;
}

expression* create_variable_literal(Parser *parser) 
{
  variable_literal* result = (variable_literal *) allocate(parser->arena,sizeof(variable_literal));
  result->base.evaluate = &variable_evaluate;

  result->var = *(parser->consume(parser));
  // advance();

  return (expression*)result;
}

expression* create_sub_expression(Parser *parser) 
{
  sub_expression* result = (sub_expression *) allocate(parser->arena,sizeof(sub_expression));
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
  infix_expression* result = (infix_expression *) allocate(parser->arena, sizeof(infix_expression));
  result->base.evaluate = &infix_expression_evaluate;

  result->lhs = _lhs;
  result->operator = *(parser->consume(parser));
  // advance();
  result->rhs = create_expression(parser, min_bp, SMI);    

  return(expression*)result;
}

expression* create_prefix_expression(Parser *parser, int min_bp ) 
{
  prefix_expression* result = (prefix_expression*) allocate(parser->arena, sizeof(prefix_expression));
  result->base.evaluate = &prefix_expression_evaluate;
  result->operator = *(parser->consume(parser));
  result->body = create_expression(parser,min_bp, SMI);

  return(expression*)result;
}

expression* create_postfix_expression(Parser *parser, expression* _lhs, int min_bp ) 
{
  prefix_expression* result = (prefix_expression *) allocate(parser->arena, sizeof(prefix_expression));
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

expression* prattParse(Parser *parser, TokenName stopAt) 
{
  printf("token - %d\n " ,next_Token_node( next_Token_node(parser->m_buf) )->val.tok);
  expression* ast = create_expression(parser, 0, stopAt);       
  printf("result = %d\n", ast->evaluate(ast));
  return ast;
}


void *parse_args(Parser *parser, void *(*token)(Parser *)) 
{
  token(parser);
  for(int i = 0; parser->peekFor(parser, CMA,0); i++)
  {
    parser-> TryConsume_err(parser, CMA, "expected ',' in args");
    token(parser);
  }
}

// void Parse(Parser *, int);

Block *parse_block(Parser *parser) {
  Block *stmt = (Block *) allocate(parser->arena, sizeof(Block));
  parser->TryConsume_err(parser, OCR, "expected '{' in block");
  // Block *temp = Parse(parser, CCR);
  Statement_node *temp = stmt->stmts;
  for(int i = 0; parser->peekFor(parser, CCR, 0); i++)
  {
    Statement_node *temp_2 = new_arena_Statement_node(
        create_stm(parser), 
        parser->arena->malloc(parser,sizeof(Statement_node))
    );
    push_Statement_node(&(temp), temp_2);
    temp = temp_2;
  }
  parser->TryConsume_err(parser, CCR, "expected '}' in block");
  return stmt;
}

Statement* parse_declear_var_stmt(Parser *parser)
{
  Declear_var *stmt = (Declear_var *) allocate(parser->arena,sizeof(Declear_var));
  stmt->type = parser->TryConsume(parser,TYPE);
  stmt->id = parser->TryConsume_err(parser,ID, "expected IDENTIFER in declear_stmt ");
  if(parser->peekFor(parser, OP_ASSIGN, 0)) {
    parser->consume(parser);
    stmt->expr = prattParse(parser, SMI);
  }
  return (Statement *) stmt;
}

// size_t function_args_type(Parser *parser){
//   parser->TryConsume_err(parser, LST, "expected '<-[]->' in arrary type");
//   parser->TryConsume_err(parser,);
//   return 0;
// }

void *function_args_declear(Parser *parser)
{ // add parser to this 
  parse_declear_var_stmt(parser);
  return 0;
}
Statement *parse_declear_func_stmt(Parser *parser)
{
  Declear_Func *stmt = (Declear_Func *) allocate(parser->arena,sizeof(Declear_Func));
  stmt->gen = NULL;
  stmt->is_extern = parser->TryConsume(parser, EXT) != NULL ? 1:0;
  parser->TryConsume_err(parser, FUN, "function Expected '<-@->' in fuction declearation statement" );
  parser->TryConsume_err(parser, OCR, "expected '{' function declearation");
  stmt->type = parser->TryConsume(parser, TYPE);
  // parse_args(parser,function_args_type );
  parser->TryConsume_err(parser, CCR, "expected '}'  near expr function declearation");
  stmt->id = parser->TryConsume_err(parser, ID, "expected a name for the function");
  if(parser->TryConsume(parser,OP_ASSIGN)) {
    parser->TryConsume_err(parser, ARG, "expected '@' in cutntion delcreation");
    parser->TryConsume_err(parser, OCR, "expected '{' function declearation");
    // stmt->args = parser_args(parser);
    parse_args(parser,function_args_declear);
    parser->TryConsume_err(parser, CCR, "expected '}' function declearation");
    parser->TryConsume_err(parser, ARW, "Expected '->' in function declearation");
    // stmt->args - parser_block(parser);
    parse_block(parser);
  }
  return (Statement *) stmt;
}


Statement *parse_assignment_var_stmt(Parser *parser)
{
  parser->TryConsume_err(parser, IDENTIFER, "Expected IDENTIFER in assignment statment");
  parser->TryConsume_err(parser, OP_ASSIGN, "Expected '<-' in assignment statement");
  // parser->TryConsume_err(parser, O)
}

Statement *function_args_var_declear(Parser *parser) {
  parser->TryConsume_err(parser, TYPE, "expected Type in loop_stm");
  return 0;
}

void *parse_expr(Parser *parser) {
  prattParse(parser, CCR);
  return 0;
}

Statement *parse_loop_stmt(Parser *parser)
{
  Lp_Stm *stmt = (Lp_Stm *) allocate(parser->arena,sizeof(Lp_Stm));
  parser->TryConsume(parser, LOP);
  parser->TryConsume_err(parser, OCR, "expected '{' function declearation");
  // parse_declear_var_stmt(parser);
  stmt->assign_stm = parse_args(parser, function_args_declear);
  parser->TryConsume_err(parser, SMI, "expected ';'");
  stmt->condition = prattParse(parser, SMI);
  parser->TryConsume_err(parser, SMI, "expected ';'");
  stmt->update = parse_args(parser, parse_expr);
  parser->TryConsume_err(parser, CCR, "expected '}' function declearation");
  parser->TryConsume_err(parser, ARW,"Expected '->' in loop");
  stmt->b = parse_block(parser);
  return (Statement *) stmt;
}

Statement *parse_foreach_loop_stmt(Parser *parser) {

}

Statement *parse_do_while_stmt(Parser *parser) {
  Do_Lp_Stm *stmt = (Do_Lp_Stm *) allocate(parser->arena, sizeof(Do_Lp_Stm));
  stmt->b = parse_block(parser);
  parser->TryConsume_err(parser, ARW, "Expected '->' in do-while statment");
  parser->TryConsume(parser, LOP);
  parser->TryConsume_err(parser, OCR, "expected '{' function declearation");
  stmt->assign_stm = parse_args(parser, function_args_declear);
  parser->TryConsume_err(parser, SMI, "expected ';'");
  stmt->condition = prattParse(parser, SMI);
  parser->TryConsume_err(parser, SMI, "expected ';'");
  stmt->update = parse_args(parser, parse_expr);
  parser->TryConsume_err(parser, CCR, "expected '}' function declearation");
  return (Statement *) stmt;
}

LINKED_LIST(expression, expression_node);
LINKED_LIST(Block, block_node);

Statement *parse_if_stmt(Parser *parser) 
{
  If_Stm *stmt = (If_Stm *) allocate(parser->arena,sizeof(If_Stm));
  stmt->no_of_expr = 0;
  stmt->no_of_block = 0;
  parser->TryConsume_err(parser, IF, "expected '?' in if statement");
  parser->TryConsume_err(parser, OCR, "expected '{' if statement");
  // stmt->expr = prattParse(parser, CCR);
  push_expression_node(&(stmt->expr), prattParse(parser, CCR));
  stmt->no_of_expr++;
  parser->TryConsume_err(parser, CCR, "expected '}' if statement");
  parser->TryConsume_err(parser, ARW,"Expected '->' in if statement");
  parse_block(parser);
  while (parser->peekFor(parser,ARW,0) && parser->peekFor(parser,IF,1))
  {
    parser->TryConsume(parser,ARW);
    parser->TryConsume_err(parser, IF, "expected '?' in if statement");
    parser->TryConsume_err(parser, OCR, "expected '{' if statement");
    // prattParse(parser, CCR);
    push_expression_node(&(stmt->expr), prattParse(parser, CCR));
    stmt->no_of_expr++;
    parser->TryConsume_err(parser, CCR, "expected '}' if statement");
    parser->TryConsume_err(parser, ARW,"Expected '->' in if statement");
    push_block_node(&(stmt->b), parse_block(parser));
    stmt->no_of_block++;
  }
  if(parser->peekFor(parser,ARW,0)) 
  {
    parser->TryConsume(parser, ARW);
    push_block_node(&(stmt->b), parse_block(parser));
    stmt->no_of_block++;
  }
  return (Statement *) stmt;
}

void parse_arrary(Parser *parser)
{
  parser->TryConsume_err(parser, OCR, "Expected '{' in array");
  if(parser->peekFor(parser, OCR, 0))
  {
    // here nested arrary
    parse_arrary(parser); 
  }
  else
  {
    prattParse(parser, CCR);
  }
}

Statement *parse_declear_arr_stmt(Parser *parser)
{
  Declear_Arr *stmt = (Declear_Arr *) allocate(parser->arena, sizeof(Declear_Arr));
  parser->TryConsume_err(parser, LST);
  parser->TryConsume_err(parser, OCR);
  stmt->type = prattParse(parser,OCR);
  parser->TryConsume_err(parser, CCR, "Expected '}' in arrary decleartion");
  stmt->id = parser->TryConsume_err(parser, IDENTIFER, "Expected IDENTIFER in arryary decleartion");
  if(parser->TryConsume(parser, OP_ASSIGN)) {
    parser->TryConsume_err(parser, LIT, "Expected '[]' in arrary decleartion");
    parser->TryConsume_err(parser, OCR, "Expected '{' in arrary decleartion");
    // parse_expr(parser);
    stmt->dim = parse_args(parser,parse_expr);
    parser->TryConsume_err(parser, CCR, "Expected '}' in arrary declearation");
    parser->TryConsume_err(parser, ARW, "Expected '->' in arrary declearation");
    // arrary
    stmt->arr = parse_arrary(parser);
  } else {
    
    stmt->dim = 0;
    stmt->arr = NULL;
  }
  return (Statement *) stmt;
}

Statement *parse_declear_strut_stmt(Parser *parser) 
{
  Declear_Struct *stmt = (Declear_Struct *) allocate(parser->arena, sizeof(Declear_Struct));
  parser->TryConsume(parser,STC);
  parser->TryConsume_err(parser,OCR, "Expected '{' in struct decleartion");
  parser->TryConsume_err(parser, CCR, "Expected '}' in struct decleartion");
  stmt->id = parser->TryConsume_err(parser, ID);
  if(parser->TryConsume(parser, OP_ASSIGN) != NULL) 
  {
    parser->TryConsume_err(parser, STA, "Expected '<+>' in struct decleartion");
    parser->TryConsume_err(parser, OCR, "Expected '{' in struct decleartion");
    parser->TryConsume_err(parser, CCR, "Expected '}' in struct decleartion");
    parser->TryConsume_err(parser, ARW, "Expected '->' in struct decleartion");
    parser->TryConsume_err(parser, OCR, "Expected '{' in struct decleartion");
    stmt->members = parse_args(parser, parse_declear_var_stmt);
    parser->TryConsume_err(parser, CCR, "Expected '}' in struct decleartion");
  }
  return (Statement *) stmt;
}

size_t consume_enum_memeber(Parser *parser) {
  if(parser->TryConsume(parser,IDENTIFER) && 
     parser->TryConsume(parser,OP_ASSIGN))
  {
    parser->TryConsume_err(parser, LITERAL, "Expected a LITERAL in enum decleartion statement");
  }

}

Statement *parse_declear_enum_stmt(Parser *parser) 
{
  parser->TryConsume_err(parser,ENM, "Expected '<-<|>->' ");
  parser->TryConsume_err(parser, OCR, "expected '{' enum decleartion statement");
  parser->TryConsume_err(parser,CCR, "Expected '}' in enum decleartion ");
  parser->TryConsume_err(parser, ID);

  if(parser->TryConsume(parser,OP_ASSIGN)){
    parser->TryConsume_err(parser, ENA);
    parser->TryConsume_err(parser, OCR);
    parser->TryConsume_err(parser, CCR);
    parser->TryConsume_err(parser, ARW);
    parser->TryConsume_err(parser, OCR);
    parse_args(parser,consume_enum_memeber);
    parser->TryConsume_err(parser,CCR);
  }
  return NULl;
}

void parse_declear_class_stmt(Parser *parser)
{
  // parser->TryConsume_err(parser, CLS);
  // parser->TryConsume_err(parser,OCR);
  // parser->TryConsume_err(parser,CCR);
  // parser->TryConsume_err(parser, ID);
  // parser->TryConsume_err(parser);
}

Statement *create_stm(Parser *parser)
{
  Statement *stmt = NULL;
  switch (parser->peek(parser,0).type) {
    case TYPE:
      // decleartion 
      stmt = parse_declear_var_stmt(parser);
      parser->TryConsume_err(parser, SMI, "expected ';'");
      return stmt;
      break;
    case KEYWORD:
      switch (parser->peek(parser,0).tok) {
        case IMP:
          // import statement
          parser->consume(parser);
          parser->TryConsume_err(parser, ID, "expected 'IDENTIFER'");
          parser->TryConsume_err(parser, SMI, "expected ';'");
          return NULL;
          break;
        case EXT:
        case FUN:
          // Fucntion decleartion
          stmt = (Statement *) parse_declear_func_stmt(parser);
          parser->TryConsume_err(parser, SMI, "expected ';'");
          return stmt;
          break;
        case LOP:
          // Loop statement
          stmt = (Statement *) parse_loop_stmt(parser);
          return stmt;
          break;
        case FEL:
          // for each loop statement
          stmt = (Statement *) parse_foreach_loop_stmt(parser);
          return stmt;
          break;
        case LST:
          // list decleartion
          stmt = (Statement *) parse_declear_arr_stmt(parser);
          parser->TryConsume_err(parser, SMI, "expected ';'");
          return stmt;
          break;
        case STC:
          // Struct decleartion
          stmt = (Statement *) parse_decleart_stru_stmt(parser);
          parser->TryConsume_err(parser, SMI, "expected ';'");
          return stmt;
          break;
        case ENM:
          // Enum decleartion
          stmt = (Statement *) parse_declear_enum_stmt(parser);
          parser->TryConsume_err(parser, SMI, "expected ';'");
          return stmt;
          break;
        case CLS:
          // class decleartion
          stmt = (Statement *) parse_declear_class_stmt(parser);
          parser->TryConsume_err(parser, SMI, "expected ';'");
          return stmt;
          break;
        case IF:
          // if elif else statement
          stmt = (Statement *) parse_if_stmt(parser);
          return stmt;
          break;
        case RET:
          // return statement
          parser->consume(parser);
          if(parser->TryConsume(parser, NULL_) != NULL || 
             parser->TryConsume(parser, SMI) != NULL) 
          {
            
          } else {
            prattParse(parser,SMI);
          }
          parser->TryConsume_err(parser, SMI, "expected ';'");
          return stmt;
          break;
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
      stmt = (Statement *)  parse_do_while_stmt(parser);
      return stmt;
      break;
    case IDENTIFER:
      // 
      // assignment statement
      //*function call */ 
      parser->consume(parser);
      switch (parser->peek(parser,0).tok) {
        case CAL:
          parser->consume(parser);
          parser->TryConsume_err(parser, OCR, "expected '{' in function call");
          parse_args(parser, parse_expr);
          parser->TryConsume_err(parser, CCR, "expected '}' in function call");
          parser->TryConsume_err(parser, SMI, "expected ';' in function call");
          // return stmt;
          break;
        case ARW:
          // parse assignment statements
          break;
      }
      break;

    case EOF_:
      return NULL;
    default:
      printf("tokentype = %d\n", parser->peek(parser,0).type);
      printf("token = %d\n", parser->peek(parser,0).tok);
  }
}

Statement_node *Parse_Statement(Parser *parser, int stopAt) 
{
  Statement_node *stmts = parser->m_buf;
  Statement_node *temp = NULL;
  for (int i= 0; parser->peekFor(parser, stopAt, 0) != NULL; i++) 
  {
    if(stmts == NULL){
      stmts= create_stm(parser);
      push_Statement_node(&(stmts), stmts);
      temp = stmsts;
      continue;
    }
    temp = create_stm(parser);
    push_Statement_node(&(temp), temp);
    // stmt->gen(generate, stmt);
  }
  return stmts;
}

void Parse(Parser *parser, int stopAt) 
{
  parser->m_res = Parse_Statement(parser, stopAt);
}



