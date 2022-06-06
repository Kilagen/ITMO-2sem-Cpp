//
// Created by kil4g on 30.04.2022.
//

#include <iostream>
#include "CRational.h"

CRational::CRational():
nom_(0),
denom_(1)
{}

CRational::CRational(int32_t nom, int32_t denom):
nom_(nom),
denom_(denom)
{
    if (denom_ == 0) {
        throw std::logic_error("Zero denominator");
    }
    if (denom_ < 0) {
        denom_ = -denom_;
        nom_ = -nom_;
    }
}

bool CRational::operator< (const CRational &r) const{
    return nom_ * r.denom_ < r.nom_ * denom_;
}

bool CRational::operator== (const CRational &r) const {
    return nom_ * r.denom_ == r.nom_ * denom_;
}

bool CRational::operator<= (const CRational &r) const {
    return nom_ * r.denom_ <= r.nom_ * denom_;
}

bool CRational::operator> (const CRational &r) const {
    return r < *this;
}

bool CRational::operator>= (const CRational &r) const {
    return r <= *this;
}

std::ostream& operator<< (std::ostream &out, const CRational &r) {
    return out << r.nom_ << '/' << r.denom_;
}

CRational::~CRational() {
    std::cout << "CRat destroyed" << std::endl;
}
