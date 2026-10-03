#include<stdio.h>
#include<stdlib.h>
#include "file.h"
#include "asserts.h"

src_code read_file(String filename) {
  FILE *f = fopen(filename,"r");

  if (!f) {
    printf("ERROR: in read_file");
    src_code code = {
      .src = NULL,
      .len = 0
    };
    return code;
  } 
  fseek(f,0, SEEK_END);
  size_t size = ftell(f);
  rewind(f);

  String buffer = malloc(size +1);
  if (!buffer) {
    fclose(f); 
    printf("ERROR: in read_file");
    src_code code = {
      .src = NULL,
      .len = 0
    };
    return code;
  }
  fread(buffer, 1, size, f);
  buffer[size] = '\0';
  
  fclose(f);
  src_code code = {
    .src = buffer,
    .len = size
  };

  return code;
}
