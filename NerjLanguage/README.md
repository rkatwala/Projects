# CS152 compiler for Nerj
#Author: Rahul Katwala
### Overview
Experimental Language: Nerj

Experimental Language Extension: .nerj

Compiler Name: NERJ-C

## Language Features

| Language Feature  | Code Examples |
| ------------- | ------------- |
| Integer Scalar variables  | num a; num b; num a,b;  |
| One-dimensional arrays of integers  | array(4)[num]arr = [1,2,3,4] <br> format: array(size)[type]name is [element_1...element_(size-1)] |
|Assignment statements|"is" <br>ex. num a is 3;| 
|Arithmetic operators (addition)|"plus" <br>ex. a plus b|
|Arithmetic operators (subtraction)|"minus" <br>ex. a minus b|
|Arithmetic operators (multiplication)|"times" <br>ex. a times b|
|Arithmetic operators (division)|"divby" <br>ex. a divby b|
|Relational operators (<) |"lt" <br>ex. a lt b|
|Relational operators (>) |"gt" <br>ex. a gt b|
|Relational operators (<=) |"lte" <br>ex. a lte b|
|Relational operators (>=) |"gte" <br>ex. a gte b|
|Relational operators (==) |"eq" <br>ex. a eq b|
|Relational operators (!=) |"neq" <br>ex. a neq b|
|While loop (including "break" and "continue" loop control statements)|while (num a neq num b) do { <br> …<br>proceed;<br>…<br>leave;<br>}|
|Return|ret a; ret b;|
|If-else-then statements|if (a neq b) then {<br>…<br>}<br>else {<br>…<br>}|
|Function definitions (including "return" statement)|func num exampleFunction: num param { <br> ...<br>ret param;<br> }|
|Read and write statements |read(var)<br>write(var)|
|Comments|#this indicates a comment|
|Whitespace|Ignored|
|Case-sensitive|Yes|
|Identifier|Cannot start with a number or special character. Cannot use keywords as identifiers.|
|Numbers|Must be an integer (i.e. '1', '2', '543)|


## Lexical Pattern and corresponding tokens

| Lexical Pattern in nerj  | Tokens |
| ------------- | ------------- |
|Reserved Words|
|num|INTEGER|
|array|ARRAY|
|while|WHILE|
|do|DO|
|proceed|CONT|
|leave|BREAK|
|read|READ|
|write|WRITE|
|if|IF|
|then|THEN|
|else|ELSE|
|func|FUNCTION|
|ret|RETURN|
|Arithmetic Operators|
|plus|ADD|
|minus|SUB|
|times|MULT|
|divby|DIV|
|Comparison Operators|
|lt|LT|
|gt|GT|
|lte|LTE|
|gte|GTE|
|neq|NEQ|
|eq|EQ|
|is |ASSIGN
|Other Special Symbols|
|;|SEMICOLON|
|,|COMMA|
|\(|LEFT_PAREN
|\)|RIGHT_PAREN
|\[|LEFT_SQR_BRACKET
|\]|RIGHT_SQR_BRACKET
|\{|BEGIN_BLOCK|
|\}|END_BLOCK|
|Identifiers and Numbers|
|identifier("hat", "a", "POI", "U_2")|IDENT XXXX [XXXX is the identifier]|
|number("1", "342", "5302", "0")|NUMBER XXXX [XXXX is the number]|
