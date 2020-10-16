#pragma once

#include <vector>

// Lomuto Partitioning
int randomizedPartition(std::vector<uint32_t>& values, int p, int r)
{
    int i = p + rand() % (r - p); // generate a random number in {p, ..., r}
    swap(&values[i], &values[r]);

    uint32_t pivotValue = values[r];
    i = p - 1;
    for (int j = p; j < r; j++)
    {
        if (values[j] <= pivotValue)
        {
            i++;
            swap(&values[i], &values[j]);
        }
    }
    swap(&values[i + 1], &values[r]);
    return (i + 1);
}

// TODO: Hoare Partitioning
// https://www.geeksforgeeks.org/quicksort-using-random-pivoting/
int randomizedPartition2(std::vector<uint32_t>& values, int low, int high)
{
    int i = low + rand() % (high - low); // generate a random number in {p, ..., r}
    swap(&values[i], &values[low]);

    uint32_t pivotValue = values[low];
    i = low - 1;
    int j = high + 1;
    while (true) {
        // Find leftmost element greater than
        // or equal to pivot
        do {
            i++;
        } while (values[i] < pivotValue);

        // Find rightmost element smaller than
        // or equal to pivot
        do {
            j--;
        } while (values[j] > pivotValue);

        // If two pointers met
        if (i >= j)
            return j;

        swap(&values[i], &values[j]);
    }
}

int randomizedPartition3(std::vector<uint32_t>& values, int l, int r)
{
    int i = rand() % (r - l + 1);
    swap(&values[l + i], &values[r]);

    uint32_t pivotValue = values[r];
    i = l;
    for (int j = l; j <= r - 1; j++)
    {
        if (values[j] <= pivotValue)
        {
            swap(&values[i], &values[j]);
            i++;
        }
    }
    swap(&values[i], &values[r]);
    return i;
}

uint32_t randomizedSelect(std::vector<uint32_t>& values, int p, int r, int i)
{
    /*
    // Partition the array around a random element and
    // get position of pivot element in sorted array
    int pos = randomizedPartition(values, p, r);

    // If position is same as k
    if (pos - p == i - 1)
        return values[pos];
    if (pos - p > i - 1)  // If position is more, recur for left subarray
        return randomizedSelect(values, p, pos - 1, i);

    // Else recur for right subarray
    return randomizedSelect(values, pos + 1, r, i - pos + p - 1);
    */

    // Pseudo code Alux Nimmervoll, Algo vo3
    // Anmerkung: code funktioniert!
    /*
    RANDOMIZED-SELECT(A,p,r,i)
        if (p==r) then return A[p]
        q=RANDOMIZED_PARTITION(A,p,r) //Pivot Element A[q]
        k=q-p+1 //Anzahl Elemente A[p..q]
        if (i==k) then return A[q] //Pivot ist das gesuchte
        elseif (i<k)
        then return RANDOMIZED-SELECT(A,p,q-1,i)
        else return RANDOMIZED-SELECT(A,q+1,r,i-k)
    */

    if (p == r) return values[p];

    int q = randomizedPartition(values, p, r); // Pivot Element A[q]
    //int q = randomizedPartition2(values, p, r); // Pivot Element A[q]
    //int q = randomizedPartition3(values, p, r); // Pivot Element A[q]
    int k = q - p + 1; // Anzahl Elemente A[p..q]
    if (i == k) return values[q]; // Pivot ist das gesuchte
    else if (i < k)
        return randomizedSelect(values, p, q - 1, i);
    else return randomizedSelect(values, q + 1, r, i - k);
}

uint32_t getRandomizedSelectMedian(std::vector<uint32_t> values, int p, int r, int i)
{
    return randomizedSelect(values, p, r, i);
}