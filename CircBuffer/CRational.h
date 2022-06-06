//
// Created by kil4g on 30.04.2022.
//

#ifndef LAB3_CRATIONAL_H
#define LAB3_CRATIONAL_H


#include <fstream>

class CRational {
private:
    int32_t nom_;
    uint32_t denom_;
public:
    CRational();
    explicit CRational(int32_t , int32_t);
    CRational(const CRational&) = default;

    bool operator== (const CRational&) const;
    bool operator< (const CRational&) const;
    bool operator<= (const CRational&) const;
    bool operator> (const CRational&) const;
    bool operator>= (const CRational&) const;

    friend std::ostream& operator<< (std::ostream&, const CRational&);

    ~CRational();
};


#endif //LAB3_CRATIONAL_H
