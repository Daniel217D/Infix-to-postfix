#include <iostream>
#include <fstream>
#include "libraries/Converter.h"
#include "libraries/Tree.h"

using std::cout;
using std::ifstream;
using std::ofstream;

int main() {
    ifstream fin("files/in.txt");
    string data;
    getline(fin, data);
    //TODO ОНО ПАДАЕТ ПРИ ТЕКУЩЕМ ВВОДЕ, ХЗ ПОЧЕМУ, !!БАГИ!!
    BiNode<string> * f1 = Converter::convertToSimplifiedTree(data);
    cout << Converter::convertToRPN(data) << "\n";
    cout << Converter::convertToString(f1);
//    f1 = Converter::simplifyTree(f1);
//    auto f2 = new BiNode<string>(f1);
//    data = Converter::convertToRPN(data);
//    cout << data;

    return 0;
}
