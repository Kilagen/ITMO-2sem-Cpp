//
// Created by kil4g on 04.06.2022.
//

#ifndef MYALLOCATOR_MYMEMORYMANAGER_H
#define MYALLOCATOR_MYMEMORYMANAGER_H
struct MyMemoryManager {
public:
    size_t allocCount;
    size_t occupiedCount;
    size_t totalCount;
    size_t blockSize;
    char* buffer;
    char** freeBlocks;

    MyMemoryManager(size_t count, size_t size);

    char* getBlock();
    [[nodiscard]] bool hasBlock() const;
    void freeBlock(char* p);
    ~MyMemoryManager();
};
#endif //MYALLOCATOR_MYMEMORYMANAGER_H
