#pragma once

// https://en.wikipedia.org/wiki/Median_of_medians
// https://oneraynyday.github.io/algorithms/2016/06/17/Median-Of-Medians/
// https://www.geeksforgeeks.org/kth-smallestlargest-element-unsorted-array-set-3-worst-case-linear-time/

int findMedian(std::vector<size_t> values) {
    size_t median;
    size_t size = values.size();
    median = values[(size / 2)];
    return median;
}

int findMedianOfMedians(std::vector<std::vector<size_t> > values) {
    std::vector<size_t> medians;
    for (size_t i = 0; i < values.size(); i++) {
        size_t m = findMedian(values[i]);
        medians.push_back(m);
    }
    return findMedian(medians);
}

size_t getMedianOfMedians(const std::vector<size_t> values, size_t k) {
    // Divide the list into n/5 lists of 5 elements each
    std::vector<std::vector<size_t> > vec2D;
    size_t count = 0;
    while (count != values.size()) {
        size_t countRow = 0;
        std::vector<size_t> row;
        while ((countRow < 5) && (count < values.size())) {
            row.push_back(values[count]);
            count++;
            countRow++;
        }
        vec2D.push_back(row);
    }

    // Calculating a new pivot for making splits
    size_t m = findMedianOfMedians(vec2D);

    // Partition the list into unique elements larger than 'm' (call this sublist L1) and those smaller them 'm' (call this sublist L2)
    std::vector<size_t> L1, L2;

    for (size_t i = 0; i < vec2D.size(); i++) {
        for (size_t j = 0; j < vec2D[i].size(); j++) {
            if (vec2D[i][j] > m) {
                L1.push_back(vec2D[i][j]);
            }
            else if (vec2D[i][j] < m) {
                L2.push_back(vec2D[i][j]);
            }
        }
    }

    if (k <= L1.size()) {
        return getMedianOfMedians(L1, k);
    }
    else if (k > (L1.size() + 1)) {
        return getMedianOfMedians(L2, k - ((int)L1.size()) - 1);
    }
    return m;
}

// custom swap function
void swap(size_t* a, size_t* b)
{
    size_t temp = *a;
    *a = *b;
    *b = temp;
}

// A simple function to find median of arr[].  This is called
// only for an array of size 5 in this program.
int findMedian(size_t arr[], int n)
{
    std::sort(arr, arr + n);  // Sort the array
    return arr[n / 2];   // Return middle element
}

// It searches for x in arr[l..r], and partitions the array
// around x.
int partition(size_t arr[], int l, int r, int x)
{
    // Search for x in arr[l..r] and move it to end
    int i;
    for (i = l; i < r; i++)
        if (arr[i] == x)
            break;
    swap(&arr[i], &arr[r]);

    // Standard partition algorithm
    i = l;
    for (int j = l; j <= r - 1; j++)
    {
        if (arr[j] <= x)
        {
            swap(&arr[i], &arr[j]);
            i++;
        }
    }
    swap(&arr[i], &arr[r]);
    return i;
}

// Returns k'th smallest element in arr[l..r] in worst case
// linear time. ASSUMPTION: ALL ELEMENTS IN ARR[] ARE DISTINCT
//int getMedianOfMedians(int arr[], int l, int r, int k)
size_t getMedianOfMedians(size_t* arr, int l, int r, int k)
{
    // If k is smaller than number of elements in array
    if (k > 0 && k <= r - l + 1)
    {
        int n = r - l + 1; // Number of elements in arr[l..r]

        // Divide arr[] in groups of size 5, calculate median
        // of every group and store it in median[] array.
        // There will be floor((n + 4) / 5) groups;
        //int median[(n + 4) / 5]; // non VS compliant!
        size_t* median = new size_t[(n + 4) / 5];
        int i = 0;
        for (i = 0; i < n / 5; i++)
            median[i] = findMedian(arr + l + i * 5, 5);
        if (i * 5 < n) //For last group with less than 5 elements
        {
            median[i] = findMedian(arr + l + i * 5, n % 5);
            i++;
        }

        // Find median of all medians using recursive call.
        // If median[] has only one element, then no need
        // of recursive call
        int medOfMed = (i == 1) ? median[i - 1] :
            getMedianOfMedians(median, 0, i - 1, i / 2);

        // Partition the array around a random element and
        // get position of pivot element in sorted array
        int pos = partition(arr, l, r, medOfMed);

        // If position is same as k
        if (pos - l == k - 1)
            return arr[pos];
        if (pos - l > k - 1)  // If position is more, recur for left
            return getMedianOfMedians(arr, l, pos - 1, k);

        // Else recur for right subarray
        return getMedianOfMedians(arr, pos + 1, r, k - pos + l - 1);
    }

    // If k is more than number of elements in array
    return SIZE_MAX;
}
