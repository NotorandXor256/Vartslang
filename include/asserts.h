#ifndef ASSERTS_H
#define ASSERTS_H

#include<stdio.h>
#include<stdlib.h>

#include "tokens.h"

typedef char *String;
typedef const char *CString;


void printE_impl(CString func,CString file,int line, CString message, ...);

void printL_impl(CString func, CString file, int line, CString message, ...);

#define printE(msg, ...) \
    printE_impl(__func__, __FILE__, __LINE__, msg, ##__VA_ARGS__)

#define printL(msg, ...) \
    printL_impl(__func__, __FILE__, __LINE__, msg, ##__VA_ARGS__)


#define LINKED_LIST(type, name)      \
typedef struct name {          \
  type val;                    \
  struct name *next_el;     \
} name;                 \
static name *new_##name(type val) {   \
  name *temp = (name *) malloc(sizeof(name));\
  temp->val = val; \
  temp->next_el = NULL; \
  return temp; \
} \
static name *next_##name(name *cur){ \
  if(cur->next_el != NULL) return cur->next_el; \
  printE("there is no next memeber");   \
  return NULL;   \
}     \
static name *push_##name(name **cur,name *next_el) {\
  if(cur == NULL) { \
    perror("Node is NULL\n"); \
    exit(EXIT_FAILURE); \
    return NULL; \
  } \
  if(*cur == NULL) {  \
    *cur = next_el;   \
    return next_el;    \
  }\
  if((*cur)->next_el == NULL) { \
    (*cur)->next_el = next_el; \
    return next_el; \
  } \
  else {  \
    printL("It didn't push the memeber"); \
  } \
  name *temp_ptr = next_##name(*cur); \
  return push_##name(&temp_ptr,next_el);\
}\
static void show_item_##name(name *n) { \
  if(n == NULL) { \
    printf("----\n"); \
    return; \
  }  \
  show_item_##name(next_##name(n)); \
} \

// type, identifer
LINKED_LIST(char,chr_node);
typedef struct {
  String src; 
  size_t len;
} src_code;

typedef struct {
  TokenName tok;
  TokenType type;
  int is_null;
  union {
    String str_value;
    int numral_value; 
  } value; 
} Token;

LINKED_LIST(Token,Token_node);

LINKED_LIST(Token_node, Token_2Dnode);

typedef struct {
  chr_node *m_buf; 
  size_t m_index;
  src_code src;
  Token_node *m_res; // linked list of tokens
} lexer;


#endif
