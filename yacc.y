%{
#include <stdio.h>
#include "control.h"
#include "error_messages.h"
#include "ast.h"
extern FILE* yyin;

extern char* yytext;
extern int yylineno;

extern int yylex (void);

int yyerror(char * s){
printf("eroare: %s la linia:%d\n",s,yylineno);
return 1;
}
%}

%union {
float       floatval;
int         intval;
char*       strval;
struct AST * ast_node;
}

%token BGIN END BEGIN_FUNCTION END_FUNCTION BEGIN_CLASS END_CLASS INT_TYPE BOOL_TYPE FLOAT_TYPE CHAR_TYPE STRING_TYPE CLASS_TYPE ARRAY_TYPE 
%token LR GR GE LE EQ NE WHILE FOR IF PRINT IS_CONST DEF AND OR NOT BEGIN_STATEMENT END_STATEMENT
%token <strval> BOOL_VALUE STRING_VALUE INT_VALUE FLOAT_VALUE  CHAR_VALUE ID
%type<strval> tip declaratii_variabile asignare apelare class_type value list_parametri parametru declaratie_variabila non_int_value
%token <intval>NR
%type <ast_node>e
%type <ast_node>expr
%left '+' '-' '*' '/'
%start start
%%
start: global_vars functions_data_types main {printf("Successfully executed!\n");}
     ;

expr: e { /* printf("a compilat: ");  printf("evaluarea expresiei este:%d ",evalAST($1));*/ }
          ;

e:  e '+' e    { 
                $$ = buildAST('+',$1,$3,"PLUS");
               }
e: e '-' e     {
                $$ = buildAST('-',$1,$3,"MINUS");
               }
e: e '/' e     {
                $$ = buildAST('/',$1,$3,"DIVIDE");
               }
e: e '*' e     {
                $$ = buildAST('*',$1,$3,"MULTIPLY");
               }
e: '(' expr ')' { $$ = buildAST(evalAST($2),0,0,"NUMBER"); } 
e: NR          {$$ = buildAST($1,0,0,"NUMBER"); }

e: ID          {
                    Variable var;
                    var.name = std::string($1);
                    var.variable_type = "int";
                    if(FindVariable(var))
                    {
                         //am gasit variabila cu numele specificat si tipul int
                         Variable v = VariableToBeReturnedTable(var);
                         int number = atoi(v.value.c_str());
                         $$ = buildAST(number,0,0,"NUMBER");
                    }
                    else
                    {
                         // printf("Nu s-a gasit o astfel de variabila de tipul int!\n");
                    }
               }
               ;

global_vars: declaratii_variabile
            |declaratii_constante

functions_data_types: declaratie_functie';'
                    | declaratie_clasa';'
                    | declaratie_functie';' functions_data_types
                    | declaratie_clasa';' functions_data_types
                    ;

main: BGIN {SetIsInMain(1);} cod END {SetIsInMain(0);};

cod: declaratii_variabile
    | statement 
    | declaratii_variabile cod
    | statement cod

tip: INT_TYPE                                     {$$="int";}
   | BOOL_TYPE                                    {$$="bool";}
   | FLOAT_TYPE                                   {$$="float";}
   | CHAR_TYPE                                    {$$="char";}
   | STRING_TYPE                                  {$$="string";}
   | ARRAY_TYPE LR tip GR '[' NR ']'              {$$="array";}
   | class_type                                   {$$=$1;}
   ;

class_type: ID
          ;

declaratie_clasa: CLASS_TYPE ID BEGIN_CLASS {
                    SetIsInClass(1);
                    SetCurrentClassName($2);
                    DefinedClass c;
                    c.name = std::string($2);
                    if(!existaClasa(c))
                   {
                     if(AddClass(c))
                     {
                          //printf("class %s added\n", c.name.c_str());
                     }
                   } 
                   } cod_clasa END_CLASS  
                    {   
                    SetIsInClass(0);
                    SetCurrentClassName(nullptr);
                    }
                    ;

cod_clasa: declaratii_variabile
        | declaratii_functii
        | declaratii_variabile cod_clasa
        | declaratii_functii cod_clasa
        ;

declaratii_variabile: declaratie_variabila';'
                    | declaratie_variabila',' declaratii_variabile
                    {  
                         char aux[]=",";
                         char aux2[]=":";
                         strcat($$,aux);
                         strcat($$,$3);
  
                    }
                    | EMPTY{
                        strcpy($$, "none");
                    }
                    ;

