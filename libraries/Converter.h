#pragma once

#include <iostream>

using std::string;

class Converter {
private:
    static unsigned short int priority(char sign);
    static bool is_operation(char sign);
public:
    static string convert(string file_in);
};
