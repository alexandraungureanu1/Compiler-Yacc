#ifndef DEF_CLASS_H
#define DEF_CLASS_H

#include "function.h"

class DefinedClass
{
public:
    string name;
    vector<Variable> data_members;
    vector<Function> methods;
    DefinedClass() = default;
    DefinedClass(string name);
    void AddDataMember(Variable &var);
    void AddMethod(Function &fun);
    ~DefinedClass() = default;
};
#endif