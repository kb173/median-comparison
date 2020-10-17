#pragma once

int pivotPartition(std::vector<uint32_t>& a, int p, int r) {

    return partition(a, p, r);
}

void quicksort(std::vector<uint32_t>& a, int p, int r)
{
    if (p < r) {
        int i = pivotPartition(a, p, r);
#ifdef PARTITION_TYPE_LOMUTO
        quicksort(a, p, i - 1);
#elif defined PARTITION_TYPE_HOARE
        quicksort(a, p, i);
#endif
        quicksort(a, i + 1, r);
    }
}

uint32_t getQuicksortMedian(std::vector<uint32_t> a, int i)
{
    //std::qsort(numbers); // only takes array param -> custom implementation with vector
    quicksort(a, 0, a.size() - 1);
    return a[i];
}