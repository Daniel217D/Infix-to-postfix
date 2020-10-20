#include <iostream>

#include "libraries/Converter.h"

using std::cout;

int main() {
    Converter::convert("files/in.txt", "files/out.txt");

    return 0;
}
