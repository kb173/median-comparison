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

    // index of median
    if (numbers.size() % 2 == 0)
    {
        std::cout << "TODO: define how to handly even datasets" << std::endl;
        return 1;
    }

    size_t idxMed = (numbers.size() - 1) / 2;
    std::cout << "median =  " << idxMed << std::endl;

    // vollständige Sortierung mit Quicksort und Ausgabe des mittleren Elements
    Timing::getInstance()->startRecord("quicksort");
    //std::cout << "quicksort median: " << getQuicksortMedian(numbers, idxMed) << std::endl;
    Timing::getInstance()->stopRecord("quicksort");

    // using std quicksort for array
    // TODO: decide how the fuck to create a dynamic size array from vector...
    //size_t* array = new size_t[numbers.size]; // create and fill new array
    //size_t* array = &numbers[0]; // just a pointer to first element as array
    //size_t* array[numbers.size()]; // invalid c++ -> non-constant expression!
    //std::copy(numbers.begin(), numbers.end(), array);
    //size_t* tmp = numbers.data(); // c++11 returns pointer to first elem
    size_t* array = new size_t[999999]; // create and fill new array
    std::copy(numbers.begin(), numbers.end(), array);
    Timing::getInstance()->startRecord("array quicksort");
    std::qsort(array, numbers.size(), sizeof(size_t), [](const void* a, const void* b)
    {
        size_t arg1 = *static_cast<const size_t*>(a);
        size_t arg2 = *static_cast<const size_t*>(b);
        if (arg1 < arg2) return -1;
        if (arg1 > arg2) return 1;
        return 0;
    });
    std::cout << "array quicksort median: " << array[idxMed] << std::endl;
    Timing::getInstance()->stopRecord("array quicksort");

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