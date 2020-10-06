#include <iostream>
#include <algorithm> // std::nth_element

#include "fileHandler.h"
#include "Timing.h"
#include "MedianQuicksort.h"

int main(int argc, char** argv) {
    Timing::getInstance()->startRecord("init");
    std::vector<size_t> numbers = readFromFile("testdata");
    std::cout << "read " << numbers.size() << " values" << std::endl;
    Timing::getInstance()->stopRecord("init");

    // vollständige Sortierung mit Quicksort und Ausgabe des mittleren Elements
    Timing::getInstance()->startRecord("quicksort");
    std::cout << "quicksort median: " << getMedian(numbers) << std::endl;
    Timing::getInstance()->stopRecord("quicksort");

    // Verwendung des C++ STL function templates nth_element
    Timing::getInstance()->startRecord("nth element");
    std::nth_element(numbers.begin(), numbers.begin() + numbers.size() / 2, numbers.end());
    size_t idxMed = numbers.size() / 2;
    if (idxMed - (int)idxMed > 0) idxMed++;
    std::cout << "nth element: " << numbers[idxMed] << std::endl;
    Timing::getInstance()->stopRecord("nth element");

    //Timing::getInstance()->getResults();
    Timing::getInstance()->print();
    return 0;
}