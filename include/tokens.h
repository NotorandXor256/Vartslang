#ifndef TOKENS_H

#define TOKENS_H
typedef enum {
  // Keywords
  IMP=100,    // <+$+>
  FUN,        // <-@->
  LOP,        // <-?->
  FEL,        // <-:-> 
  LST,        // <-[]->
  STC,        // <-<+>->
  ENM,        // <-<|>->
  CLS,        // <-<:>->
  ARG,        // @  
  CAL,        // <|
  IF,         // ?
  RET,        // ^^^
  LIT,        // []
  STA,        // <+>
  ENA,        // <|>
  ITA,        // <:>
  I32,
  I64,
  F32,
  F64,
  U8,
  B1,
    
  // operator/assign
  ASG=200,   // <-
  // operator/arthimatic
  MNS = 220,
  PLS,
  MUL,
  DIV,
  INC,       // ++
  DEC,       // -- 
  // operator/relational
  GT = 240,  // >
  LT,        // <
  GTE,       // >=
  LTE,       // <=
  EQU,       // ==
  NEQ,       // !=
  // operator/logical
  NOT = 260, // !
  AND,       // /\ /
  OR,        // \/
  // operator/bitwise
  BNT = 280,       // ~
  BND,       // &
  BOR,       // | 
  XOR,       // ^ 
  SHL,       // <<
  SHR,       // >>
  // operator/membership
  IN = 290,  // <-:
  // operator/unary
  PMS, 
  // operator/member_access
  DOT,       // .
  // operator/type_cast
  TCO,       // (int), (float), (bool)

  //puctation
  ARW=300,   // ->
  SMI,       // ;
  OCR, CCR,  // { }
  CMA,       // ,
  NL,        // \n

  // liter 
  INT = 400,
  FLT,
  CHR,
  STR,
  TRU, 
  FLS,
  NULL_,

  COLLECTION,
  
  //identifer
  ID = 500,

  // speical 
  EOF_
} TokenName;

typedef enum {
  KEYWORD= 1000,
  TYPE,
  OPRATOR,
  OP_ASSIGN,
  OP_ARTHIMATIC,
  OP_RELATIONAL,
  OP_LOGICAL,
  OP_BITWISE,
  OP_MEMBERSHIP,
  OP_MEMBER_ACCESS,
  OP_UNARY,
  OP_TYPE_CAST,
  PUNCTATION,
  LITERAL,
  IDENTIFER,
  SPEICAL
} TokenType;



#endif // TOKENS_H
