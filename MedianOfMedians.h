#pragma once

// https://en.wikipedia.org/wiki/Median_of_medians
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