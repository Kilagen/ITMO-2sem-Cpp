//
// Created by kil4gen on 15.04.2022.
//

#include <string>
#include <iostream>
#include "Stat.h"
#include "CurrencyIO.h"


int main(int argc, char** argv) {
    const std::string CURRENCY[] = {"AMD", "AUD", "AZN", "BGN", "BRL", "BYN",
                                    "CAD","CHF", "CNY", "CZK", "DKK", "EUR",
                                    "GBP","HKD", "HUF", "INR", "JPY", "KGS",
                                    "KRW","KZT", "MDL", "NOK", "PLN", "RON",
                                    "SEK","SGD", "TJS", "TMT", "TRY", "UAH",
                                    "USD","UZS", "XDR", "ZAR"};
    if (argc < 3 || argc > 5) {
        throw std::invalid_argument("Invalid argument count");
    }
    long long period_start = strtoll(argv[1], nullptr, 10);
    long long period_end = strtoll(argv[2], nullptr, 10);

    if (argc == 4 && std::string(argv[3])=="TST") {
        Stat values = CurrencyIO::Read("TST", period_start, period_end);
        std::cout << "Test" << std::endl;
        std::cout << "mean: " << values.mean() << std::endl;
        std::cout << "median: " << values.median() << std::endl;
        return 0;
    }

    for (const auto& cur : CURRENCY) {
        Stat values = CurrencyIO::Read(cur, period_start, period_end);

        std::cout << cur << std::endl;
        std::cout << "mean: " << values.mean() << std::endl;
        std::cout << "median: " << values.median() << std::endl;
    }
}