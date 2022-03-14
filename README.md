## Requirements

Design an original programming language using YACC. Your language should include: </br></br>
:heavy_check_mark: predefined types  ( int , float, char,  string, bool), array types  and user defined data types (similar to classes in object orientated languages, but with your own syntax); provide specific syntax to allow initialization and use of variables of user defined types </br>
:heavy_check_mark: variable declarations/definition, constant definitions, function definitions </br>
:heavy_check_mark: control statements (if, for, while, etc.), assignment statements </br>
:heavy_check_mark: assignment statements should be of the form: left_value  = expression (where left_value can be an identifier, an element of an array, or anything else specific to your language) </br>
:heavy_check_mark: arithmetic and boolean expressions </br>
:heavy_check_mark: function calls which can have as parameters: expressions, other function calls, identifiers, constants, </br> </br>


Your language should include a  predefined function Print (with two parameters, a string and an int or bool or float (eg: Print(“value of expression x+2  is:”,x+2) )</br>
Your programs should be structured in 3 sections: one section for global variables, another section for functions and user defined data types and a special function representing the entry point of the programm </br>

Your yacc analyzer should: </br>
:heavy_check_mark: 1) do the syntactic analysis of the program </br>
:heavy_check_mark: 2) create a symbol  table for every input source program in your language, which should include: </br>
information regarding variable or constant identifiers  ( type, value – for identifiers having a predefined type, scope: global definition,defined inside a function , defined inside a user defined type, or any other situation specific to your language) </br>
information regarding function identifiers (the returned type, the type and and name of each formal parameter, whether the function is a  method in a  class etc) </br>
 The symbol table should be printable in two files: symbol_table.txt and symbol_table_functions.txt (for functions) </br>
 :heavy_check_mark: 3) provide semantic analysis and check that: </br>
-   any variable that appears in a program has been previously defined and any function that is 
called has been defined  </br>
- a variable should not be declared more than once; </br>                  
- a function is not defined more than once with the same signature (function overloading should be permitted) </br>
- the left side of an assignment has the same type as the right side (the left side can be an element of an array, an identifier etc)  </br>
- the parameters of a function call have the types from the function definition </br>

Detailed error messages should be provided if these conditions do not hold (e.g. which variable is not defined or it is defined twice and the programm line); </br>
:heavy_check_mark: 4) build abstract syntax trees (AST) for the integer expressions in a program;  </br>
if a program is syntactically and semantically correct and the expr type is int , for every call of the form Print(str,expr) , the AST for the expression will be evaluated and the actual value of expr will be printed. </br>
Also, for every assignment instruction left_value = expr (left_value is an identifier or element of an array with int type), the AST will be evaluated and its value will be assigned to the left_value </br>

AST: abstract syntax tree - built during parsing </br>
abstract syntax tree for an arithmetic expression: </br>
inner nodes: operators </br>
leafs: operands of expressions (numbers, identifiers, vector elements, function calls etc) </br>

