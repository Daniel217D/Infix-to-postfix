#include <iostream>
#include <fstream>
#include "libraries/Converter.h"

using std::cout;
using std::ifstream;
using std::ofstream;

int main() {
    ifstream fin("files/in.txt");
    string data;
    getline(fin, data);

    data = Converter::convert(data);

    cout << data;

    return 0;
}
