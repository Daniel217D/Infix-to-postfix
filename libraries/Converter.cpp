#include "Converter.h"
#include "Stack.h"
#include "Tree.h"

using std::string;
using std::to_string;

string Converter::convertToRPN(const string &str_in) {
    Stack<char> stack;
    bool wasNum = false;
    string result;

    stack.push('(');
    for (char symbol : str_in) {
        if ((symbol >= 'a' && symbol <= 'z') || (symbol >= 'A' && symbol <= 'Z') || (symbol >= '0' && symbol <= '9') ||
            symbol == '.') {
            result.push_back(symbol);
            wasNum = true;
        } else if (symbol == '(') {
            stack.push('(');
        } else if (symbol == ')') {
            symbol = stack.pop();

            if (symbol != '(' && wasNum) {
                result.push_back(' ');
                wasNum = false;
            }

            while (symbol != '(') {
                result.push_back(symbol);
                result.push_back(' ');
                symbol = stack.pop();
            }
        } else if (isOperation(symbol)) {
            char temp = stack.pop();

            if (wasNum) {
                result.push_back(' ');
                wasNum = false;
            }

            while (temp != '(' && priority(temp) >= priority(symbol)) {
                result.push_back(temp);
                result.push_back(' ');
                temp = stack.pop();
            }

            stack.push(temp);
            stack.push(symbol);
        }
    }

    if (wasNum) {
        result.push_back(' ');
    }

    char symbol = stack.pop();

    while (symbol != '(') {
        result.push_back(symbol);
        result.push_back(' ');
        symbol = stack.pop();
    }

    return result;
}

BiNode<string> *Converter::convertToTree(const string &str_in) {
    Stack<BiNode<string> *> result;
    Stack<char> signs;
    string num;

    signs.push('(');
    for (char symbol : str_in) {
        if (isVariable(symbol)) {
            num.push_back(symbol);
        } else if (symbol == '(') {
            signs.push('(');
        } else if (symbol == ')') {
            symbol = signs.pop();

            if (symbol != '(' && num.length() != 0) {
                result.push(new BiNode<string>(num));
                num = "";
            }

            while (symbol != '(') {
                BiNode<string> *r = result.pop();
                BiNode<string> *l;
                //negative numbers
                if (!result.is_empty()) {
                    l = result.pop();
                } else {
                    l = new BiNode<string>("0");
                }
                string s_temp;
                s_temp.push_back(symbol);
                result.push(new BiNode<string>(s_temp, l, r));
                symbol = signs.pop();
            }
        } else if (isOperation(symbol)) {
            char temp = signs.pop();

            if (num.length() != 0) {
                result.push(new BiNode<string>(num));
                num = "";
            }

            while (temp != '(' && priority(temp) >= priority(symbol)) {
                BiNode<string> *r = result.pop();
                BiNode<string> *l;
                //negative numbers
                if (!result.is_empty()) {
                    l = result.pop();
                } else {
                    l = new BiNode<string>("0");
                }

                string s_temp;
                s_temp.push_back(temp);
                result.push(new BiNode<string>(s_temp, l, r));
                temp = signs.pop();
            }

            signs.push(temp);
            signs.push(symbol);
        }
    }

    if (num.length() != 0) {
        result.push(new BiNode<string>(num));
        num = "";
    }

    char symbol = signs.pop();

    while (symbol != '(') {
        BiNode<string> *r = result.pop();
        BiNode<string> *l;
        //negative numbers
        if (!result.is_empty()) {
            l = result.pop();
        } else {
            l = new BiNode<string>("0");
        }
        string s_temp;
        s_temp.push_back(symbol);
        result.push(new BiNode<string>(s_temp, l, r));
        symbol = signs.pop();
    }

    return result.pop();
}

BiNode<string> *Converter::convertToSimplifiedTree(const string &str_in) {
    return simplifyTree(convertToTree(str_in));
}

string Converter::simplifyExpression(const string& str_in) {
    return convertToString(simplifyTree(convertToTree(str_in)));
}

