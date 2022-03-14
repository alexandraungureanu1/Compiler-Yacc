#ifndef TABLES_HANDLER_H
#define TABLES_HANDLER_H

#include "defined_class.h"

class TablesHandler
{
public:
    vector<Variable> symbol_table_variables;
    vector<Function> symbol_table_functions;
    vector<DefinedClass> symbol_table_classes;

    bool AddGlobalVariable(Variable &var);
    void AddLocalVariable(Variable &var);
    void AddDataMemberVariable(Variable &var);
    bool AddFunction(Function &fun);
    bool AddClass(DefinedClass &def_class);

    bool CheckDefinedVariable(Variable &var);
    bool CheckDefinedFunction(Function &fun);
    bool CheckDefinedClass(DefinedClass &def_class);

    void PrintVariableSymbolTable();
    void PrintMethodsSymbolTable();

    void GetType(unsigned val, string &str_type);

    Function ReturnFunction(Function &fun);
    string FindVariableAfterName(Variable &var);
    Variable ReturnedVariable(Variable &var);
    Variable VariableToBeReturned(Variable &var);
    bool FindFunction(Function &f);
    bool FindVariable(Variable &var);
};
#endif