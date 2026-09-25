# Vartslang's grammer

<program> ::= (<compound_stm> | <simple_stm>)*

<simple_stm> ::= <decleartive_stm> | <assign_stm> | <return_stm> | <function_call_stm> | <import_stm>

<compound_stm> ::=  <if_stm> | <lp_stm> | <do_lp_stm> | <for_each_loop>   

<decleartive_stm> ::= <declear/variable> | <declear/array> | <declear/function>> | <declear/struct> | <declear/enum> | <declear/class> ";"

<declear/variable> :: <type> <identifer> (<op/assign> <expr>)? 

<declear/array> ::=  "<-[]->" "{" <expr>  ( "," <expr> )* "}" <identifer> (<op/assign> "[]" <array> )?

<array> ::= "{" ( ( <expr> | <array> ) ( "," <expr> | <array> )* )? "}" 

<declear/function> ::= "<=$=>"? "<-@->" "{" <type> "}" <identifer>  (<op/assign> "@" "{" <declear/variable>? ("," <declear/variable> )* "}" <arrow> <block> )?

<declear/struct> ::= 
"<-<+>->" "{" "}" <identifer> 
( 
    <op/assign> 
    "<+>" "{" "}" <arrow> 
    "{" 
        ( <decleartive_stm> ";" )* 

    "}"
)? 

<declear/enum> ::= 
"<-<|>->" "{" "}" <identifer> (<op/assign> "<|>" "{" "}" <arrow> 
"{" 
    (identifer (<op/assign> <literal>)? )?
    (
        "," <identifer> (<op/assign> <literal>)? 
    )* 
"}" )?

<declear/class> ::=
"<-<:>->" "{" "}" <identifer> ( <op/assign_stm> 
"<:>" "{" ( <identifer> ("," <identifer> )* ) | E "}" <arrow> <block>  )? 

<if_stm> ::= 
    "?" "{" <expr> "}" <arrow> <block> 
    ( <arrow> "?" "{" <expr> "}" <arrow> <block> )* 
    ( <arrow> <block>)?

<lp_stm> ::= 
    "<-?->" "{" ( <assign_stm> ("," <assign_stm>)* )? ";" 
    <expr>? ";" 
    (<expr> ( ","<expr> )* )? "}" 
    <arrow> <block>

<do_lp_stm> ::= <block> <arrow> "<-?->" "{" 
    ( <assign_stm> ("," <assign_stm>)* )? ";" 
    <expr>? ";" 
    ( <expr> ( <expr> ",")* )? "}"

<for_each_loop> ::= "<-:->" "{" <type> <identifer> "<-:" <identifer> "}" <arrow> <block>

<function_call_stm> ::= <function_call> ";"

<block> ::= "{" (<compound_stm>)* "}"

<assign_stm> ::= <assign/variable> | <assign/array> | <assign/function> | <assign/struct> | <assign/enum> | <assign/class> ";"

<assign/variable> ::= <identifer> <op/assign> <expr> 

<assign/array> ::= <identifer> (<op/assign>  "[]" ( <arrary> | <expr> ) )? 

<assign/function> ::=  <identifer> (<op/assign> <block> ) 

<assign/struct> ::= 
"<-<+>->" "{" "}" <identifer> 
( 
    <op/assign> 
    "<+>" "{" "}" <arrow> 
    ( 
        "{" ( <assign_stm> ";" )* "}" |
        identifer |
        E
    ) 
)?

<assign/enum> ::= 
"<-<|>->" "{" "}" <identifer> <op/assign> "<|>" "{" "}" <arrow> 
"{" 
   (
        (<identifer> | <assign_stm>) |
        ("," ( <identifer> | <assign_stm> ))*
   )?
"}"

<assign/class> ::= <identifer> <op/assign_stm> 
                    "<:>" "{" ( <identifer> ("," <identifer> )* ) | E "}" <arrow> <block> 

<type> ::= "i32" | "i64" | "f32" | "f64" | "u8" | "b1"

<expr> ::= <primary_expr> | <unary_expr> | <binary_expr> | <grouping>

<prefix> ::= <literal> | <unary> | <identifer> | <grouping>

<grouping> ::= "(" <expr> ")"

<unary_expr> ::= <op/prefix> ( <primary_expr> | "(" <unary_expr> ")" ) | 
                ( <primary_expr> | "(" <unary_expr> ")" ) <op/suffix> |
                <op/other> <grouping>

<binary_expr> ::= <expr> <oprator> <expr>

<oprator> ::= <bin_op> | <prefix_op> | <postfix_op>

<bin_op> ::= <op/assign> | <op/arthimatic> | <op/logical> | <op/relation> | <op/membership> | <op/bitwise> 

<unary_op> ::= <prefix_op> | <postfix_op>

<prefix_op> ::= <prefix_op/> | "++" | "--"

<postfix_op> ::= "++" | "--" 

<prefix_op/> ::= "+" | "-" | "!" | "~"

<op/assign> ::= "<-"

<op/arthimatic> ::= "+" | "-" | "*" | "/" | "%" 

<op/logical> ::= "||" | "&&" | "!"

<op/relation> ::= "==" | "!=" | ">=" | "<=" | ">" | "<"

<op/membership> ::= "<-:"

<op/bitwise> ::= "~" | "&" | "^~^" | "|"

<function_call> ::= <identifer> ( "<|" "{" (<expr> ("," <expr>)* ("," <assign_var_stm> ("," <assign_var_stm>)*)? )?  "}" )*

<primary_expr> ::= <literal> | <identifer> | <function_call>

<literal> ::= <numral> | <STRING> | "<:+:>" | "<:-:>" | "><"

<identifer> ::= ( "A" | "B" | ... | "Z" | "a" | "b" | ... | "z" | "_") 
                ( "A" | "B" | ... | "Z" | "a" | "b" | ... | "z" | "_" | <digit>)*

<numral> ::= <digit> (<digit>)*

<digit> ::= "0" | "1" | "2" | "3" | "4" | "5" | "6" | "7" | "8" | "9"

<STRING> ::= """ (ascii_charaters)* """

<arrow> ::= "->"


## definitions

term = an peice of expr separted by operator
factor = literal that is
