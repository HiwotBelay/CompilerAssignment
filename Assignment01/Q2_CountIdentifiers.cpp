#include <iostream>
#include <string>
#include <cctype>
using namespace std;

string keywords[] = {
    "int", "char", "float", "double", "void", "if", "else", "for",
    "while", "do", "return", "main", "cout", "cin", "string", "bool"};

bool isKeyword(string word)
{
    for (int i = 0; i < 16; i++)
    {
        if (keywords[i] == word)
        {
            return true;
        }
    }
    return false;
}

bool isValidIdentifier(string word)
{
    if (word.empty())
        return false;

    if (!isalpha(word[0]) && word[0] != '_')
    {
        return false;
    }

    for (int i = 1; i < word.length(); i++)
    {
        if (!isalnum(word[i]) && word[i] != '_')
        {
            return false;
        }
    }

    if (isKeyword(word))
    {
        return false;
    }

    return true;
}

int countIdentifiers(string code)
{
    int count = 0;
    string word = "";
    bool inString = false;
    bool inComment = false;

    for (int i = 0; i < code.length(); i++)
    {
        char c = code[i];

        if (c == '"')
        {
            inString = !inString;
            if (!inString && !word.empty() && isValidIdentifier(word))
            {
                count++;
            }
            word = "";
            continue;
        }

        if (inString)
        {
            continue;
        }

        if (i < code.length() - 1 && code[i] == '/' && code[i + 1] == '/')
        {
            if (!word.empty() && isValidIdentifier(word))
            {
                count++;
            }
            word = "";
            inComment = true;
            i++;
            continue;
        }

        if (c == '\n' && inComment)
        {
            inComment = false;
            continue;
        }

        if (inComment)
        {
            continue;
        }

        if (isalnum(c) || c == '_')
        {
            word += c;
        }
        else
        {
            if (!word.empty() && isValidIdentifier(word))
            {
                count++;
            }
            word = "";
        }
    }

    if (!word.empty() && isValidIdentifier(word))
    {
        count++;
    }

    return count;
}

int main()
{
    string code = "";
    string line;

    cout << "Enter code (type END to finish):" << endl;

    while (getline(cin, line))
    {
        if (line == "END")
        {
            break;
        }
        code += line + "\n";
    }

    int result = countIdentifiers(code);
    cout << "Total identifiers: " << result << endl;

    return 0;
}
