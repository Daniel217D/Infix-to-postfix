#include "Converter.h"
#include "Stack.h"
#include <fstream>

using std::ifstream;
using std::ofstream;
using std::string;

bool Converter::convert(string file_in, string file_out) {
    ifstream fin(file_in);
    ofstream fout(file_out);

    if (!fin.is_open() || !fout.is_open()) {
        return false;
    }

    Stack<char> stack;
    char symbol;

    stack.push('(');
    while (fin >> symbol) {
        if ((symbol >= 'a' && symbol <= 'z') || (symbol >= 'A' && symbol <= 'Z') || (symbol >= '0' && symbol <= '9')) {
            fout << symbol;
        } else if (symbol == '(') {
            stack.push('(');
        } else if (symbol == ')') {
            symbol = stack.pop();

            while (symbol != '(') {
                fout << symbol;
                symbol = stack.pop();
            }
        } else if (is_operation(symbol)) {
            char temp = stack.pop();

            while (temp != '(' && priority(temp) >= priority(symbol)) {
                fout << temp;
                temp = stack.pop();
            }

            stack.push(temp);
            stack.push(symbol);
        }
    }

    symbol = stack.pop();

    while (symbol != '(') {
        fout << symbol;
        symbol = stack.pop();
    }

    fin.close();
    fout.close();
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