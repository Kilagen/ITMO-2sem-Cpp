//
// Created by kil4gen on 15.04.2022.
//

#include <fstream>
#include <iostream>
#include <string>
#include "CurrencyIO.h"


bool CurrencyIO::Write(const std::string& currency, double value, int time) {
    std::ofstream fout;
    fout.open("Log/"+currency+".txt", std::fstream::app);
    if (!fout.is_open()) {
        std::cout << "Cringe happened" << currency << std::endl;
        fout.close();
        return false;
    } else {
        fout << value << ' ' << time << '\n';
        fout.close();
        return true;
    }
}

Stat CurrencyIO::Read(const std::string& currency, long long start, long long end) {
    std::ifstream fin;
    Stat st;
    fin.open("Log/"+currency+".txt");
    if (!fin.is_open()) {
        std::cout << "Cringe " << currency << std::endl;
        fin.close();
        return {};
    }
    long long time = 0;
    double value = 0;
    while (true) {
        fin >> value >> time;
        if (fin.eof() || time > end) {
            break;
        }
        if (start <= time) {
            st.append(value);
        }
    }
    return st;
}
