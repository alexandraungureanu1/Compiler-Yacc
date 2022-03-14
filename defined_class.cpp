#include "defined_class.h"

DefinedClass::DefinedClass(string name)
{
    this->name = name;
}

void DefinedClass::AddDataMember(Variable &var)
{
    this->data_members.push_back(var);
}

void DefinedClass::AddMethod(Function &fun)
{
    this->methods.push_back(fun);
}