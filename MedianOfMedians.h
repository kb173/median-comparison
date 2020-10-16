#pragma once

// https://en.wikipedia.org/wiki/Median_of_medians
// https://oneraynyday.github.io/algorithms/2016/06/17/Median-Of-Medians/
// https://www.geeksforgeeks.org/kth-smallestlargest-element-unsorted-array-set-3-worst-case-linear-time/

uint32_t findMedian(std::vector<uint32_t> values)
{
    return values[(values.size() / 2)];
}

uint32_t findMedianOfMedians(std::vector<std::vector<uint32_t> > values)
{
    std::vector<uint32_t> medians;
    for (size_t i = 0; i < values.size(); i++) {
        uint32_t m = findMedian(values[i]);
        medians.push_back(m);
    }
    return findMedian(medians);
}

uint32_t getMedianOfMedians(const std::vector<uint32_t> values, uint32_t k)
{
    // Divide the list into n/5 lists of 5 elements each
    std::vector<std::vector<uint32_t> > vec2D;
    size_t count = 0;
    while (count != values.size()) {
        size_t countRow = 0;
        std::vector<uint32_t> row;
        while ((countRow < 5) && (count < values.size()))
        {
            row.push_back(values[count]);
            count++;
            countRow++;
        }
        vec2D.push_back(row);
    }

    // Calculating a new pivot for making splits
    uint32_t m = findMedianOfMedians(vec2D);

    // Partition the list into unique elements larger than 'm' (call this sublist L1) and those smaller them 'm' (call this sublist L2)
    std::vector<uint32_t> L1, L2;

    for (size_t i = 0; i < vec2D.size(); i++)
    {
        for (size_t j = 0; j < vec2D[i].size(); j++)
        {
            if (vec2D[i][j] > m)
            {
                L1.push_back(vec2D[i][j]);
            }
            else if (vec2D[i][j] < m)
            {
                L2.push_back(vec2D[i][j]);
            }
        }
    }

    if (k <= L1.size())
    {
        return getMedianOfMedians(L1, k);
    }
    else if (k > (L1.size() + 1))
    {
        return getMedianOfMedians(L2, k - ((int)L1.size()) - 1);
    }
    return m;
}

// A simple function to find median of arr[].
// This is called only for an array of size 5 in this program.
uint32_t findMedian(uint32_t arr[], int n)
{
    std::sort(arr, arr + n);  // Sort the array
    return arr[n / 2];   // Return middle element
}

// searches for x in arr[l..r], and partitions the array around x
int partition(uint32_t arr[], int l, int r, uint32_t pivotValue)
{
    // Search for x in arr[l..r] and move it to end
    int i;
    for (i = l; i < r; i++)
        if (arr[i] == pivotValue)
            break;
    swap(&arr[i], &arr[r]);

    // Standard partition algorithm
    i = l;
    for (int j = l; j < r; j++)
    {
        if (arr[j] <= pivotValue)
        {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i], &arr[r]);
    return i;
}

// Returns k'th smallest element in arr[l..r] in worst case
// linear time. ASSUMPTION: ALL ELEMENTS IN ARR[] ARE DISTINCT
//int getMedianOfMedians(int arr[], int l, int r, int k)
uint32_t getMedianOfMedians(uint32_t* arr, int l, int r, int k)
{
    int n = r - l + 1; // Number of elements in arr[l..r]

    // Divide arr[] in groups of size 5, calculate median
    // of every group and store it in median[] array.
    // There will be floor((n + 4) / 5) groups;
    //int median[(n + 4) / 5]; // non VS compliant!
    uint32_t* median = new uint32_t[(n + 4) / 5];
    int i = 0;
    for (i = 0; i < n / 5; i++)
        median[i] = findMedian(arr + l + i * 5, 5);
    if (i * 5 < n) //For last group with less than 5 elements
    {
        median[i] = findMedian(arr + l + i * 5, n % 5);
        i++;
    }

    // Find median of all medians using recursive call.
    // If median[] has only one element, then no need for recursive call
    uint32_t medOfMed = (i == 1) ? median[0] : getMedianOfMedians(median, 0, i - 1, i / 2);

    // Partition the array around a random element and
    // get position of pivot element in sorted array
    int pos = partition(arr, l, r, medOfMed);

    if (pos - l == k - 1) return arr[pos];
    else if (pos - l > k - 1)
        return getMedianOfMedians(arr, l, pos - 1, k);
    else return getMedianOfMedians(arr, pos + 1, r, k - pos + l - 1);
}
