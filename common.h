#pragma once
#include <vector>

// custom swap function for just pointer swapping (check difference)
void swap(uint32_t* a, uint32_t* b)
{
    uint32_t temp = *a;
    *a = *b;
    *b = temp;
}

// comparator function used by qsort
int compare(const void* a, const void* b)
{
    // TODO: check why this does not return the same results???
    //return (*(uint32_t*)a - *(uint32_t*)b);
    //return (int)(*(int*)a - *(int*)b);
    //return (int)(*(const int*)a - *(const int*)b);
    uint32_t arg1 = *static_cast<const uint32_t*>(a);
    uint32_t arg2 = *static_cast<const uint32_t*>(b);
    if (arg1 < arg2) return -1;
    if (arg1 > arg2) return 1;
    return 0;
}

#define PARTITION_TYPE_LOMUTO
//#define PARTITION_TYPE_HOARE

#ifdef PARTITION_TYPE_LOMUTO
// Lomuto Partitioning
int partition(std::vector<uint32_t>& a, int p, int r)
{
    uint32_t pivotValue = a[r];
    /*int i = p - 1;
    for (int j = p; j < r; j++)
    {
        if (a[j] <= pivotValue)
        {
            i++;
            swap(&a[i], &a[j]);
        }
    }
    swap(&a[i + 1], &a[r]);
    return (i + 1);*/
    int i = p;
    for (int j = p; j < r; j++)
    {
        if (a[j] <= pivotValue)
        {
            swap(&a[i], &a[j]);
            i++;
        }
    }
    swap(&a[i], &a[r]);
    return i;
}
#elif defined PARTITION_TYPE_HOARE
// Hoare Partitioning
int partition(std::vector<uint32_t>& a, int p, int r)
{
    uint32_t pivotValue = a[p];
    int i = p - 1;
    int j = r + 1;
    while (true)
    {
        do { i++; } while (a[i] < pivotValue);

        do { j--; } while (a[j] > pivotValue);

        if (i >= j) return j;

        swap(&a[i], &a[j]);
    }
}
#endif