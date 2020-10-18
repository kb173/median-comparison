#pragma once

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