BiNode<string> *Converter::simplifyTree(BiNode<string> *tree, bool removeLastSimplification) {
    BiNode<string> *res = nullptr;

    if (isVariable(tree->getValue())) {
        res =  new BiNode<string>(tree->getValue());
        //Если справа "0" или "1"
    } else if (isVariable(tree->getRight()->getValue()) &&
               (tree->getRight()->getValue() == "0" || tree->getRight()->getValue() == "1")) {
        //"0" справа от знаков "+", "-", "*", "^"
        if (tree->getRight()->getValue() == "0" &&
            (tree->getValue() == "+" || tree->getValue() == "-" || tree->getValue() == "*" || tree->getValue() == "^")) {
            if (tree->getValue() == "*") {
                res =  new BiNode<string>("0");
            } else if (tree->getValue() == "+" || tree->getValue() == "-") {
                res =  new BiNode<string>(simplifyTree(tree->getLeft()));
            } else if (tree->getValue() == "^") {
                res =  new BiNode<string>("1");
            }
            //"1" справа от знаков "*", "/", "^"
        } else if (tree->getRight()->getValue() == "1" &&
                   (tree->getValue() == "*" || tree->getValue() == "/" || tree->getValue() == "^")) {
            if (tree->getValue() == "*" || tree->getValue() == "/") {
                res =  new BiNode<string>(tree->getLeft());
            } else if (tree->getValue() == "^") {
                res =  new BiNode<string>(tree->getLeft());
            }
        }
        //Если слева "0" или "1"
    } else if (isVariable(tree->getLeft()->getValue()) &&
               (tree->getLeft()->getValue() == "0" || tree->getLeft()->getValue() == "1")) {
        //"0" слева от знаков "+", "-", "*", "/", "^"
        if (tree->getLeft()->getValue() == "0" &&
            (tree->getValue() == "+" || tree->getValue() == "-" || tree->getValue() == "*" || tree->getValue() == "/" ||
             tree->getValue() == "^")) {
            if (tree->getValue() == "*" || tree->getValue() == "/" || tree->getValue() == "^") {
                res =  new BiNode<string>("0");
            } else if (tree->getValue() == "+") {
                res =  new BiNode<string>(simplifyTree(tree->getRight()));
            } else if (tree->getValue() == "-" && isVariable(tree->getRight()->getValue())) {
                if(tree->getRight()->getValue()[0] == '-') {
                    res = new BiNode<string>(tree->getRight()->getValue().substr(1, tree->getRight()->getValue().length() - 1));
                } else {
                    res = new BiNode<string>("-"+tree->getRight()->getValue());
                }
            }
            //"1" слева от знаков "*", "^"
        } else if (tree->getLeft()->getValue() == "1" && (tree->getValue() == "*" || tree->getValue() == "^")) {
            if (tree->getValue() == "*") {
                res =  new BiNode<string>(simplifyTree(tree->getRight()));
            } else if (tree->getValue() == "^") {
                res =  new BiNode<string>("1");
            }
        }

//    } if(isNumericalVariable(tree->getLeft()->getValue()) && isNumericalVariable(tree->getRight()->getValue())) {
//        int l = strToInt(tree->getLeft()->getValue());
//        int r = strToInt(tree->getRight()->getValue());
//        return new BiNode<string>(to_string(doMath(tree->getValue(), l,r)));
    }

    if(res == nullptr) {
        res = new BiNode<string>(tree->getValue(), simplifyTree(tree->getLeft()), simplifyTree(tree->getRight()));

        //Проверка на то что слева или справа появилась константа на которую можно упростить
        if(!removeLastSimplification && (isVariable(res->getLeft()->getValue()) || isVariable(res->getRight()->getValue()))) {
            res =  simplifyTree(res, true);
        }
    }

    return res;
}

string Converter::convertToString(BiNode<string> *tree) {
    if (isVariable(tree->getValue())) {
        return tree->getValue();
    } else {
        string r = "";

        unsigned short int mp = isOperation(tree->getLeft()->getValue()) ? minPriority(tree->getLeft()) : 4;
        unsigned short int cp = priority(tree->getValue());
        if (mp < cp) {
            r += ("(" + convertToString(tree->getLeft()) + ")");
        } else {
            r += convertToString(tree->getLeft());
        }

        r += tree->getValue();

        mp = isOperation(tree->getRight()->getValue()) ? minPriority(tree->getRight()) : 4;
        if (mp <= cp) {
            r += ("(" + convertToString(tree->getRight()) + ")");
        } else {
            r += convertToString(tree->getRight());
        }

        return r;
    }
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

unsigned short int Converter::priority(string sign) {
    return priority(sign[0]);
}

bool Converter::isOperation(char sign) {
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

bool Converter::isOperation(string sign) {
    return sign.length() == 1 && isOperation(sign[0]);
}

bool Converter::isVariable(char symbol) {
    return (symbol >= 'a' && symbol <= 'z') || (symbol >= 'A' && symbol <= 'Z') || (symbol >= '0' && symbol <= '9') ||
           symbol == '.';
}

bool Converter::isVariable(string symbols) {
    return symbols.length() >= 2 || (symbols.length() >= 1 && isVariable(symbols[0]));
}

//bool Converter::isNumericalVariable(string symbols) {
//    bool res = true;
//
//    if(symbols[0] == '-' && symbols.length() == 1) {
//        res = false;
//    } else {
//        for (unsigned int i = 0 + (symbols[0] == '-'); i < symbols.length() && res; ++i) {
//            res = symbols[i] >= '0' && symbols[i] <= '9';
//        }
//    }
//
//    return res;
//}

unsigned short int Converter::minPriority(BiNode<string> *tree) {
    if (isVariable(tree->getLeft()->getValue()) && isVariable(tree->getRight()->getValue())) {
        return priority(tree->getValue());
    }

    unsigned short int l = isOperation(tree->getLeft()->getValue()) ? minPriority(tree->getLeft()) : 4;
    unsigned short int r = isOperation(tree->getRight()->getValue()) ? minPriority(tree->getRight()) : 4;
    unsigned short int m = priority(tree->getValue());

    return l < r ? (l < m ? l : m) : (r < m ? r : m);
}

//int Converter::strToInt(const string& str) {
//    int res = 0;
//    unsigned int factor = 1;
//
//    for (int i = str.length() - 1; i >= 0 + (str[0] == '-'); --i) {
//        res += (str[i] - '0') * factor;
//    }
//
//    return str[0] == '-' ? -res : res;
//}

//int Converter::doMath(const string& str, int l, int r) {
//    int res = 0;
//
//    switch (str[0]) {
//        case '^':
//            res = pow(l,r);
//            break;
//        case '*':
//            res = l * r;
//            break;
//        case ':':
//        case '/':
//            res = l / r;
//            break;
//        case '+':
//            res = l + r;
//            break;
//        case '-': {
//            res = l - r;
//            break;
//        }
//    }
//
//    return res;
//}

//int Converter::pow(int number, unsigned int exp) {
//    int result = 1;
//    for (unsigned int i = 0; i < exp; ++i) {
//        result *= number;
//    }
//    return result;
//}