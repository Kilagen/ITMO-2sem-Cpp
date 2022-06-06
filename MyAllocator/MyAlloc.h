//
// Created by kil4g on 25.05.2022.
//

#include <iostream>
#include <fstream>
#include <exception>
#include <memory>
#include "MyMemoryManager.h"

#ifndef MYALLOCATOR_MYALLOC_H
#define MYALLOCATOR_MYALLOC_H

template<typename T, size_t size, size_t count>
class MyAllocator {
public:
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;
    typedef T* pointer;
    typedef const T* const_pointer;
    typedef T value_type;

    MyMemoryManager* mmm;

    template <typename U>
    struct rebind {
        typedef MyAllocator<U, size * sizeof(value_type) / sizeof(U), count> other;
    };

    explicit MyAllocator():
        mmm(new MyMemoryManager(count, (1+size)*(sizeof(value_type)))) {
        //std::cout << "Constructor of value size " << sizeof(value_type) << std::endl;
    }


    template<typename U>
    explicit MyAllocator(const MyAllocator<U, size * sizeof(value_type) / sizeof(U), count>& alloc) noexcept:
            mmm(alloc.mmm)
    {
        //std::cout << "Copy constructor from " << sizeof(U) << " to " << sizeof(value_type) << std::endl;
        (mmm->allocCount)++;
    }

    bool operator==(const MyAllocator &alloc) const noexcept {
        return mmm == alloc.mmm;
    }
    bool operator!=(const MyAllocator &alloc) const noexcept {
        return mmm != alloc.mmm;
    }

    pointer allocate(size_type n) {
        if (n * sizeof(value_type) > mmm->blockSize) {
            std::cout << n << " * " << sizeof(value_type) << " is more than size of chunk " << mmm->blockSize << std::endl;
            using namespace std::string_literals;
            throw std::invalid_argument(std::to_string(n) +
                " more than size of chunk " +
                std::to_string(mmm->blockSize / sizeof(value_type)));
        }
        if (mmm->hasBlock()) {
            return reinterpret_cast<pointer>(mmm->getBlock());
        } else {
            throw std::logic_error("No blocks left");
        }
    }

    void deallocate(pointer p, size_type) {
        if (p == nullptr)
            return;
        mmm->freeBlock(reinterpret_cast<char *>(p));
    }

    ~MyAllocator() {
        //std::cout << "Destructor of " << sizeof(value_type) << std::endl;
        if (mmm->allocCount > 1) {
            (mmm->allocCount)--;
            //std::cout << "Allocators left " << mmm->allocCount << std::endl;
        } else {
            //std::cout << "Last allocator. Free memory" << std::endl;
            (*mmm).~MyMemoryManager();
        }
    }

};
#endif //MYALLOCATOR_MYALLOC_H
