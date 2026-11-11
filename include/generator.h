#ifndef GENERATOR_H
#define GENERATOR_H
#include "file.h"
#include "asserts.h"
#include "parser.h"


LINKED_LIST_ARENA(String, Section_bss);
LINKED_LIST_ARENA(String, Section_data);
LINKED_LIST_ARENA(String, Section_text);

typedef struct Asm_Code{
  Section_bss *bss; 
  Section_data *data;
  Section_text *text;
} Asm_Code;

typedef struct {
  Statement_node *m_buf;
  Arena_node *arena;
  Asm_Code *code; 
  FILE *m_res;  
} Generator;

#endif // !GENERATOR_H
