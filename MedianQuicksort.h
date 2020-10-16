#pragma once

uint32_t pivotPartition(std::vector<uint32_t>& values, uint32_t left, uint32_t right) {
    uint32_t pivotIndex = left + (right - left) / 2;
    uint32_t pivotValue = values[pivotIndex];
    int i = left;
    int j = right;
    while (i <= j) {
        while (values[i] < pivotValue)
        {
            i++;
        }
        while (values[j] > pivotValue)
        {
            j--;
        }
        if (i <= j) {
            swap(&values[i], &values[j]);
            i++;
            j--;
        }
    }
    return i;
}

void quicksort(std::vector<uint32_t>& values, uint32_t left, uint32_t right)
{
    if (left < right) {
        uint32_t pivotIndex = pivotPartition(values, left, right);
        quicksort(values, left, pivotIndex - 1);
        quicksort(values, pivotIndex, right);
    }
}

uint32_t getQuicksortMedian(std::vector<uint32_t> values, uint32_t i)
{
    //std::qsort(numbers); // only takes array param -> custom implementation with vector
    quicksort(values, 0, values.size() - 1);
    return values[i];
}