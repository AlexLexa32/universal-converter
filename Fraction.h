#pragma GCC optimize("Ofast,unroll-loops,mfma,mavx,mavx2")
#pragma GCC target("avx,avx2,fma")
#pragma GCC optimize("03")
#pragma once
#include <exception>
#include <iostream>
#include <numeric>
#include <algorithm>
#include "MegaInt.h"

MegaInt gcd(MegaInt first_number, MegaInt& second_number) {
    if (first_number == 0) return second_number;
    return gcd(second_number%first_number, first_number);
}

class Fraction {
public:
    Fraction reducing(Fraction& f) {
        MegaInt gd = gcd(f.num_, f.den_);
        f.num_ = f.num_/gd;
        f.den_ = f.den_/gd;
        if (!f.den_.positive) {
            f.num_.positive ^= true;
            f.den_.positive ^= true;
        }
        return f;
    }
    Fraction() {
        num_ = 0;
        den_ = 1;
    };
    Fraction(MegaInt& num, MegaInt den) {
        if (den == 0) {
            throw std::overflow_error("Divide by zero exception");
        }
        num_ = num, den_ = den;
        reducing(*this);
    }
    explicit Fraction(const MegaInt& num): num_(num), den_(1) {}

    Fraction(const Fraction& other) {
        num_ = other.num_;
        den_ = other.den_;
    };
    ~Fraction() = default;
    MegaInt num() const {
        return num_;
    }
    MegaInt den() const {
        return den_;
    }
    Fraction& operator=(Fraction other) {
        num_ = other.num_;
        den_ = other.den_;
        return *this;
    }
    Fraction operator-() {
        Fraction tmpp = *this;
        tmpp.num_ *= -1;
        return tmpp;
    }
    Fraction operator+() {
        return reducing(*this);
    }
    Fraction operator++() {
        num_ += den_;
        return reducing(*this);
    }
    Fraction operator++(int) {
        Fraction tmpp = *this;
        num_ += den_;
        reducing(*this);
        return tmpp;
    }
    Fraction operator--() {
        num_ -= den_;
        return reducing(*this);
    }
    Fraction operator--(int) {
        Fraction tmpp = *this;
        num_ -= den_;
        reducing(*this);
        return tmpp;
    }
    Fraction operator+(Fraction other) {
        MegaInt tmpp = num_ * other.den_;
        other.num_ *= den_;
        other.den_ *= den_;
        other.num_ += tmpp;
        reducing(other);
        return other;
    }
    Fraction operator+(MegaInt nn) {
        Fraction tmpp = *this;
        nn *= tmpp.den_;
        tmpp.num_ += nn;
        return reducing(tmpp);
    }
    Fraction operator+=(Fraction other) {
        *this = *this + other;
        return *this;
    }
    Fraction operator+=(MegaInt nn) {
        *this = *this + nn;
        return *this;
    }
    Fraction operator-(Fraction other) {
        Fraction tmpp;
        tmpp.den_ = other.den_ * den_;
        tmpp.num_ = num_ * other.den_ - other.num_ * den_;
        return reducing(tmpp);
    }
    Fraction operator-(MegaInt nn) {
        Fraction tmp = *this;
        nn *= tmp.den_;
        tmp.num_ -= nn;
        return reducing(tmp);
    }
    Fraction operator-=(Fraction other) {
        *this = *this - other;
        return *this;
    }
    Fraction operator-=(MegaInt nn) {
        *this = *this - nn;
        return *this;
    }
    Fraction operator*(Fraction other) {
        other.num_ *= num_;
        other.den_ *= den_;
        return reducing(other);
    }
    Fraction operator*(MegaInt nn) {
        Fraction tmpp = *this;
        tmpp.num_ *= nn;
        return reducing(tmpp);
    }
    Fraction operator*=(Fraction other) {
        *this = *this * other;
        return *this;
    }
    Fraction operator*=(const MegaInt& nn) {
        *this = *this * nn;
        return *this;
    }
    Fraction operator/(Fraction other) {
        std::swap(other.num_, other.den_);
        other.num_ *= num_;
        other.den_ *= den_;
        return reducing(other);
    }
    Fraction operator/(MegaInt nn) {
        Fraction tmpp = *this;
        tmpp.den_ *= nn;
        return reducing(tmpp);
    }
    Fraction operator/=(Fraction other) {
        *this = *this / other;
        return *this;
    }
    Fraction operator/=(MegaInt nn) {
        *this = *this / nn;
        return *this;
    }
    bool operator<(Fraction other) {
        return num_*other.den_ < den_*other.num_;
    }
    bool operator>=(Fraction other) {
        return !(*this < other);
    }
    bool operator<=(Fraction other) {
        return *this < other || *this == other;
    }
    bool operator>(Fraction other) {
        return *this >= other && *this != other;
    }
    bool operator==(Fraction other) {
        return num_ == other.num_ && den_ == other.den_;
    }
    bool operator!=(Fraction other) {
        return !(*this == other);
    }
    bool operator<(MegaInt nn) {
        return num_ < den_ * nn;
    }
    bool operator>=(MegaInt nn) {
        return !(*this < nn);
    }
    bool operator<=(MegaInt nn) {
        return *this < nn || *this == nn;
    }
    bool operator>(MegaInt nn) {
        return *this >= nn && *this != nn;
    }
    bool operator==(MegaInt nn) {
        return num_ == nn && den_ == 1;
    }
    bool operator!=(MegaInt nn) {
        return !(*this == nn);
    }
    friend Fraction reducing(Fraction& f);
    friend Fraction operator+(MegaInt lhs, Fraction rhs);
    friend Fraction operator-(MegaInt lhs, Fraction rhs);
    friend Fraction operator*(MegaInt lhs, Fraction rhs);
    friend Fraction operator/(MegaInt lhs, Fraction rhs);
    friend Fraction operator+=(MegaInt lhs, Fraction rhs);
    friend Fraction operator-=(MegaInt lhs, Fraction rhs);
    friend Fraction operator*=(MegaInt lhs, Fraction rhs);
    friend Fraction operator/=(MegaInt lhs, Fraction rhs);
    friend bool operator<(MegaInt lhs, Fraction rhs);
    friend bool operator>(MegaInt lhs, Fraction rhs);
    friend bool operator<=(MegaInt lhs, Fraction rhs);
    friend bool operator>=(MegaInt lhs, Fraction rhs);
    friend bool operator==(MegaInt lhs, Fraction rhs);
    friend bool operator!=(MegaInt lhs, Fraction rhs);
    friend bool operator<(const Fraction& lhs, const Fraction& rhs);

