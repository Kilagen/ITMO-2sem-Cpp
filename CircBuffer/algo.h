//
// Created by kil4g on 28.04.2022.
//

#ifndef LAB3_ALGO_H
#define LAB3_ALGO_H
namespace algo {
    template<typename Iterator, typename Predicate>
    bool all_of(Iterator begin, Iterator end, Predicate f) {
        while (begin != end) {
            if (!f(*begin)) {
                return false;
            }
            ++begin;
        }
        return true;
    }

    template<typename Iterator, typename Predicate>
    bool any_of(Iterator begin, Iterator end, Predicate f) {
        while (begin != end) {
            if (f(*begin)) {
                return true;
            }
            ++begin;
        }
        return false;
    }

    template<typename Iterator, typename Predicate>
    bool none_of(Iterator begin, Iterator end, Predicate f) {
        while (begin != end) {
            if (f(*begin)) {
                return false;
            }
            ++begin;
        }
        return true;
    }

    template<typename Iterator, typename Predicate>
    bool one_of(Iterator begin, Iterator end, Predicate f) {
        while (begin != end) {
            if (f(*begin)) {
                return none_of(++begin, end, f);
            }
            ++begin;
        }
        return false;
    }

    template<typename Iterator>
    bool is_sorted(Iterator begin, Iterator end) {
        Iterator tmp = begin;
        tmp++;
        while (tmp != end) {
            if (*tmp < *begin) {
                return false;
            }
            tmp++;
            begin++;
        }
        return true;
    }

    template<typename Iterator, typename Comp>
    bool is_sorted(Iterator begin, Iterator end, Comp f) {
        while (begin + 1 != end) {
            if (!Comp(*(begin++), *begin)) {
                return false;
            }
        }
        return true;
    }

    template<typename Iterator, typename Predicate>
    bool is_partitioned(Iterator begin, Iterator end, Predicate f) {
        while (begin != end) {
            if (f(*begin)) {
                return all_of(++begin, end, f);
            }
            ++begin;
        }
        return false;
    }

    template<typename Iterator, typename T>
    Iterator find_not(Iterator begin, Iterator end, T val) {
        while (begin != end) {
            if ((*begin) != val) {
                return begin;
            }
            ++begin;
        }
        return end;
    }

    template<typename Iterator, typename T>
    Iterator find_backward(Iterator begin, Iterator end, T val) {
        while (begin < end) {
            --end;
            if ((*end) == val) {
                return end;
            }
        }
        return begin;
    }

    template<typename Iterator>
    bool is_palindrome(Iterator begin, Iterator end) {
        --end;
        while (end - begin > 1) {
            if (*begin != *end) {
                return false;
            }
            --end;
            ++begin;
        }
        return true;
    }

    template<typename Iterator, typename Func>
    bool is_palindrome(Iterator begin, Iterator end, Func f) {
        --end;
        while (end - begin > 1) {
            if (f(*begin) != f(*end)) {
                return false;
            }
            --end;
            ++begin;
        }
        return true;
    }
}
#endif //LAB3_ALGO_H
