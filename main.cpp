#include <iostream>

#include "fileHandler.h"
#include "Timing.h"

int main(int argc, char** argv) {
    Timing::getInstance()->startRecord("init");
    std::vector<size_t> numbers = readFromFile("testdata");
    std::cout << "read " << numbers.size() << " values" << std::endl;
    Timing::getInstance()->stopRecord("init");

    Timing::getInstance()->startRecord("test");
    Timing::getInstance()->stopRecord("test");
    //Timing::getInstance()->getResults();
    Timing::getInstance()->print();
    return 0;
}