#pragma once

// http://ndevilla.free.fr/median/median/index.html

uint32_t getWirthKthSmallest(std::vector<uint32_t> a, uint32_t k)
{
    uint32_t l = 0;
    uint32_t m = a.size() - 1;

    while (l < m) {
        uint32_t x = a[k];
        uint32_t i = l;
        uint32_t j = m;

        do {
            while (a[i] < x) i++;
            while (x < a[j]) j--;

            if (i <= j) {
                swap(&a[i], &a[j]);
                i++;
                j--;
            }
        } while (i <= j);

        if (j < k) l = i;
        if (k < i) m = j;
    }

    return a[k];
}
