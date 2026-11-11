#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "tokens.h"
#include "asserts.h"
#include "file.h"
#include "grammer.h"
#include "lexer.h"
#include "parser.h"
#include "generator.h"

int main(int argc, char *argv[])
{
  if(argc != 2) 
  {
    printf("No input file given\n");
    printE("NO INPUT FILE GIVEN");
    return EXIT_FAILURE;
  }
  src_code content = read_file(argv[1]);
  if(content.src == NULL) 
  {
    printf("file error\n");
    return EXIT_FAILURE;
  }
  
  lexer src = {
    .m_buf = NULL,
    .m_index= 0,
    .src = content,
    .m_res = NULL 
  };
  
  tokenize(&src);
  if(src.m_res == NULL)
  {
    printE("src.M-res is null");
    return -1;
  }

  size_t size = 4*1024 * sizeof(uintptr_t);

  Arena_node arena = (Arena_node){
    .val = {
      .data = (uintptr_t *) malloc(size),
      .malloc = allocate,
      .size = size,
      .offset=0
    },
    .next_el = NULL
  };

  Parser tokens = (Parser){
    .m_buf = src.m_res,
    .arena = &arena,
    .peek = &peek_token,
    .peekFor = &peekFor_token,
    .consume = &consume_token,
    .TryConsume = &TryConsume_token,
    .TryConsume_err = &TryConsume_err_token,
    .m_res = NULL
  };
  if(tokens.m_buf == NULL) 
  {
    printE("tokens.M_buf is null");
    return -1;
  }
  Parse(&tokens, EOF_);
  // Generator genrator = (Generator){
  // };
  // sprintf();
  // system();
  // system();
  // system();
  free(src.src.src);
  return 0;
}
