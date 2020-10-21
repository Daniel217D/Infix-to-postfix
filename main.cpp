#include <iostream>

#include "libraries/Converter.h"

using std::cout;

int main() {
    bool res = Converter::convert("files/in.txt", "files/out.txt");

    if(res) {
        cout << "Программа успешно завершена";
    } else {
        cout << "Ошибка в работе программы";
    }

    return 0;
}
