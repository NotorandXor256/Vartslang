#include<stdio.h>
#include<stdlib.h>
#include<stdarg.h>

#include "asserts.h"

uintptr_t *a(Arena *arena, size_t size) {
  if(size > arena->size - arena->offset) {
    printL("space not left in arena, %d\n", arena->size - arena->offset);
    return NULL;
  }
  uintptr_t *temp = arena->data + arena->offset;
  arena->offset += size;
  return temp;
}

uintptr_t *allocate(Arena_node *arena,size_t size)
{
  if(size > (arena->val.size)) {
    printE("can't allocate this big memory");
    return NULL;
  }
  if(size > arena->val.size - arena->val.offset){
    Arena temp = {
      .data = (uintptr)malloc(arena->val.size), 
      .size = arena->val.size,
      .offset = 0
    };
    arena = push_Arena_node(&(arena),new_Arena_node(temp));
  } 
  return a(&(arena->val), size);
}

void printE_impl(CString func, CString file,int line, CString message, ...) {

    va_list args;

    printf("ERROR: In function '%s' In file '%s' in line %d \n",func,file, line);

    va_start(args, message);
    printf("ERROR: ");
    vprintf(message, args);
    va_end(args);
    printf("\t\n");
}

void printL_impl(CString func, CString file,int line, CString message, ...) {

    va_list args;

    va_start(args, message);
    printf("LOG:Func['%s']:FILE['%s']:LINE[%d]: ",func,file,line);
    vprintf(message, args);
    va_end(args);
    printf("\t\n");
}
