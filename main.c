#include <stdio.h>
#include <stdlib.h>

#include "asserts.h"
#include "file.h"
#include "grammer.h"
#include "asserts.h"
#include "lexer.h"
#include "parser.h"

int main(int argc, char* argv[]) {
  if(argc != 2) {
    printf("No input file given\n");
    printE("NO INPUT FILE GIVEN");
    return EXIT_FAILURE;
  }
  src_code content = read_file(argv[1]);
  if(content.src == NULL) {
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
  if(src.m_res == NULL){
    printE("src.M-res is null");
    return -1;
  }
  Parser tokens = {
    .m_buf = src.m_res,
    .peek = &peek_token,
    .peekFor = &peekFor_token,
    .consume = &consume_token,
    .TryConsume = &TryConsume_token,
    .m_res = NULL,
  };
  if(tokens.m_buf == NULL){
    printE("tokens.M-res is null");
    return -1;
  }
  Parse(&tokens);
  free(src.src.src);
  return 0;
}
