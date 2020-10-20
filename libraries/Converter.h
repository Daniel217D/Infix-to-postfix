#pragma once

#include <iostream>
//#include "Stack.h"

using std::string;

class Converter {
private:
    static unsigned short int priority(char sign);
    static bool is_operation(char sign);
public:
    static bool convert(string file_in, string file_out);
};
