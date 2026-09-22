#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "lexer.h"
#include "asserts.h"

char peek_char(lexer *src, int offset) {
  // IMPORTANT - this function will have no safe grard
  // peek func returns the char m_index + offset
  // without advencing the cursor
  if ((src->m_index + offset) >= src->src.len)
    return '\0';
  return *(src->src.src + src->m_index + offset);
}

char consume_char(lexer *src) {
  // return the charater at m_index and increment
  // the index by one
  if (src->m_index >= src->src.len) return '\0';
  src->m_index++;
  return *(src->src.src + src->m_index - 1);
}

Token to_token(const String token_src) {
  // Keyword
  if      (strcmp(token_src, "<+$+>") == 0)     return (Token){IMP,KEYWORD,1,{NULL}};
  else if (strcmp(token_src, "<-@->") == 0)     return (Token){F32,KEYWORD,1,{NULL}};
  else if (strcmp(token_src, "<-?->") == 0)     return (Token){LOP,KEYWORD,1,{NULL}};
  else if (strcmp(token_src, "<-:->") == 0)     return (Token){FEL,KEYWORD,1,{NULL}};
  else if (strcmp(token_src, "<-[]->") == 0)    return (Token){LST,KEYWORD,1,{NULL}};
  else if (strcmp(token_src, "<-<+>->") == 0)   return (Token){STC,KEYWORD,1,{NULL}};
  else if (strcmp(token_src, "<-<|>->") == 0)   return (Token){ENM,KEYWORD,1,{NULL}};
  else if (strcmp(token_src, "<-<:>->") == 0)   return (Token){CLS,KEYWORD,1,{NULL}};
  else if (strcmp(token_src, "@") == 0)         return (Token){ARG,KEYWORD,1,{NULL}};
  else if (strcmp(token_src, "<|") == 0)        return (Token){CAL,KEYWORD,1,{NULL}};
  else if (strcmp(token_src, "?") == 0)         return (Token){IF, KEYWORD,1,{NULL}};
  else if (strcmp(token_src, "^^^") == 0)       return (Token){RET,KEYWORD,1,{NULL}};
  else if (strcmp(token_src, "[]")== 0 )        return (Token){LIT,KEYWORD,1,{NULL}};
  else if (strcmp(token_src, "<+>")== 0 )       return (Token){STA,KEYWORD,1,{NULL}};
  else if (strcmp(token_src, "<|>")== 0 )       return (Token){ENA,KEYWORD,1,{NULL}};
  else if (strcmp(token_src, "<:>")== 0 )       return (Token){ITA,KEYWORD,1,{NULL}};
  else if (strcmp(token_src, "i32") == 0)       return (Token){I32,TYPE,1,{NULL}};
  else if (strcmp(token_src, "i64") == 0)       return (Token){I64,TYPE,1,{NULL}};
  else if (strcmp(token_src, "f32") == 0)       return (Token){F32,TYPE,1,{NULL}};
  else if (strcmp(token_src, "f64") == 0)       return (Token){F64,TYPE,1,{NULL}};
  else if (strcmp(token_src, "u8") == 0)        return (Token){U8, TYPE,1,{NULL}};
  else if (strcmp(token_src, "b1") == 0)        return (Token){B1, TYPE,1,{NULL}};
 

  // operator / assign
  else if (strcmp(token_src, "<-") == 0)        return (Token){ASG,OP_ASSIGN,1,{NULL}};

  // operator/arthimatic
  else if (strcmp(token_src, "+") == 0)         return (Token){PLS,OP_ARTHIMATIC,1,{NULL}};
  else if (strcmp(token_src, "-") == 0)         return (Token){MNS,OP_ARTHIMATIC,1,{NULL}};
  else if (strcmp(token_src, "*") == 0)         return (Token){MUL,OP_ARTHIMATIC,1,{NULL}};
  else if (strcmp(token_src, "/") == 0)         return (Token){DIV,OP_ARTHIMATIC,1,{NULL}};
  else if (strcmp(token_src, "++") == 0)        return (Token){INC,OP_ARTHIMATIC,1,{NULL}}; 
  else if (strcmp(token_src, "--") == 0)        return (Token){DEC,OP_ARTHIMATIC,1,{NULL}};

  // operator/relational
  else if (strcmp(token_src, ">") == 0)         return (Token){GT ,OP_RELATIONAL,1,{NULL}};
  else if (strcmp(token_src, "<") == 0)         return (Token){LT ,OP_RELATIONAL,1,{NULL}};
  else if (strcmp(token_src, ">=") == 0)        return (Token){GTE,OP_RELATIONAL,1,{NULL}};
  else if (strcmp(token_src, "<=") == 0)        return (Token){LTE,OP_RELATIONAL,1,{NULL}};
  else if (strcmp(token_src, "==") == 0)        return (Token){EQU,OP_RELATIONAL,1,{NULL}};
  else if (strcmp(token_src, "!=") == 0)        return (Token){NEQ,OP_RELATIONAL,1,{NULL}}; 

  // operator/logical
  else if (strcmp(token_src, "!") == 0)         return (Token){NOT,OP_LOGICAL,1,{NULL}};
  else if (strcmp(token_src, "/\\") == 0)       return (Token){AND,OP_LOGICAL,1,{NULL}};
  else if (strcmp(token_src, "\\/") == 0)       return (Token){OR ,OP_LOGICAL,1,{NULL}};

  //operator/bitwise
  else if (strcmp(token_src, "~") == 0)         return (Token){BNT,OP_BITWISE,1,{NULL}};
  else if (strcmp(token_src, "&") == 0)         return (Token){BND,OP_BITWISE,1,{NULL}};
  else if (strcmp(token_src, "|") == 0)         return (Token){BOR,OP_BITWISE,1,{NULL}};
  else if (strcmp(token_src, "^") == 0)         return (Token){XOR,OP_BITWISE,1,{NULL}};
  else if (strcmp(token_src, "<<") == 0)        return (Token){SHL,OP_BITWISE,1,{NULL}};
  else if (strcmp(token_src, ">>") == 0)        return (Token){SHR,OP_BITWISE,1,{NULL}};

  // operator/membership
  else if (strcmp(token_src, "<-:")==0)         return (Token){IN,OP_MEMBERSHIP,1,{NULL}};

  // operator/member access
  else if (strcmp(token_src, ".") == 0)         return (Token){DOT,OP_MEMBER_ACCESS,1,{NULL}};

  // puncutations
  else if (strcmp(token_src, "->") == 0)        return (Token){ARW,PUNCTATION,1,{NULL}};
  else if (strcmp(token_src, ";") == 0)         return (Token){SMI,PUNCTATION,1,{NULL}};
  else if (strcmp(token_src, "{") == 0)         return (Token){OCR,PUNCTATION,1,{NULL}};
  else if (strcmp(token_src, "}") == 0)         return (Token){CCR,PUNCTATION,1,{NULL}};
  else if (strcmp(token_src, ",") == 0)         return (Token){CMA,PUNCTATION,1,{NULL}};
  else if (strcmp(token_src, "\n") == 0)        return (Token){NL ,PUNCTATION,1,{NULL}};
  
  //literals
  else if (isdigit(*token_src))                 return (Token){INT,LITERAL,0,{.numral_value = atoi(token_src)}};
  else if (strcmp(token_src, ":+:") == 0)       return (Token){TRU,LITERAL,0,{.numral_value = 1}};
  else if (strcmp(token_src, ":-:") == 0)       return (Token){FLS,LITERAL,0,{.numral_value= 0}};
  else if (strcmp(token_src, "><") == 0)        return (Token){NULL_,LITERAL,0,{NULL}};

  else if (isalpha(*token_src))                 return (Token){ID, IDENTIFER,0, {.str_value = token_src}};

  else {
    printf("lexer.c to_token function: unknown token %s, %d, %d\n", token_src,*token_src,*(token_src+1));
    exit(-1);
    return (Token){0,0,0,{NULL}}; // make sure you define this
  }
}

