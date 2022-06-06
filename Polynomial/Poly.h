//
// Created by kil4g on 11.03.2022.
//
#include <map>
#include <iostream>

class Poly {
private:
    std::map<uint64_t, long long> coef_;
public:
    Poly() = default;
    explicit Poly(std::map<uint64_t, long long> coef)
            : coef_(std::move(coef))
    {
    }
    Poly& operator=(const Poly& other) = default;

    bool operator==(const Poly& other) {
        return coef_ == other.coef_;
    }

    bool operator!=(const Poly& other) {
        return coef_ != other.coef_;
    }

    void operator/=(long long divisitor) {
        for (const auto& [key, val] : coef_) {
            coef_[key] /= divisitor;
        }
    }
    Poly operator/(long long val) const {
        Poly div(*this);
        div /= val;
        return div;
    }
    void operator*=(long long multiplier) {
        if (multiplier == 0) {
            coef_ = {{0, 0}};
        }
        for (const auto& [key, val] : coef_) {
            coef_[key] *= multiplier;
        }
    }
    Poly operator*(long long val) const {
        Poly multi(*this);
        multi *= val;
        return multi;
    }
    void operator*=(const Poly& other) {
        std::map<unsigned int, long long> new_coef;
        for (const auto& [key1, val1] : coef_) {
            for (const auto& [key2, val2] : other.coef_) {
                if (new_coef.count(key1+key2) == 1) {
                    new_coef[key1 + key2] += val1 * val2;
                } else {
                    new_coef[key1 + key2] = val1 * val2;
                }
            }
        }
        for (const auto& [key, val] : new_coef) {
            if (val == 0) {
                new_coef.erase(key);
            }
        }

        for (const auto& [ckey, cval] : new_coef) {
            coef_[ckey] = cval;
        }
    }
    Poly operator*(const Poly& other) const {
        Poly multi(*this);
        multi *= other;
        return multi;
    }
    long long &operator[](unsigned int index) {
        if (coef_.count(index) == 0) {
            coef_[index] = 0;
        }
        return coef_.at(index);
    }

    void operator+=(const Poly& other) {
        for (const auto& [key, val] : other.coef_) {
            if (coef_.count(key) == 1) {
                long long new_val = coef_[key] + val;
                if (new_val == 0) {
                    coef_.erase(key);
                } else {
                    coef_[key] = new_val;
                }
            } else {
                coef_[key] = val;
            }
        }
    }
    Poly operator+(const Poly& other) const {
        Poly sum(*this);
        sum += other;
        return sum;
    }
    void operator-=(const Poly& other) {
        for (const auto& [key, val] : other.coef_) {
            if (coef_.count(key) == 1) {
                long long new_val = coef_[key] - val;
                if (new_val == 0) {
                    coef_.erase(key);
                } else {
                    coef_[key] = new_val;
                }
            } else {
                coef_[key] = -val;
            }
        }
    }
    Poly operator-(const Poly& other) const {
        Poly sub(*this);
        sub -= other;
        return sub;
    }
    friend std::istream& operator>>(std::istream& is, Poly& poly) {
        std::map<unsigned int, long long> coef;
        int n;
        unsigned int key;
        long long val;
        is >> n;
        for (; n > 0; n--) {
            is >> key;
            is >> val;
            if (coef.count(key) > 0) {
                throw std::invalid_argument("Multiple coefs with the same power");
            }
            if (val != 0) {
                coef[key] = val;
            }
        }

        for (const auto& [ckey, cval] : coef) {
            poly.coef_[ckey] = cval;
        }
        return is;
    }
    friend std::ostream& operator<<(std::ostream& os, const Poly& poly) {
        auto it = poly.coef_.begin();
        auto end = poly.coef_.end();
        if (it != end) {
            unsigned key = it->first;
            long long val = it->second;
            if (val != 1 || key == 0) {
                os << val;
            }
            if (key > 0) {
                os << 'x';
                if (key > 1) {
                    os << '^' << key;
                }
            }
            for (it++; it != end; it++) {
                key = it->first;
                val = it->second;
                if (val > 0) {
                    os << '+';
                }
                if (val != 1) {
                    os << val;
                }
                os << 'x' << '^' << key;
            }
        } else {
            os << 0;
        }
        return os;
    }
};