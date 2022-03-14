#include "control.h"
#include "error_messages.h"
TablesHandler table;
bool isInFunction;
bool isInClass;
bool isInMain;
char *currentFunctionName;
char *currentClassName;

void Initialize(TablesHandler &_table)
{
    table = _table;
}

bool AddVariable(Variable &v)
{
    if (!existaVariabila(v))
    {
        return table.AddGlobalVariable(v);
    }
    else
    {
        M_ERROR_EXISTS_VAR;
        exit(0);
    }
}

bool FindParameters(Function &f, string parameters)
{
    Variable p;
    p.name = "";
    parameters += ',';
    int index = 0;

    for (int i = 0; i < parameters.size(); i++)
    {
        if (parameters[i] == ',')
        {
            p.variable_type = f.parameters[index].variable_type;

            if (table.FindVariable(p))
            {
                index++;
            }
            else
            {
                return false;
            }

            p.name = "";
        }
        else
        {
            p.name += parameters[i];
        }
    }

    return true;
}

bool AddDataMember(Variable &var, string class_name)
{
    for (unsigned i = 0; i < table.symbol_table_classes.size(); i++)
    {
        if (table.symbol_table_classes[i].name == class_name)
        {
            table.symbol_table_classes[i].data_members.push_back(var);
            return true;
        }
    }
    return false;
}

bool existaDataMember(Variable &var, string class_name)
{
    for (unsigned i = 0; i < table.symbol_table_classes.size(); i++)
    {
        if (table.symbol_table_classes[i].name == class_name)
        {
            for (unsigned j = 0; j < table.symbol_table_classes[i].data_members.size(); j++)
            {
                if (table.symbol_table_classes[i].data_members[j].name == var.name)
                    return true;
            }
        }
    }
    return false;
}
void SetIsInFunction(bool val)
{
    isInFunction = val;
}

void SetIsInClass(bool val)
{
    isInClass = val;
}

void SetIsInMain(bool val)
{
    isInMain = val;
}

bool GetIsInMain()
{
    return isInMain;
}

bool GetIsInFunction()
{
    return isInFunction;
}

bool GetIsInClass()
{
    return isInClass;
}

void SetCurrentFunctionName(char *fName)
{
    if (fName == nullptr)
        currentFunctionName = nullptr;
    else
        currentFunctionName = strdup(fName);
}

void SetCurrentClassName(char *name)
{
    if (name == nullptr)
        currentClassName = 0;
    else
        currentClassName = strdup(name);
}

char *GetCurrentClassName()
{
    return currentClassName;
}

char *GetCurrentFunctionName()
{
    return currentFunctionName;
}

bool AddClass(DefinedClass &def_class)
{
    return table.AddClass(def_class);
}

bool existaClasa(DefinedClass &def_class)
{
    return table.CheckDefinedClass(def_class);
}

bool existaVariabila(Variable &var)
{
    return table.CheckDefinedVariable(var);
}

bool checkVarByName(Variable &v)
{
    for (unsigned i = 0; i < table.symbol_table_variables.size(); i++)
    {
        if (table.symbol_table_variables[i].name == v.name)
        {
            return true;
        }
    }
    return false;
}
string GetVariableValue(Variable &v)
{
    for (unsigned i = 0; i < table.symbol_table_variables.size(); i++)
    {
        if (v.name == table.symbol_table_variables[i].name)
        {
            return v.value;
        }
    }
}
bool existaFunctie(Function &f)
{
    return table.CheckDefinedFunction(f);
}

void addFunction(Function &f)
{
    table.AddFunction(f);
}

void PrintSymbolTables()
{
    table.PrintVariableSymbolTable();
    table.PrintMethodsSymbolTable();
}

void addParams(Function &f, string params)
{
    if (params == "none")
    {
        return;
    }
    for (int i = 0; i < params.size(); i++)
    {
        Variable var;

        string tip;

        while (params[i] != ':')
        {
            tip += params[i];
            i++;
        }

        string nume;
        i++;

        var.variable_type = tip;

        while (params[i] != ',' && i < params.size())
        {
            nume += params[i];
            i++;
        }
        var.name = nume;
        var.scope = "function ";
        var.scope += f.name;
        var.value = "none";

        f.parameters.push_back(var);
    }
}
string GetClassDataMembers(string class_name)
{
    string result = "";
    for (unsigned i = 0; i < table.symbol_table_classes.size(); i++)
    {
        if (table.symbol_table_classes[i].name == class_name)
        {
            for (unsigned j = 0; j < table.symbol_table_classes[i].data_members.size(); j++)
            {
                result += table.symbol_table_classes[i].data_members[j].name;
                result += ",";
            }
            return result;
        }
    }
}

string GetDataMembersTypes(string class_name)
{
    string result = "";
    for (unsigned i = 0; i < table.symbol_table_classes.size(); i++)
    {
        if (table.symbol_table_classes[i].name == class_name)
        {
            for (unsigned j = 0; j < table.symbol_table_classes[i].data_members.size(); j++)
            {
                result += table.symbol_table_classes[i].data_members[j].variable_type;
                result += ",";
            }
            return result;
        }
    }
}

bool SetVarScope(Variable &v)
{
    if (GetIsInMain())
    {
        v.scope = "main";
        return 1;
    }
    else if (GetIsInFunction() && GetIsInClass())
    {
        v.scope = "function ";
        v.scope += GetCurrentClassName();
        v.scope += "::";
        v.scope += GetCurrentFunctionName();
        return 1;
    }
    else if (GetIsInFunction())
    {
        v.scope = "function ";
        string fct_name = GetCurrentFunctionName();
        v.scope += fct_name;
        return 1;
    }
    else if (GetIsInClass())
    {
        string class_name = GetCurrentClassName();
        v.scope = "class ";
        v.scope += class_name;
        v.scope += "data member";
        if (!existaDataMember(v, class_name))
        {
            AddDataMember(v, class_name);
        }
        else
        {
            M_ERROR_EXISTS_DATA_MEMBER;
        }
        return 0;
    }
    return 1;
}

void changeVarValue(Variable &v)
{
    for (unsigned i = 0; i < table.symbol_table_variables.size(); i++)
    {
        if (v.name == table.symbol_table_variables[i].name)
        {
            table.symbol_table_variables[i].value = v.value;
        }
    }
}

bool RecognizeFunction(Function &f)
{
    return table.FindFunction(f);
}

Function ReturnedFunction(Function &f)
{
    return table.ReturnFunction(f);
}

string ReturnTypeVariable(Variable &var)
{
    return table.FindVariableAfterName(var);
}

Variable ReturnVariable(Variable &var)
{
    return table.ReturnedVariable(var);
}

bool FindVariable(Variable &var)
{
    return table.FindVariable(var);
}

Variable VariableToBeReturnedTable(Variable &var)
{
    return table.VariableToBeReturned(var);
}