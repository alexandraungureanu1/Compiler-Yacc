#ifndef VARIABLE_H
#define VARIABLE_H

#include <iostream>
#include <vector>
using namespace std;

class Variable
{
public:
    string variable_type;
    string name;
    string value;
    string scope;
    bool is_constant;
    Variable() = default;
    Variable(string variable_type, string name, string scope, bool is_constant);
    ~Variable() = default;
};

#endif