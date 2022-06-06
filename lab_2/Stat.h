//
// Created by kil4g on 16.04.2022.
//

#ifndef LAB_2_STAT_H
#define LAB_2_STAT_H


#include <vector>

class Stat
{
private:
    std::vector<double> v;
    double sum = 0;
    std::size_t size = 0;
    double kthStat(std::size_t l, std::size_t r, std::size_t k);
public:
    void append(double val);
    [[nodiscard]] bool isEmpty() const;
    [[nodiscard]] double median();
    [[nodiscard]] double mean() const;
};


#endif //LAB_2_STAT_H
