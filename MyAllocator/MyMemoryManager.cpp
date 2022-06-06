//
// Created by kil4g on 04.06.2022.
//

#include "MyAlloc.h"

MyMemoryManager::MyMemoryManager(size_t count, size_t size):
        allocCount(1),
        occupiedCount(0),
        totalCount(count),
        blockSize(size),
        freeBlocks(new char*[count]),
        buffer(static_cast<char*>(malloc(count * size))) {
    for (size_t i = 0; i < count; i++) {
        *(freeBlocks + i) = buffer + i * size;
    }
}

char* MyMemoryManager::getBlock() {
    return *(freeBlocks + (occupiedCount++));
}

[[nodiscard]] bool MyMemoryManager::hasBlock() const {
    return occupiedCount < totalCount;
}

void MyMemoryManager::freeBlock(char* p) {
    if (occupiedCount == 0) {
        throw std::logic_error("All blocks are free");
    }
    occupiedCount--;
    *(freeBlocks + occupiedCount) = p;
}

MyMemoryManager::~MyMemoryManager() {
    free(buffer);
    delete[] freeBlocks;
}
