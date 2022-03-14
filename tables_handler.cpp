#include "tables_handler.h"
#include <stdio.h>

bool TablesHandler::AddGlobalVariable(Variable &var)
{
    if (!CheckDefinedVariable(var))
    {
        this->symbol_table_variables.push_back(var);
        return true;
    }
    return false;
}

bool TablesHandler::AddFunction(Function &fun)
{
    if (!CheckDefinedFunction(fun))
    {
        this->symbol_table_functions.push_back(fun);
        return true;
    }
    return false;
}

bool TablesHandler::AddClass(DefinedClass &def_class)
{
    if (!CheckDefinedClass(def_class))
    {
        this->symbol_table_classes.push_back(def_class);
        return true;
    }
    return false;
}

bool TablesHandler::CheckDefinedVariable(Variable &var)
{
    for (unsigned i = 0; i < symbol_table_variables.size(); i++)
    {
        if (symbol_table_variables[i].name == var.name && symbol_table_variables[i].scope == var.scope)
        {
            return 1;
        }
    }

    return 0;
}

bool TablesHandler::CheckDefinedFunction(Function &fun)
{
    bool ok = 1;

    for (unsigned i = 0; i < symbol_table_functions.size(); i++)
    {
        if ((symbol_table_functions[i].name == fun.name) &&
            symbol_table_functions[i].parameters.size() == fun.parameters.size())
        {
            for (unsigned idx = 0; idx < symbol_table_functions[i].parameters.size(); idx++)
            {
                if (symbol_table_functions[i].parameters[idx].variable_type != fun.parameters[idx].variable_type)
                {
                    ok = 0;
                }
            }
            return ok;
        }
    }
    ok = 1;
    if (fun.is_class_method == true)
    {
        for (unsigned i = 0; i < symbol_table_classes.size(); i++)
        {
            if (symbol_table_classes[i].name == fun.class_name)
            {
                for (unsigned idx = 0; idx < symbol_table_classes[i].methods.size(); idx++)
                {
                    if ((symbol_table_classes[i].methods[idx].name == fun.name) &&
                        symbol_table_classes[i].methods[idx].parameters.size() == fun.parameters.size())
                    {
                        for (unsigned j = 0; j < symbol_table_classes[i].methods[idx].parameters.size(); j++)
                        {
                            if (symbol_table_classes[i].methods[idx].parameters[j].variable_type != fun.parameters[j].variable_type)
                            {
                                ok = 0;
                            }
                        }
                    }
                }
                return ok;
            }
        }
    }

    return 0;
}

bool TablesHandler::CheckDefinedClass(DefinedClass &def_class)
{
    for (unsigned i = 0; i < symbol_table_classes.size(); i++)
    {
        if (symbol_table_classes[i].name == def_class.name)
        {
            return 1;
        }
    }
    return 0;
}

string TablesHandler::FindVariableAfterName(Variable &var)
{

    string return_type;

    for (unsigned i = 0; i < symbol_table_variables.size(); i++)
    {
        if (symbol_table_variables[i].name == var.name)
        {
            return_type = symbol_table_variables[i].variable_type;
            return return_type;
        }
    }

    return_type = "none";
    return return_type;
}

Variable TablesHandler::ReturnedVariable(Variable &var)
{
    for (unsigned i = 0; i < symbol_table_variables.size(); i++)
    {
        if (symbol_table_variables[i].name == var.name)
        {
            return symbol_table_variables[i];
        }
    }
}

Variable TablesHandler::VariableToBeReturned(Variable &var)
{
    // se stie ca exista o astfel de variabila
    for (unsigned i = 0; i < symbol_table_variables.size(); i++)
    {
        if (symbol_table_variables[i].name == var.name && symbol_table_variables[i].variable_type == var.variable_type)
        {
            return symbol_table_variables[i];
        }
    }
}

bool TablesHandler::FindFunction(Function &fun)
{
    for (unsigned i = 0; i < symbol_table_functions.size(); i++)
    {
        if ((symbol_table_functions[i].name == fun.name))
            return true;
    }
    return false;
}

bool TablesHandler::FindVariable(Variable &var)
{

    for (unsigned i = 0; i < symbol_table_variables.size(); i++)
    {
        if (symbol_table_variables[i].name == var.name && symbol_table_variables[i].variable_type == var.variable_type)
        {
            return true;
        }
    }

    return false;
}

Function TablesHandler::ReturnFunction(Function &fun)
{
    for (unsigned i = 0; i < symbol_table_functions.size(); i++)
    {
        if ((symbol_table_functions[i].name == fun.name))
            return symbol_table_functions[i];
    }
}

void TablesHandler::PrintVariableSymbolTable()
{
    FILE *f;
    f = fopen("symbol_table.txt", "w+");

    fprintf(f, "Variables Symbol Table is: \n");
    for (unsigned i = 0; i < symbol_table_variables.size(); i++)
    {
        fprintf(f, "%s, %s, %s, %s \n", symbol_table_variables[i].variable_type.c_str(), symbol_table_variables[i].name.c_str(),
                symbol_table_variables[i].value.c_str(), symbol_table_variables[i].scope.c_str());
    }
}

void TablesHandler::PrintMethodsSymbolTable()
{
    FILE *f;
    f = fopen("symbol_table_functions.txt", "w+");

    fprintf(f, "Functions Symbol Table is: \n");
    for (unsigned i = 0; i < symbol_table_functions.size(); i++)
    {
        string function_signature = "";
        function_signature += symbol_table_functions[i].return_type;
        function_signature += " ";
        function_signature += symbol_table_functions[i].name;
        function_signature += "(";
        for (unsigned j = 0; j < symbol_table_functions[i].parameters.size(); j++)
        {
            function_signature += symbol_table_functions[i].parameters[j].variable_type;
            function_signature += " ";
        }
        function_signature += ")";
        fprintf(f, "%s\n", function_signature.c_str());
    }
}