declaratie_variabila: tip':'ID
                    {
                         Variable v;
                         v.name = string($3);
                         v.variable_type = string($1);
                         v.scope = "global";
                         v.value = "none";
                         v.is_constant = 0;
                         if(v.variable_type != "bool" && v.variable_type != "int" && v.variable_type != "char" && v.variable_type != "string" && v.variable_type != "array" && v.variable_type != "float")
                         {
                              DefinedClass c;
                              c.name = string($1);
                              if(!existaClasa(c))
                              {    printf("TIP %s \n", c.name.c_str());
                                   M_ERROR_INEXISTENT_TYPE;
                                   exit(0);                              
                              }
                         }
                         DefinedClass c;
                         c.name = string($1);
                         if(existaClasa(c))
                         {
                            string data_members = GetClassDataMembers($1);
                            string types = GetDataMembersTypes($1);
                            for(unsigned i = 0; i< data_members.size(); i++)
                            {
                                 string data_member = "", dm_type = "";
                                 while(data_members[i] != ',' && i<data_members.size())
                                 {
                                      data_member += data_members[i];
                                      i++;
                                 }
                                 unsigned j = 0;
                                 while(types[j] != ',' && j < types.size())
                                 {
                                      dm_type += types[j];
                                      j++;
                                 }
                                 v.name = string($3);
                                 v.name += '.';
                                 v.name += data_member;
                                 v.variable_type = dm_type;
                                 SetVarScope(v);
                                 AddVariable(v);
                            }
                         }
                         else
                         {
                              if(SetVarScope(v))
                              {
                                   AddVariable(v);
                              }

                         }
                    
                         char aux[1024];
                         sprintf(aux,"%s:%s",$$,$3);
                         $$=strdup(aux);

                    }
                    ;

declaratii_constante: declaratie_constanta';'
                    | declaratii_constante declaratie_constanta
                    ;

declaratie_constanta: IS_CONST':'tip':'asignare';'
                    {
                    }
                    ;

declaratii_functii: declaratie_functie';'
                  | declaratie_functie';' declaratii_functii

declaratie_functie: DEF tip ':' ID {SetIsInFunction(1); SetCurrentFunctionName($4);} '(' declaratii_variabile ')' BEGIN_FUNCTION  cod_functie END_FUNCTION
                  { 
                       Function f;
                       f.name = std::string($4);
                       f.return_type = std::string($2);
                       string params = std::string($7);
                       addParams(f, params);
                       if(GetIsInClass()){
                              string class_name = GetCurrentClassName();
                              string temp = class_name;
                              temp += "::";
                              temp += f.name;
                              f.name=temp;
                              f.class_name = class_name;
                              if(!existaFunctie(f))
                              {
                                   addFunction(f);
                              }
                              else
                              {
                                   M_ERROR_EXISTS_FUNC;
                              }
                         }
                          else if(!existaFunctie(f)){
                               f.is_class_method = 0;
                               f.class_name = "none";

                              addFunction(f);
                         }
                         else
                         {
                             M_ERROR_EXISTS_FUNC;
                         }
                       SetIsInFunction(0); 
                       SetCurrentFunctionName(nullptr);
                  }
                  | DEF tip ':' ID {SetIsInFunction(1); SetCurrentFunctionName($4);} '('')' BEGIN_FUNCTION  cod_functie END_FUNCTION                          
                  { 
                       SetIsInFunction(0); 
                       SetCurrentFunctionName(nullptr);
                  }

cod_functie: declaratie_variabila';'                    
           | statement                                       
           | cod_functie declaratie_variabila        
           | cod_functie statement       
           | EMPTY               
           ;

