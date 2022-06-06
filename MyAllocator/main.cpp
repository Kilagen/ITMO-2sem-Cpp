#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <unordered_map>
#include "MyAlloc.h"


bool testUMap() {
    int rounds = 1000;
    int start_time = clock();
    std::unordered_map<const int, const int, std::hash<int>, std::equal_to<>, MyAllocator<std::pair<const int, const int>, 4000, 4000>> m;
    for (int j = 1; j <= rounds; j++) {
        for (int i = 0; i < 2000; ++i) {
            m.insert({i, i + i * i});
        }

        for (int i = 0; i < 2000; ++i) {
            m.erase(i);
        }
    }
    std::cout << "MyAllocator - " << clock() - start_time << std::endl;

    start_time = clock();
    std::unordered_map<const int, const int, std::hash<int>, std::equal_to<>> m1;
    for (int j = 1; j <= rounds; j++) {
        for (int i = 0; i < 2000; ++i) {
            m1.insert({i, i + i * i});
        }

        for (int i = 0; i < 2000; ++i) {
            m1.erase(i);
        }
    }
    std::cout << "std::allocator - " << clock() - start_time << std::endl;
    return true;
}

bool testList() {
    int n = 100000;
    int rounds = 500;

    int start_time = clock();
    std::list<int, MyAllocator<int, 1, 100000>> list2;

    for (int j = 1; j <= rounds; ++j) {
        // std::cout << j << ' ';
        for (int i = 0; i < n; ++i)
            list2.push_back(i);
        for (int i = 0; i < n; ++i)
            list2.pop_back();
    }
    std::cout << "MyAllocator - " << clock() - start_time << std::endl;

    start_time = clock();
    std::list<int> list1;

    for (int j = 1; j <= rounds; ++j) {
        // std::cout << j << ' ';
        for (int i = 0; i < n; ++i)
            list1.push_back(i);
        for (int i = 0; i < n; ++i)
            list1.pop_back();
    }
    std::cout << "std::allocator - " << clock() - start_time << std::endl;
    return true;
}

bool testVector() {
    int n = 100000;
    int rounds = 2000;

    int start_time = clock();
    std::vector<int, MyAllocator<int, 150000, 20>> list2;

    for (int j = 1; j <= rounds; ++j) {
        // std::cout << j << ' ';
        for (int i = 0; i < n; ++i)
            list2.push_back(i);
        for (int i = 0; i < n; ++i)
            list2.pop_back();
    }
    std::cout << "MyAllocator - " << clock() - start_time << std::endl;

    start_time = clock();
    std::vector<int> list1;

    for (int j = 1; j <= rounds; ++j) {
        // std::cout << j << ' ';
        for (int i = 0; i < n; ++i)
            list1.push_back(i);
        for (int i = 0; i < n; ++i)
            list1.pop_back();
    }
    std::cout << "std::allocator - " << clock() - start_time << std::endl;
    return true;
}

bool testDeque() {
    int n = 100000;
    int rounds = 2000;

    int start_time = clock();
    std::deque<int, MyAllocator<int, 2600, 1000>> list2;

    for (int j = 1; j <= rounds; ++j) {
        // std::cout << j << ' ';
        for (int i = 0; i < n; ++i)
            list2.push_back(i);
        for (int i = 0; i < n; ++i)
            list2.pop_back();
    }
    std::cout << "MyAllocator - " << clock() - start_time << std::endl;

    start_time = clock();
    std::deque<int> list1;

    for (int j = 1; j <= rounds; ++j) {
        // std::cout << j << ' ';
        for (int i = 0; i < n; ++i)
            list1.push_back(i);
        for (int i = 0; i < n; ++i)
            list1.pop_back();
    }
    std::cout << "std::allocator - " << clock() - start_time << std::endl;
    return true;

}

int main () {
    std::cout << "-------------------------------" << std::endl;
    std::cout << "Testing Deque" << std::endl;
    testDeque();
    std::cout << "-------------------------------" << std::endl;
    std::cout << "Testing Unordered Map" << std::endl;
    testUMap();
    std::cout << "-------------------------------" << std::endl;
    std::cout << "Testing List" << std::endl;
    testList();
    std::cout << "-------------------------------" << std::endl;
    std::cout << "Testing Vector" << std::endl;
    testVector();

    std::cout << "\nOK\n";
    return 0;
}
