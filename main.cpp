#include <iostream>
#include <algorithm> // std::nth_element

#include "fileHandler.h"
#include "Timing.h"
#include "MedianQuicksort.h"
#include "MedianOfMedians.h"
#include "RandomizedSelect.h"

int main(int argc, char** argv) {
    // read test values from input file
    Timing::getInstance()->startRecord("init");
    std::vector<size_t> numbers = readFromFile("testdata");
    std::cout << "just read " << numbers.size() << " values" << std::endl;
    Timing::getInstance()->stopRecord("init");

    // index of median -> if odd count +1
    size_t idxMed = numbers.size() / 2;
    std::cout << "median =  " << idxMed << std::endl;
    if (idxMed - (int)idxMed > 0) idxMed++;

    // vollständige Sortierung mit Quicksort und Ausgabe des mittleren Elements
    Timing::getInstance()->startRecord("quicksort");
    std::cout << "quicksort median: " << getQuicksortMedian(numbers, idxMed) << std::endl;
    Timing::getInstance()->stopRecord("quicksort");

    // vorgestellter Randomzized - Select rekursiv implementiert
    Timing::getInstance()->startRecord("randomized select");
    std::cout << "randomized select: " << randomizedSelect(numbers, 0, numbers.size() - 1, idxMed) << std::endl;
    Timing::getInstance()->stopRecord("randomized select");

    // ein weiterer Median - Algorithmus aus der Literatur
    Timing::getInstance()->startRecord("median of medians");
    std::cout << "median of medians: " << getMedianOfMedians(numbers, idxMed) << std::endl;
    Timing::getInstance()->stopRecord("median of medians");

    // noch ein ein weiterer Median - Algorithmus weil wir so cool sind
    Timing::getInstance()->startRecord("wirth");
    Timing::getInstance()->stopRecord("wirth");

    // Verwendung des C++ STL function templates nth_element
    Timing::getInstance()->startRecord("nth element");
    std::nth_element(numbers.begin(), numbers.begin() + idxMed, numbers.end());
    std::cout << "nth element: " << numbers[idxMed] << std::endl;
    Timing::getInstance()->stopRecord("nth element");

    //Timing::getInstance()->getResults();
    Timing::getInstance()->print();
    return 0;
}