#include <iostream>
#include <string>
#include <map>
using namespace std;

enum Type
{
    INT,
    FLOAT,
    CHAR,
    BOOL,
    ERROR
};

string typeName(Type t)
{
    string names[] = {"int", "float", "char", "bool", "error"};
    return names[t];
}

class ConversionMatrix
{
    map<pair<Type, Type>, bool> safe;

public:
    ConversionMatrix()
    {
        safe[{INT, FLOAT}] = true;
        safe[{CHAR, INT}] = true;
        safe[{CHAR, FLOAT}] = true;
    }

    bool isSafe(Type from, Type to)
    {
        if (from == to)
            return true;
        return safe.count({from, to}) > 0;
    }

    bool isUnsafe(Type from, Type to)
    {
        if (from == FLOAT && to == INT)
            return true;
        return false;
    }

    Type commonType(Type t1, Type t2)
    {
        if (t1 == t2)
            return t1;
        if (isSafe(t1, t2))
            return t2;
        if (isSafe(t2, t1))
            return t1;
        if (t1 == INT && t2 == FLOAT)
            return FLOAT;
        if (t1 == FLOAT && t2 == INT)
            return FLOAT;
        return ERROR;
    }
};

class TypeChecker
{
    ConversionMatrix matrix;
    map<string, Type> vars;

public:
    void declare(string name, Type type)
    {
        vars[name] = type;
        cout << name << ": " << typeName(type) << endl;
    }

    Type checkAssign(string var, Type exprType)
    {
        if (vars.count(var) == 0)
        {
            cout << "Error: " << var << " not declared" << endl;
            return ERROR;
        }

        Type varType = vars[var];

        if (varType == exprType)
        {
            cout << "OK: " << var << " = " << typeName(exprType) << endl;
            return varType;
        }

        if (matrix.isSafe(exprType, varType))
        {
            cout << "OK: " << var << " = " << typeName(exprType)
                 << " -> " << typeName(varType) << " (converted)" << endl;
            return varType;
        }

        if (matrix.isUnsafe(exprType, varType))
        {
            cout << "Error: Unsafe conversion " << typeName(exprType)
                 << " -> " << typeName(varType) << " (data loss)" << endl;
            return ERROR;
        }

        cout << "Error: Cannot convert " << typeName(exprType)
             << " to " << typeName(varType) << endl;
        return ERROR;
    }

    Type checkExpr(Type left, string op, Type right)
    {
        Type result = matrix.commonType(left, right);

        if (result == ERROR)
        {
            cout << "Error: Incompatible types" << endl;
            return ERROR;
        }

        if (op == "+" || op == "-" || op == "*" || op == "/")
        {
            cout << "OK: " << typeName(left) << " " << op << " " << typeName(right)
                 << " -> " << typeName(result);
            if (left != result)
                cout << " (converted " << typeName(left) << ")";
            if (right != result)
                cout << " (converted " << typeName(right) << ")";
            cout << endl;
            return result;
        }

        if (op == "==" || op == "<" || op == ">")
        {
            cout << "OK: " << typeName(left) << " " << op << " "
                 << typeName(right) << " -> bool" << endl;
            return BOOL;
        }

        return ERROR;
    }
};

int main()
{
    TypeChecker tc;

    cout << "=== Type Checker ===" << endl;

    cout << "\n1. Declarations:" << endl;
    tc.declare("x", INT);
    tc.declare("y", FLOAT);

    cout << "\n2. Safe conversions:" << endl;
    tc.checkAssign("y", INT);

    cout << "\n3. Unsafe conversions:" << endl;
    tc.checkAssign("x", FLOAT);

    cout << "\n4. Expressions:" << endl;
    tc.checkExpr(INT, "+", FLOAT);
    tc.checkExpr(CHAR, "*", INT);
    tc.checkExpr(INT, "<", FLOAT);

    return 0;
}
