//
// Created by kil4gen on 16.04.2022.
//

#include "Stat.h"

void Stat::append(double val) {
    v.push_back(val);
    sum += val;
    size++;
}

double Stat::median() {
    if (isEmpty()) {
        return -1;
    }
    if (size % 2 == 0) {
        return (kthStat(0, size, size/2) + kthStat(0, size, size/2+1))/2;
    }
    return kthStat(0, size, (size+1)/2);

}

double Stat::mean() const {
    if (isEmpty()) {
        return -1;
    }
    return sum / (float)size;
}

double Stat::kthStat(std::size_t l, std::size_t r, std::size_t k) {
    std::size_t i = l;
    std::size_t j = r;
    double pivot = v[(l + r)/2];
    while (i <= j) {
        while (v[i] < pivot) i++;
        while (v[j] > pivot) j--;
        if (i <= j) std::swap(v[i++], v[j--]);
    }
    if (l <= k && k <= j) return kthStat(l, j, k);
    if (i <= k && k <= r) return kthStat(i, r, k);
    return v[k];
}

bool Stat::isEmpty() const {
    return size==0;
}
