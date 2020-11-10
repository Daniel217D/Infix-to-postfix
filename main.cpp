#include <iostream>
#include <fstream>
#include "libraries/Converter.h"
#include "libraries/Tree.h"

using std::cout;
using std::ifstream;
using std::ofstream;

int main() {
    ifstream fin("files/in.txt");
    ofstream fout("files/out.txt");
    string data;

    while(!fin.eof()) {
        getline(fin, data);
        fout << Converter::simplifyExpression(data) << "\n";
    }

    fin.close();
    fout.close();
    return 0;
}
