#include <stdio.h>
#include <stdlib.h>

#include "asserts.h"
#include "generator.h"
#include "file.h"

// size_t Generate_ (Generator *gen)
// {
//   gen-add_section_data  
// }

void Generate(Generator *generator) 
{
  if(generator->m_res == NULL) printE("File opening opration failed");
  for (int i =0; generator->m_buf != NULL; i++) 
  {
    generator->m_buf->val.gen(generator, &(generator->m_buf->val));
  }
  for (int i = 0;generator->code->bss != NULL; i++)
  {
    fprintf(generator->m_res, generator->code->bss->val);
    generator->code->bss = next_Section_bss(generator->code->bss);
  }
  for (int i = 0; generator->code->data != NULL; i++)
  {
    fprintf(generator->m_res, generator->code->data->val);
    generator->code->data = next_Section_data(generator->code->data);
  }
  for (int i = 0; generator->code->text != NULL; i++)
  {
    fprintf(generator->m_res, generator->code->text->val);
    generator->code->text = next_Section_text(generator->code->text);
  }
}
// void 
