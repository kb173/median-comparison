#pragma once

int randomizedPartition(std::vector<uint32_t>& a, int p, int r)
{
    // generate a random number in {p, ..., r} to swap
#ifdef PARTITION_TYPE_LOMUTO
    int i = p + rand() % (r - p);
    swap(&a[i], &a[r]);
#elif defined PARTITION_TYPE_HOARE
    int i = rand() % (r - p + 1);
    swap(&a[p + i], &a[r]);
#endif
    return partition(a, p, r);
}

uint32_t randomizedSelect(std::vector<uint32_t>& a, int p, int r, int i)
{
    // -----------------------------------------------------------
    // Pseudo code Alux Nimmervoll, Algo vo3
    // Anmerkung: code funktioniert!
    //
    // RANDOMIZED-SELECT(A,p,r,i)
    //    if (p==r) then return A[p]
    //    q=RANDOMIZED_PARTITION(A,p,r) //Pivot Element A[q]
    //    k=q-p+1 //Anzahl Elemente A[p..q]
    //    if (i==k) then return A[q] //Pivot ist das gesuchte
    //    elseif (i<k)
    //    then return RANDOMIZED-SELECT(A,p,q-1,i)
    //    else return RANDOMIZED-SELECT(A,q+1,r,i-k)
    // -----------------------------------------------------------

    if (p == r) return a[p];

    int q = randomizedPartition(a, p, r); // Pivot Element A[q]
    int k = q - p + 1; // Anzahl Elemente A[p..q]
    if (i == k) return a[q]; // Pivot ist das gesuchte
    else if (i < k)
    #ifdef PARTITION_TYPE_LOMUTO
        return randomizedSelect(a, p, q - 1, i);
    #elif defined PARTITION_TYPE_HOARE
        return randomizedSelect(a, p, q, i);
    #endif
    else return randomizedSelect(a, q + 1, r, i - k);
}

uint32_t getRandomizedSelectMedian(std::vector<uint32_t> a, int p, int r, int i)
{
    return randomizedSelect(a, p, r, i);
}