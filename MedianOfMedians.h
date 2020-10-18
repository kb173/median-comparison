#pragma once

// Implemented pseudocode from https://en.wikipedia.org/wiki/Median_of_medians

uint32_t pivot(std::vector<uint32_t> &v, uint32_t left, uint32_t right);
uint32_t partition(std::vector<uint32_t> &v, uint32_t left, uint32_t right, uint32_t pivotIndex, uint32_t n);

// Return the index of an element which is close to (but likely not exactly) the median.
uint32_t findMedianOfMedians(std::vector<uint32_t> &v, uint32_t left, uint32_t right, uint32_t n) {
 
    while (true) {
        if (left == right) {
            return left;
        }

        uint32_t pivotIndex = pivot(v, left, right);
        pivotIndex = partition(v, left, right, pivotIndex, n);

        if (n == pivotIndex) {
            return n;
        } else if (n < pivotIndex) {
            right = pivotIndex - 1;
        } else {
            left = pivotIndex + 1;
        }
    }
}

uint32_t partition(std::vector<uint32_t> &v, uint32_t left, uint32_t right, uint32_t pivotIndex, uint32_t n) {
    
    uint32_t pivotValue = v[pivotIndex];
    swap(&v[pivotIndex], &v[right]);

    uint32_t storeIndex = left;

    // Move all elements smaller than the pivot to the left of the pivot
    for (uint32_t i = left; i < right; i++) {
        if (v[i] < pivotValue) {
            swap(&v[storeIndex], &v[i]);
            storeIndex++;
        }
    }

    // Move all elements equal to the pivot right after
    // the smaller elements
    uint32_t storeIndexEq = storeIndex;

    for (uint32_t i = storeIndex; i < right; i++) {
        if (v[i] == pivotValue) {
            swap(&v[storeIndexEq], &v[i]);
            storeIndexEq++;
        }
    }

    swap(&v[right], &v[storeIndexEq]);

    if (n < storeIndex) {
        return storeIndex;
    }
    if (n <= storeIndexEq) {
        return n;
    }
    return storeIndexEq;
}

uint32_t partition5(std::vector<uint32_t> &v, uint32_t left, uint32_t right) {
    uint32_t i = left + 1;

    while (i <= right) {
        uint32_t j = i;

        while (j > left && v[j - 1] > v[j]) {
            swap(&v[j - 1], &v[j]);
            j = j - 1;
        }
        i = i + 1;
    }
    return (left + right) / 2;
}

uint32_t pivot(std::vector<uint32_t> &v, uint32_t left, uint32_t right) {
    // for 5 or less elements just get median
    if (right - left < 5) {
        return partition5(v, left, right);
    }

    // otherwise move the medians of five-element subgroups to the first n/5 positions
    for (uint32_t i = left; i <= right; i += 5) {
        // get the median position of the i'th five-element subgroup
        uint32_t subRight = i + 4;

        if (subRight > right) {
            subRight = right;
        }

        uint32_t median5 = partition5(v, i, subRight);
        swap(&v[median5], &v[left + (i - left) / 5]);
    }

    // compute the median of the n/5 medians-of-five
    uint32_t mid = (right - left) / 10 + left + 1;
    return findMedianOfMedians(v, left, left + (right - left) / 5, mid);
}

uint32_t getMedianOfMedians(std::vector<uint32_t> v, uint32_t left, uint32_t right, uint32_t n) {
    return v[findMedianOfMedians(v, left, right, n)];
}