Token ret_token(lexer *src, int (*fun)(char), int offset) {
  int lenght = 0;
  chr_node **temp_ptr = &(src->m_buf); 
  for (int i = 0;fun(peek_char(src,offset));i++) {
    if (i > 17) break;
    char temp_char_var = consume_char(src);
    push_chr_node(temp_ptr,new_chr_node(temp_char_var));
    lenght++;
  }
  String str_buf = (String) malloc((lenght * sizeof(char)) + 1);
  for (int i = 0; src->m_buf != NULL; i++) {
    *(str_buf + i) = src->m_buf->val; //
    printL("value of char: %c\n", src->m_buf->val);
    src->m_buf = next_chr_node(src->m_buf);
    if (i > lenght) {
      printf("\n");
      printE("tonken lenght is e then buffer by %d", i - lenght);
      break;
    }
  }
  *(str_buf + lenght) = '\0';
  printf("str_buf : %s\n",str_buf);

  Token tok = to_token(str_buf);
  free(str_buf);
  str_buf = NULL;
  return tok;
}

int alpha(char chr) {
  return (
    isalpha(chr) || 
    isdigit(chr) || 
    chr == '_'
  );
}

int numa(char chr) {
  return (
    isdigit(chr) || 
    chr == '_'
  );
}

int is_pucuation(char chr){
  return (
    chr == ';' || 
    chr == '{' || 
    chr == '}' || 
    chr == ',' || 
    chr == '.' || 
    chr == ';'
  );
}
int extr(char chr) {
  return !(
    chr == ' ' ||
    isdigit(chr) ||
    isalpha(chr) ||
    is_pucuation(chr)
  );
}



int reverse_puc(char chr) {
  return !is_pucuation(chr);
}

void tokenize(lexer *src) { // make this return list of tokens somehow
  printf("reading source code\n");
  for (int i = 0; src->m_index < src->src.len; i++) 
  {
    if(i>500) break;
    if (isalpha(peek_char(src, 0))) 
    {
      Token_node *tok = new_Token_node(ret_token(src,alpha,0));
      push_Token_node(&(src->m_res),tok);
    } 
    else if (isdigit(peek_char(src, 0))) 
    {
      Token_node *tok = new_Token_node(ret_token(src,numa,0));
      push_Token_node(&(src->m_res),tok);
    } 
    else if (is_pucuation(peek_char(src,0)))
    {
      Token_node *tok = new_Token_node(ret_token(src,reverse_puc,-1));
      push_Token_node(&(src->m_res), tok);
    } 
    else if (!(peek_char(src,0) == ' ' || peek_char(src,0) == '\n')) 
    {
      Token_node *tok = new_Token_node(ret_token(src,extr,0));
      push_Token_node(&(src->m_res),tok);
    } 
    else 
    {
      consume_char(src);
    }
  }
  Token_node *end = (Token_node *)malloc(sizeof(Token_node));
  end->val = (Token){EOF_, SPEICAL,1,{NULL}};
  end->next_el = NULL;
  push_Token_node(&(src->m_res),end);
  printf("__________\n");
  
}
