//
// Created by kil4gen on 15.04.2022.
//

#ifndef LAB_2_CURRENCYIO_H
#define LAB_2_CURRENCYIO_H


#include "Stat.h"

class CurrencyIO {
public:
    static bool Write(const std::string& currency, double value, int time);
    static Stat Read(const std::string& currency, long long start, long long end);
};


#endif //LAB_2_CURRENCYIO_H
