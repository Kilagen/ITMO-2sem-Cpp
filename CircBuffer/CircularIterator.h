//
// Created by kil4g on 25.04.2022.
//
#include <iterator>
#include <iostream>

#ifndef LAB3_CIRCULARITERATOR_H
#define LAB3_CIRCULARITERATOR_H

template<typename T>
class circularIterator {
public:
    typedef std::random_access_iterator_tag iterator_category;
    typedef T value_type;
    typedef typename std::allocator_traits<std::allocator <T>>::difference_type difference_type;
    typedef T& reference;
    typedef T* pointer;
    T* p_;
    T* begin_;
    T* end_;
    T* first_;
    T* last_;
    circularIterator() = default;
    circularIterator(T* p, T* begin, T* end, T* first, T* last):
    p_(p),
    begin_(begin),
    end_(end),
    first_(first),
    last_(last)
    {}

    circularIterator& operator=(const circularIterator &ci) = default;

    bool operator==(const circularIterator &ci) const {
        return p_ == ci.p_;
    }
    bool operator!=(const circularIterator &ci) const {
        return p_ != ci.p_;
    }
    T& operator*() {
        return *p_;
    }
    T* operator->() {
        return p_;
    }
    circularIterator& operator++() {
        if (p_ != end_) {
            p_++;
        } else {
            p_ = begin_;
        }
        return *this;
    }
    circularIterator operator++(int) {
        circularIterator retCI = *this;
        operator++();
        return retCI;
    }

    circularIterator& operator--() {
        if (p_ == begin_)
            p_ = end_;
        else
            p_--;
        return *this;
    }
    circularIterator operator--(int) {
        circularIterator retCI = *this;
        operator--();
        return retCI;
    }

    circularIterator& operator+= (int n) {
        if (n >= 0) {
            if (p_ + n > end_) {
                n = n + (begin_ - end_) - 1;
            }
        } else {
            if (p_ + n < begin_) {
                n = n + (end_ - begin_) + 1;
            }
        }
        p_ += n;
        return *this;
    }

    circularIterator operator+ (int n) const {
        circularIterator retCI = *this;
        retCI += n;
        return retCI;
    }

    circularIterator operator- (int n) const {
        return (*this) + (-n);

    }
    circularIterator& operator-= (int n) {
        *this += -n;
        return *this;
    }

    int operator- (const circularIterator& it) const {
        if (p_ > it.p_)
            return p_ - it.p_;
        return (p_ - begin_) + (end_ - it.p_);
    }

    T& operator[] (size_t n) {
        return *((*this) + n);
    }

    bool operator> (const circularIterator &it) const {
        if ((last_ - p_ > 0 && last_ - it.p_ > 0) || (last_ - p_ < 0 && last_ - it.p_ < 0)) {
            return p_ > it.p_;
        }
        return p_ < it.p_;
    }
    bool operator< (const circularIterator &it) const {
        return it > *this;
    }
    bool operator>= (const circularIterator &it) const {
        return !(*this < it);
    }
    bool operator<= (const circularIterator &it) const {
        return !(*this > it);
    }

    ~circularIterator() = default;
};

#endif //LAB3_CIRCULARITERATOR_H
