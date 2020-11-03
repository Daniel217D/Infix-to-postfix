#include "Converter.h"
#include "Stack.h"

using std::string;

string Converter::convert(string str_in) {
    Stack<char> stack;
    bool wasNum = false;
    string result;

    stack.push('(');
    for (char symbol : str_in) {
        if ((symbol >= 'a' && symbol <= 'z') || (symbol >= 'A' && symbol <= 'Z') || (symbol >= '0' && symbol <= '9') || symbol == '.') {
            result.push_back(symbol);
            wasNum = true;
        } else if (symbol == '(') {
            stack.push('(');
        } else if (symbol == ')') {
            symbol = stack.pop();

            if(symbol != '(' && wasNum) {
                result.push_back(',');
                wasNum = false;
            }

            while (symbol != '(') {
                result.push_back(symbol);
                symbol = stack.pop();
            }
        } else if (is_operation(symbol)) {
            char temp = stack.pop();

            if(wasNum) {
                result.push_back(',');
                wasNum = false;
            }

            while (temp != '(' && priority(temp) >= priority(symbol)) {
                result.push_back(temp);
                temp = stack.pop();
            }

            stack.push(temp);
            stack.push(symbol);
        }
    }

    char symbol = stack.pop();

    while (symbol != '(') {
        result.push_back(symbol);
        symbol = stack.pop();
    }

    return result;
}

unsigned short int Converter::priority(char sign) {
    unsigned short int result = 0;

    switch (sign) {
        case '^': {
            result = 3;
            break;
        }
        case '*':
        case ':':
        case '/': {
            result = 2;
            break;
        }
        case '+':
        case '-': {
            result = 1;
            break;
        }
    }

    return result;
}

bool Converter::is_operation(char sign) {
    bool result = false;

    switch (sign) {
        case '^':
        case '*':
        case ':':
        case '/':
        case '+':
        case '-': {
            result = true;
            break;
        }
    }

    return result;
}