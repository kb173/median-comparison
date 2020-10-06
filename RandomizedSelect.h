#pragma once

/*
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