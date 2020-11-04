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
    static unsigned short int minPriority(BiNode<string>* tree);
public:
    static string convertToRPN(const string& str_in);
    static BiNode<string> *convertToTree(const string& str_in);
    static BiNode<string> *convertToSimplifiedTree(const string& str_in);
    static BiNode<string> *simplifyTree(BiNode<string>* tree);
    static string convertToString(BiNode<string>* tree);
};
