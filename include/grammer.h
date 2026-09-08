#ifndef GRAMMER_H
#define GRAMMER_H
#include "lexer.h"
#define GEN_FUN(name, start_, end_)       \
  int name(TokenType tok)                             \
  {                                                   \
    return tok >= (int)(start_) && (tok < (int)(end_));         \
  } 

typedef struct Block Block;

typedef struct  {
  Token *type; 
} Type;

typedef struct {
  Token *identifer; 
} Identifer;

typedef struct expression 
{
  int(*evaluate)(struct expression*);
} expression;


#include "parser.h"

typedef struct {
  Type type;
  Identifer id;
  expression expr;
} Assign_Var;

typedef struct {
  Type *type;
  Identifer id;
  expression expr;
} Assign_Arr;

typedef struct Assign_Func {
  Type type;
  Identifer id;
  union {
    Block *b; 
    struct Assign_Func *func_ptr;
  } code;
} Assign_Func;

typedef struct {
  Identifer id; 
  Assign_Var *assign_stm;
} Assign_Struct;

typedef struct {
  Identifer id; 
  
} Assign_Enum;

typedef struct {
  Identifer id;
} Assign_Class;

typedef struct {
  Assign_Var Var;
  Assign_Arr Arr;
  Assign_Func Func;
  Assign_Struct Struct;
  Assign_Enum Enum;
  Assign_Class Class;
} Assign_Stm;

typedef struct If_Stm {
  expression *expr;
  Block *b;
  struct If_Stm *next;
} If_Stm;

typedef struct  {
  Assign_Stm *assign_stm;
  expression condition;   
  expression *update;
  Block *b;
} Lp_Stm;

typedef struct {
  Assign_Stm *assign_stm;
  expression condition;   
  expression *update;
  Block *b;
} Do_Lp_Stm;

typedef struct {
   
} For_Each_Loop;

typedef struct {

} Func_Call_Stm;

typedef union {
  Assign_Stm assign_stm;
  If_Stm if_stm;
  Lp_Stm lp_stm;
  Do_Lp_Stm do_lp_stm;
  For_Each_Loop for_each_loop;
  Func_Call_Stm func_call_stm;
} Compound_Stm;

struct block {
  Compound_Stm *statements;
};

#endif
