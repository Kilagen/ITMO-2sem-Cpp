//
// Created by kil4g on 07.05.2022.
//

#ifndef LAB6_POLY_H
#define LAB6_POLY_H

template <long long x, unsigned int p>
struct mon {
    static const long long val = mon<x, p/2>::val * mon<x, (p + 1)/2>::val;
};

template<long long x>
struct mon<x, 0> {
    static const long long val = 1;
};

template<long long x>
struct mon<x, 1> {
    static const long long val = x;
};

template <int...>
struct pol {
};

template<int x, int coef, int pow>
struct pol<x, coef, pow> {
    static const long long val = coef * mon<x, pow>::val;
};

template <int x, int coef, int pow, int ... other>
struct pol<x, coef, pow, other...> {
    static const long long val = coef * mon<x, pow>::val + pol<x, other...>::val;
};

template <int ... other>
std::ostream &operator<< (std::ostream& out, pol<other...> p) {
    return out << p.val;
}
#endif //LAB6_POLY_H