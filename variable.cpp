#include "variable.h"

Variable::Variable(string variable_type, string name, string scope, bool is_constant)
{
    this->variable_type = variable_type;
    this->name = name;
    this->scope = scope;
    this->is_constant = is_constant;
}