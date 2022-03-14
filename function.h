#ifndef FUNCTION_H
#define FUNCTION_H

#include "variable.h"

class Function
{
public:
    string return_type;
    string name;
    vector<Variable> parameters;
    // vector<Variable> local_variables;
    int is_class_method;
    string class_name;
    Function() = default;
    Function(string return_type, string name);
    Function(string return_type, string name, string class_name);
    void AddParameter(Variable &param);
    // void AddLocalVar(Variable &avar);
    ~Function() = default;
};
#endif
// TODO: local variables for functions