asignare: ID '=' NR                       
          {
               Variable v;
               v.name = std::string($1);
               if(checkVarByName(v) == 1)
               {
                    v.value = to_string($3);
                    changeVarValue(v);
               }
               else
               {
                    M_ERROR_NOT_EXISTS_VAR
                    exit(0);
               }
          }
        | ID '=' non_int_value{
               Variable v;
               v.name = std::string($1);
               
               Variable temp;
               temp.name = string($3);
               if(checkVarByName(temp))
               {
                  v.value = GetVariableValue(temp);
                  changeVarValue(v);
               }
               else if(checkVarByName(v) == 1)
               {
                    v.value = string($3);
                    changeVarValue(v);
               }
               else
               {
                    M_ERROR_NOT_EXISTS_VAR
                    exit(0);
               }
        }
        | ID '=' ID                          
          {
             Variable v1;
             Variable v2;
             v1.name = std::string($1);
             v2.name = std::string($3);
             if(checkVarByName(v1) && checkVarByName(v2))
             {
                  v1.value = GetVariableValue(v2);
                  changeVarValue(v1);
             }       
             else{
               M_ERROR_NOT_EXISTS_VAR;
               exit(0);
             }
          }
        | ID '=' apelare                     
          {
             Variable var;
             std::string str = "";
             str += std::string($3);
             var.name = std::string($1);

             Function f;
             f.name = "";
             int b = 0;

             for(int i = 0; i < str.size(); i++)
             {
                  if(str[i] == '(') 
                  {
                       b = 1;
                       break;
                  }
                  f.name += str[i];
             }


               if(RecognizeFunction(f))
               {
                    Function found = ReturnedFunction(f);
                    string function_return_type = found.return_type;

                    string variable_type = ReturnTypeVariable(var);
                    if(variable_type == "none")
                    {
                         printf("Variabila nu exista\n");
                    }
                    if(variable_type == found.return_type)
                    {
                         printf("Asignare reusita!\n");
                    }
                    else
                    {
                         printf("Error: Tipul variabilelor nu coincide!\n");
                         exit(0);
                    }
               }
               else
               {
                    printf("Error: Function does not exist.\n");
                    exit(0);
               }          
          }
         /*  | ID '=' expr {
             Variable v;
               v.name = std::string($1);
               if(checkVarByName(v) == 1)
               {
                    v.value = to_string(evalAST($3));
                    changeVarValue(v);
               }
               else
               {
                    M_ERROR_NOT_EXISTS_VAR
                    exit(0);
               }
        }*/
        ;

statement: FOR '('for_params')' BEGIN_STATEMENT cod_functie END_STATEMENT
         | WHILE '('conditions')' BEGIN_STATEMENT cod_functie END_STATEMENT
         | IF '('conditions')' BEGIN_STATEMENT cod_functie END_STATEMENT
         | asignare';' 
         | apelare';'
         | print';'
         ;

print: PRINT '(' STRING_VALUE ',' expr ')' {
     if(GetIsInMain()){
          string msg = string($3);
          msg = msg.substr(1, msg.size() - 2);
          printf("\n%s%d\n", msg.c_str(), evalAST($5));
     }
}
        ;

for_params:asignare ';' condition';'asignare {}
          ;


conditions: condition
          | condition logical_operator conditions
          ;

condition: BOOL_VALUE
         | ID
         | apelare
         ;

logical_operator: AND
                | OR
                | NOT
                | NE
                | LE
                | GE
                | LR
                | GR
                | EQ
                ;

non_int_value: STRING_VALUE 
     | CHAR_VALUE   
     | BOOL_VALUE   
     ;
value: NR    
     | STRING_VALUE 
     | CHAR_VALUE   
     | BOOL_VALUE   
     ;

apelare: ID '(' ')'         
          {
               strcat($$,"()");
               Function f;
               f.name = std::string($1);
               f.return_type = "";

               if(RecognizeFunction(f))
               {
                    Function found = ReturnedFunction(f);
                    if(found.parameters.size() == 0)
                    {
                    }
                    else
                    {
                         printf("Error: Numar incorect de parametrii\n");
                         exit(0);
                    }
               }
               else
               {
                    M_ERROR_NOT_EXISTS_FUNC
                    exit(0);
               }

          }
       | ID '('list_parametri')'   
          {
               char* aux=strdup($1);
               $1=aux;
               strcat($$,"(");
               strcat($$,$3);
               strcat($$,")");
               Function f;
          
               f.name = std::string($1);

               if(RecognizeFunction(f))
               {
                    
                    Function found = ReturnedFunction(f);
                    if(found.parameters.size() != 0)
                    {
                         if(FindParameters(found, $3))
                         {
                              printf("Functie apelata corect.\n");
                         }
                    }
                    else
                    {
                         printf("Error: Numar incorect de parametrii\n");
                         exit(0);
                    }
               }
               else
               {
                    M_ERROR_NOT_EXISTS_FUNC
                    exit(0);
               }
               
          }
       ;

list_parametri: parametru          {$$=strdup($1);}
              | parametru',' list_parametri {char aux[1024]; sprintf(aux,"%s,%s",$$,$3);$$=strdup(aux);}
              ;

parametru: value                    {$$=strdup($1);}
         | apelare                  {$$=strdup($1);}
         | ID                       {$$=strdup($1);}
         | expr                     {}
         ;
EMPTY:
     ; 
%%
#include "tables_handler.h"
#include "control.h"

int main(int argc, char** argv)
{
TablesHandler table;
Initialize(table);
yyin=fopen(argv[1],"r");
yyparse();
PrintSymbolTables();
}
