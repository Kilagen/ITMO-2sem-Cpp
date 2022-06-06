#include <iostream>
#include <algorithm>
#include "CircularBuffer.h"
#include "algo.h"
#include "CRational.h"

bool less_of_f(char c) {
    return c < 'f';
}
void testCRational() {
    CircularBuffer<CRational> crat(15);
    for (int i = 0; i < 10; i++) {
        crat.push_back(CRational(i, i+1));
        for (const auto& c: crat) {
            std::cout << c << ' ';
        }
        std::cout << std::endl;
    }
    for (int i = 0; i < 10; i++) {
        crat.push_back(CRational(i, 2*i+1));
        for (const auto& c: crat) {
            std::cout << c << ' ';
        }
        std::cout << std::endl;
    }
    std::cout << "Sorted:" << algo::is_sorted(crat.begin(), crat.end()) << std::endl;
    std::sort(crat.begin(), crat.end());
    for (const auto& c: crat) {
        std::cout << c << ' ';
    }
    std::cout << std::endl;
    std::cout << "Sorted:" << algo::is_sorted(crat.begin(), crat.end()) << std::endl;
    std::cout << "Reverse" << std::endl;
    std::reverse(crat.begin(), crat.end());
    for (const auto& c: crat) {
        std::cout << c << ' ';
    }
    std::cout << std::endl;
}

void testChar() {
    CircularBuffer<char> crat(15);
    for (char i = 70; i < 80; i++) {
        crat.push_front(i);
        for (auto c: crat) {
            std::cout << c << ' ';
        }
        std::cout << std::endl;
    }
    for (char i = 97; i < 105; i++) {
        crat.push_back(i);
        for (auto c: crat) {
            std::cout << c << ' ';
        }
        std::cout << std::endl;
    }
    std::cout << "Sorted:" << algo::is_sorted(crat.begin(), crat.end()) << std::endl;
    std::sort(crat.begin(), crat.end());
    for (auto c: crat) {
        std::cout << c << ' ';
    }
    std::cout << std::endl;
    std::cout << "Sorted:" << algo::is_sorted(crat.begin(), crat.end()) << std::endl;
    std::cout << "Reverse" << std::endl;
    std::reverse(crat.begin(), crat.end());
    for (auto c: crat) {
        std::cout << c << ' ';
    }
    std::cout << std::endl;
    std::cout << "Push_front h 5 times" << std::endl;
    for (int i = 0; i < 5; i++) {
        crat.push_front('h');
    }
    for (auto c: crat) {
        std::cout << c << ' ';
    }
    std::cout << std::endl;
    std::cout << "Find not h: " << *algo::find_not(crat.begin(), crat.end(), 'h') << std::endl;
    std::cout << "Partioned by less of f: " << algo::is_partitioned(crat.begin(), crat.end(), less_of_f) << std::endl;

}

void memTest() {
    for (int i = 0; i < 1000000; i++) {
        CircularBuffer<char> crat(15000);
    }
}



int main() {
    std::cout << "Test CRational" << std::endl;
    testCRational();
    std::cout << "Test Char" << std::endl;
    testChar();
    //std::cout << "Memory Test" << std::endl;
    //memTest();

    return 0;
}
