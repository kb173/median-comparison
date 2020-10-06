#pragma once

size_t pivotPartition(std::vector<size_t>& values, size_t left, size_t right) {
    size_t pivotIndex = left + (right - left) / 2;
    size_t pivotValue = values[pivotIndex];
    size_t i = left;
    size_t j = right;
    while (i <= j) {
        while (values[i] < pivotValue) {
            i++;
        }
        while (values[j] > pivotValue) {
            j--;
        }
        if (i <= j) {
            std::swap(values[i], values[j]);
            i++;
            j--;
        }
    }
    return i;
}

void quicksort(std::vector<size_t>& values, size_t left, size_t right) {
    if (left < right) {
        size_t pivotIndex = pivotPartition(values, left, right);
        quicksort(values, left, pivotIndex - 1);
        quicksort(values, pivotIndex, right);
    }
}

size_t getQuicksortMedian(std::vector<size_t> values, size_t i) {
    //std::qsort(numbers); // only takes array param -> custom implementation with vector
    quicksort(values, 0, values.size() - 1);
    return values[i];
}