#include "function.h"

Function::Function(string return_type, string name)
{
    this->return_type = return_type;
    this->name = name;
    this->is_class_method = false;
}

Function::Function(string return_type, string name, string class_name)
{
    this->return_type = return_type;
    this->name = name;
    this->class_name = name;
    this->is_class_method = true;
}

void Function::AddParameter(Variable &param)
{
    this->parameters.push_back(param);
}

/*void Function::AddLocalVar(Variable &var)
{
    this->parameters.push_back(var);
}*/