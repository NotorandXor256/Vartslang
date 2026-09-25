#ifndef GRAMMER_H
#define GRAMMER_H
#include "lexer.h"
#define GEN_FUN(name, start_, end_)       \
static int name(TokenType tok)                             \
{                                                   \
  return tok >= (int)(start_) && (tok < (int)(end_));         \
} 

GEN_FUN(is_keyword,(int)FUN,(int)ASG)
GEN_FUN(is_type, (int)I32,(int)ASG)
GEN_FUN(is_operator, (int)ASG, (int) ARW)
GEN_FUN(is_operator_infix,(int) ASG,(int) IN)
GEN_FUN(is_operator_assign,(int) ASG,(int) MNS) 
GEN_FUN(is_operator_arthimatic,(int) MNS,(int) GT)
GEN_FUN(is_operator_relational, (int) GT, (int) NEQ)
GEN_FUN(is_operator_logical, (int) NOT, (int) BNT)
GEN_FUN(is_operator_bitwise, (int) BNT, (int) SHR)
GEN_FUN(is_operator_membership, (int) IN, (int) PMS)
GEN_FUN(is_operator_unary, (int) PMS, (int) DOT)
GEN_FUN(is_operator_member_access, (int) DOT, (int) TCO)
GEN_FUN(is_operator_type_cast, (int) TCO, (int) ARW)
GEN_FUN(is_puctation, (int) ARW,(int) INT)
GEN_FUN(is_liter,(int) INT,(int) COLLECTION)
GEN_FUN(is_identifer,(int) ID,(int) EOF_)


typedef struct Block Block;
typedef struct Program Program;

typedef Token Type;
typedef Token Identifer;

typedef struct expression 
{
  int(*evaluate)(struct expression*);
} expression;

typedef struct Arrary 
{
    
} Arrary;

//#include "parser.h"
typedef struct {
  Type *type;
  Identifer *id;
  expression expr;
} Declear_var;

typedef struct {
  Identifer *id;
  expression expr;
} Assign_Var;

typedef struct {
  expression *type;
  Identifer *id;
   
} Declear_Arr;

typedef struct {
  Type *type;
  Identifer id;
  expression expr;
} Assign_Arr;

typedef Declear_var arguments;
typedef struct {
  int is_extern;
  Type *type;
  Identifer *id;
  arguments *args; 
  union {
    Block *b; 
    Identifer *func_ptr; // if assigned value of an other function
  } code;
  // expression ret; // return statement
} Declear_Func;

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
  Declear_var Var;
  Declear_Arr Arr;
  Declear_Func Func;
  // Declear_Struct Struct;
  // Declear_Enum Enum;
  // Declear_Class Class;
} Declear_Stm;

typedef struct {
  Assign_Var Var;
  Assign_Arr Arr;
  // Assign_Func Func;
  // Assign_Struct Struct;
  // Assign_Enum Enum;
  // Assign_Class Class;
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
  Token *output_type;
  Token *id;
} Func_Call_Stm;

typedef struct {
  Assign_Stm assign_stm;
  Func_Call_Stm func_call_stm;
} Simple_Stm;

typedef union {
  If_Stm if_stm;
  Lp_Stm lp_stm;
  Do_Lp_Stm do_lp_stm;
  For_Each_Loop for_each_loop;
} Compound_Stm;

struct block {
  Compound_Stm *statements;
};

typedef union {
  Simple_Stm *stament;
  Compound_Stm *statements;
} Statement;

struct Program {
  Statement *stms; 
};

#endif
