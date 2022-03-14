#ifndef CONTROL_H
#define CONTROL_H

#include "tables_handler.h"
#include <stdio.h>
#include <string.h>

void Initialize(TablesHandler &_table);
bool AddVariable(Variable &var);
bool AddClass(DefinedClass &def_class);
bool AddDataMember(Variable &var, string class_name);
bool existaDataMember(Variable &var, string class_name);
void SetIsInFunction(bool val);
void SetIsInClass(bool val);
void SetIsInMain(bool val);
bool GetIsInMain();
bool GetIsInFunction();
bool GetIsInClass();
void SetCurrentFunctionName(char *fName);
void SetCurrentClassName(char *name);
char *GetCurrentClassName();
char *GetCurrentFunctionName();
bool existaClasa(DefinedClass &def_class);
bool existaVariabila(Variable &var);
void PrintSymbolTables();
bool existaFunctie(Function &f);
void addFunction(Function &f);
void addParams(Function &f, string params);
void changeVarValue(Variable &v);
bool checkVarByName(Variable &v);
bool SetVarScope(Variable &var);
string GetClassDataMembers(string class_name);
string GetDataMembersTypes(string class_name);
string GetVariableValue(Variable &v);
bool RecognizeFunction(Function &f);
Function ReturnedFunction(Function &f);
string ReturnTypeVariable(Variable &var);
Variable ReturnVariable(Variable &var);
bool FindVariable(Variable &var);
Variable VariableToBeReturnedTable(Variable &var);
bool FindParameters(Function &f, string parameters);
#endif
