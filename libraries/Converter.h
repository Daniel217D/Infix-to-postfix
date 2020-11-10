#pragma once
#include "Tree.h"
#include <iostream>

using std::string;

class Converter {
private:
    static unsigned short int priority(char sign);
    static unsigned short int priority(string sign);
    static bool isOperation(char sign);
    static bool isOperation(string sign);
    static bool isVariable(char symbol);
    static bool isVariable(string symbols);
//    static bool isNumericalVariable(string symbols);
    static unsigned short int minPriority(BiNode<string>* tree);
//    static int strToInt(const string& str);
//    static int doMath(const string& str, int l, int r);
//    static int pow(int number, unsigned int exp);
public:
    static string convertToRPN(const string& str_in);
    static BiNode<string> *convertToTree(const string& str_in);
    static BiNode<string> *convertToSimplifiedTree(const string& str_in);
    static BiNode<string> *simplifyTree(BiNode<string>* tree, bool removeLastSimplification = false);
    static string simplifyExpression(const string& str_in);
    static string convertToString(BiNode<string>* tree);
};
