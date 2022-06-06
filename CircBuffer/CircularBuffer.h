//
// Created by kil4g on 26.04.2022.
//

#include "CircularIterator.h"

#ifndef LAB3_CIRCULARBUFFER_H
#define LAB3_CIRCULARBUFFER_H

template<typename T>
class CircularBuffer {
private:
    T* buffer_;
    T* first_;
    T* last_;
    size_t size_;
public:
    explicit CircularBuffer(size_t size=0):
    size_(size),
    buffer_(nullptr),
    first_(nullptr),
    last_(nullptr)
    {
        if (size_ > 0) {
            first_ = last_ = buffer_ = new T[size_ + 1];
        }
    }

    CircularBuffer(const CircularBuffer &other):
    size_(other.size_)
    {
        if (size_ == 0) {
            delete [] buffer_;
            first_ = last_ = buffer_ = nullptr;
            return ;
        }
        buffer_ = new T[size_ + 1];
        for (size_t i = 0; i < size_; i++) {
            buffer_[i] = other.buffer_[i];
        }
        first_ = other.first_ + (buffer_ - other.buffer_);
        last_ = other.last_ + (buffer_ - other.buffer_);
    }

    ~CircularBuffer() {
        delete [] buffer_;
        std::cout << "Buffer destroyed" << std::endl;
    }

    CircularBuffer& operator=(const CircularBuffer &other) {
        if (&other == this) {
            return *this;
        }
        delete[] buffer_;
        size_ = other.size_;
        if (size_ == 0) {
            buffer_ = first_ = last_ = nullptr;
            return *this;
        }
        buffer_ = new T[size_ + 1];
        for (size_t i = 0; i < size_; i++) {
            buffer_[i] = other.buffer_[i];
        }
        first_ = other.first_ + (buffer_ - other.buffer_);
        last_ = other.last_ + (buffer_ - other.buffer_);
        return *this;
    }

    void resize(size_t size) {
        if (size == 0) {
            delete[] buffer_;
            first_ = last_ = buffer_ = nullptr;
            size_ = size;
            return;
        }
        T* new_buffer = new T[size + 1];
        size_t i = 0;
        for (auto t = this->begin(); t != this->end(); t++) {
            new_buffer[i] = *t;
            ++i;
            if (i >= size) {
                break;
            }
        }
        delete[] buffer_;
        last_ = new_buffer + i;
        first_ = buffer_ = new_buffer;
        size_ = size;
    }

    void pop_front() {
        if (first_ == last_) {
            return;
        }
        (*first_).~T();
        if (first_ - buffer_ == size_)
            first_ = buffer_;
        else
            first_++;
    }

    void pop_back() {
        if (first_ == last_) {
            return;
        }
        (*last_).~T();
        if (last_ == buffer_) {
            last_ = buffer_  + size_;
        } else {
            last_--;
        }
    }

    void push_back(T val) {
        *last_ = val;
        if (last_ - buffer_ == size_) {
            last_ = buffer_;
        } else {
            last_++;
        }
        if (first_ == last_) {
            if (first_ - buffer_ == size_)
                first_ = buffer_;
            else
                first_++;
        }
    }

    void push_front(T val) {
        if (first_ == buffer_) {
            first_ = buffer_ + size_;
        } else {
            first_--;
        }
        *first_ = val;
        if (first_ == last_) {
            if (last_ == buffer_) {
                last_ = buffer_  + size_;
            } else {
                last_--;
            }
        }
    }

    const T& operator[](size_t i) const {
        if (first_ + i > buffer_ + size_) {
            return *(first_ + i - size_);
        }
        return *(first_ + i);
    }

    T& front() {
        if (size_ == 0) {
            throw std::logic_error("zero size");
        }
        return *first_;
    }
    T& back() {
        if (size_ == 0) {
            throw std::logic_error("zero size");
        }
        if (last_ == buffer_) {
            return *(buffer_ + size_);
        }
        return *(last_ - 1);
    }

    T& operator[](size_t i) {
        if (first_ + i > buffer_ + size_) {
            return *(first_ + i - size_ - 1);
        }
        return *(first_ + i);
    }

    circularIterator<T> begin() {
        return circularIterator<T>(first_, buffer_, buffer_ + size_, first_, last_);
    }

    circularIterator<T> end() {
        return circularIterator<T>(last_, buffer_, buffer_ + size_, first_, last_);
    }
};

#endif //LAB3_CIRCULARBUFFER_H
