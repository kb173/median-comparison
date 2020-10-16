#pragma once

// http://ndevilla.free.fr/median/median/index.html

size_t getWirthKthSmallest(std::vector<size_t> a, size_t k)
{
    size_t l = 0;
    size_t m = a.size() - 1;

    while (l < m) {
        size_t x = a[k];
        size_t i = l;
        size_t j = m;

        do {
            while (a[i] < x) i++;
            while (x < a[j]) j--;

            if (i <= j) {
                std::swap(a[i], a[j]);
                i++;
                j--;
            }
        } while (i <= j);

        if (j < k) l = i;
        if (k < i) m = j;
    }

    return a[k];
}
