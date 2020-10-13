#pragma once

// custom swap function
void swap(size_t* a, size_t* b)
{
    size_t temp = *a;
    *a = *b;
    *b = temp;
}