#pragma once

int partition(std::vector<size_t>& values, int left, int right) {
    int pivotIndex = left + (right - left) / 2;
    int pivotValue = values[pivotIndex];
    int i = left, j = right;
    int temp;
    while (i <= j) {
        while (values[i] < pivotValue) {
            i++;
        }
        while (values[j] > pivotValue) {
            j--;
        }
        if (i <= j) {
            temp = values[i];
            values[i] = values[j];
            values[j] = temp;
            i++;
            j--;
        }
    }
    return i;
}

void quicksort(std::vector<size_t>& values, int left, int right) {
    if (left < right) {
        int pivotIndex = partition(values, left, right);
        quicksort(values, left, pivotIndex - 1);
        quicksort(values, pivotIndex, right);
    }
}

size_t getMedian(std::vector<size_t> values) {
    //std::qsort(numbers); // only takes array param
    quicksort(values, 0, values.size() - 1);
    size_t idxMed = values.size() / 2;
    if (idxMed - (int)idxMed > 0) idxMed++;
    return values[idxMed];
}