    friend std::ostream& operator<<(std::ostream& out, const Fraction& fract);

//private:
    MegaInt num_, den_;
};

Fraction reducing(Fraction& fr) {
    MegaInt gd = gcd(fr.num_, fr.den_);
    fr.num_ = fr.num_/gd;
    fr.den_ = fr.den_/gd;
//    if (!fr.den_.positive) {
//        fr.num_.positive ^= true;
//        fr.den_.positive ^= true;
//    }
    return fr;
}

bool operator<(const Fraction& lhs, const Fraction& rhs) {
    return lhs.num_*rhs.den_ < rhs.num_*lhs.den_;
}

Fraction operator+(MegaInt lhs, Fraction rhs) {
    lhs *= rhs.den_;
    rhs.num_ += lhs;
    return reducing(rhs);
}

Fraction operator-(MegaInt lhs, Fraction rhs) {
    lhs *= rhs.den_;
    rhs.num_ -= lhs;
    return -reducing(rhs);
}

Fraction operator*(MegaInt lhs, Fraction rhs) {
    rhs.num_ *= lhs;
    return reducing(rhs);
}

Fraction operator/(MegaInt lhs, Fraction rhs) {
    std::swap(rhs.num_, rhs.den_);
    rhs.num_ *= lhs;
    return rhs;
}

Fraction operator+=(MegaInt lhs, Fraction rhs) {
    rhs += lhs;
    return reducing(rhs);
}

Fraction operator-=(MegaInt lhs, Fraction rhs) {
    rhs -= lhs;
    return reducing(rhs);
}

Fraction operator*=(MegaInt lhs, Fraction rhs) {
    rhs *= lhs;
    return reducing(rhs);
}

Fraction operator/=(MegaInt lhs, Fraction rhs) {
    rhs /= lhs;
    return reducing(rhs);
}

bool operator<(MegaInt lhs, Fraction rhs) {
    return rhs > lhs;
}

bool operator>(MegaInt lhs, Fraction rhs) {
    return rhs < lhs;
}

bool operator<=(MegaInt lhs, Fraction rhs) {
    return rhs >= lhs;
}

bool operator>=(MegaInt lhs, Fraction rhs) {
    return rhs >= lhs;
}

bool operator==(MegaInt lhs, Fraction rhs) {
    return rhs == lhs;
}

bool operator!=(MegaInt lhs, Fraction rhs) {
    return rhs != lhs;
}

std::ostream& operator<<(std::ostream& out, const Fraction& fract) {
    out << fract.num_ << '/' << fract.den_;
    return out;
}
