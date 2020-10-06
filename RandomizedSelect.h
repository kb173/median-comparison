#pragma once

#include <vector>

/*
// Pseudo code Alux Nimmervoll, Algo vo3
// Anmerkung: code funktioniert!

RANDOMIZED-SELECT(A,p,r,i)
    if (p==r) then return A[p]
    q=RANDOMIZED_PARTITION(A,p,r) //Pivot Element A[q]
    k=q-p+1 //Anzahl Elemente A[p..q]
    if (i==k) then return A[q] //Pivot ist das gesuchte
    elseif (i<k)
    then return RANDOMIZED-SELECT(A,p,q-1,i)
    else return RANDOMIZED-SELECT(A,q+1,r,i-k)
*/

size_t randomizedPartition(std::vector<size_t>& values, size_t p, size_t r) {
    size_t i = p + rand() % (r - p + 1); // generate a random number in {p, ..., r}
    std::swap(values[i], values[r]);

    size_t pivotValue = values[r];
    i = p - 1;
    for (size_t j = p; j < r; j++) {
        if (values[j] <= pivotValue) {
            i++;
            std::swap(values[i], values[j]);
        }
    }
    std::swap(values[i + 1], values[r]);
    return i + 1;
}

size_t randomizedSelect(std::vector<size_t> values, size_t p, size_t r, size_t i)
{
    if (p == r) return values[p];

    size_t q = randomizedPartition(values, p, r); // Pivot Element A[q]
    size_t k = q - p + 1; // Anzahl Elemente A[p..q]
    if (i == k) return values[q]; // Pivot ist das gesuchte
    else if (i < k)
        return randomizedSelect(values, p, q - 1, i);
    else return randomizedSelect(values, q + 1, r, i - k);
}