#ifndef SSCH_PRAK_MEGAINT_H
#define SSCH_PRAK_MEGAINT_H
#endif //SSCH_PRAK_MEGAINT_H
#pragma GCC optimize("Ofast,unroll-loops,mfma,mavx,mavx2")
#pragma GCC target("avx,avx2,fma")
#pragma GCC optimize("03")
#pragma once
#include <vector>
#include <string>
#include <cstdint>

struct MegaInt {
    static const long long BASE = 10;
    static const long long SIZE = 100;

    int16_t digits[SIZE];
    bool positive;

    MegaInt() {
        positive = true;
        for (int i = 0; i < SIZE; i++) {
            digits[i] = 0;
        }
    }

    MegaInt(long long x) {
        positive = x >= 0;
        if (!positive) {
            x *= -1;
        }
        for (int i = 0; i < SIZE; i++) {
            digits[i] = 0;
        }

        int next = 0;
        while (x) {
            digits[next++] = x % BASE;
            x /= BASE;
        }
    }

    MegaInt(std::string x) {
        positive = x[0] != '-';
        for (int i = 0; i < SIZE; ++i) {
            digits[i] = 0;
        }
        int next = 0;
        while (!x.empty() && x.back() != '-') {
            digits[next++] = x.back()-'0';
            x.pop_back();
        }
    }

    MegaInt(std::string s, int p) {
        for (int i = 0; i < SIZE; ++i) {
            digits[i] = 0;
        }
        std::reverse(s.begin(), s.end());
        positive = s.back() != '-';
        if (!positive) {
            s.pop_back();
        }
        while (!s.empty()) {
            *this *= p;
            if (s.back() >='A' && s.back() <='Z') {
                *this += s.back() - 'A' + 10;
            } else if (s.back() == '[') {
                int tmp = 0;
                s.pop_back();
                while (s.back() != ']') {
                    tmp *= 10;
                    tmp += s.back()-'0';
                    s.pop_back();
                }
                *this += tmp;
            } else {
                *this += s.back() - '0';
            }
            s.pop_back();
        }
    }

    MegaInt(const MegaInt& other) {
        positive = other.positive;
        for (int i = 0; i < SIZE; ++i) {
            digits[i] = other.digits[i];
        }
    }

    MegaInt& operator=(const MegaInt& other) {
        positive = other.positive;
        for (int i = 0; i < SIZE; ++i) {
            digits[i] = other.digits[i];
        }

        return *this;
    }
    bool operator<(const MegaInt& other) {
        for (int i = SIZE-1; i >= 0; --i) {
            if (digits[i] != other.digits[i]) {
                return digits[i] < other.digits[i];
            }
        }
        return false;
    }
    void operator+=(const MegaInt& other) {
        for (int i = 0; i < SIZE; ++i)  {
            digits[i] += other.digits[i];
        }

        for (int i = 0; i < SIZE - 1; ++i) {
            if (digits[i] >= BASE) {
                digits[i] -= BASE;
                digits[i + 1]++;
            }
        }
    }

    void operator+=(int other) {
        for (int i = 0; i < SIZE; ++i) {
            digits[i] += other%BASE;
            other /= BASE;
        }

        for (int i = 0; i < SIZE - 1; ++i) {
            if (digits[i] >= BASE) {
                digits[i] -= BASE;
                digits[i + 1]++;
            }
        }
    }

    MegaInt operator+(const MegaInt& other) {
        MegaInt n(*this);
        n += other;
        return n;
    }

    MegaInt& operator++() {
        *this += 1;
        return *this;
    }

    void operator-=(const MegaInt& other) {
        for (int i = 0; i < SIZE; ++i) {
            digits[i] -= other.digits[i];
        }

        for (int i = 0; i < SIZE - 1; ++i) {
            if (digits[i] < 0) {
                digits[i] += BASE;
                digits[i + 1]--;
            }
        }
    }

    MegaInt operator-(const MegaInt& other) {
        MegaInt n(*this);
        n -= other;
        return n;
    }

    MegaInt& operator--() {
        *this -= 1;
        return *this;
    }

    void operator*=(const MegaInt& other) {
        *this = *this * other;
    }

    void operator*=(int x) {
        *this = *this * x;
    }

    MegaInt operator*(const MegaInt& other) {
        MegaInt result;
        result.positive = positive^other.positive;
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE - i; ++j) {
                result.digits[i + j] += digits[i] * other.digits[j];
            }
        }
        for (int i = 0; i < SIZE - 1; ++i) {
            result.digits[i + 1] += result.digits[i] / BASE;
            result.digits[i] %= BASE;
        }

        return result;
    }

    MegaInt operator *(long long x) {
        MegaInt result;
        for (long long i = 0; i < x; ++i) {
            result += *this;
        }
        return result;
    }

    void operator/=(long long x) {
        for (int i = SIZE - 1; i >= 0; --i) {
            if (i) {
                digits[i - 1] += (digits[i] % x) * BASE;
            }

            digits[i] /= x;
        }
        for (int i = 0; i < SIZE - 1; ++i) {
            digits[i + 1] += digits[i] / BASE;
            digits[i] %= BASE;
        }
    }

    MegaInt operator/(long long x) {
        MegaInt n(*this);
        n /= x;
        return n;
    }

    MegaInt operator/(const MegaInt& x) {
        std::string INF(SIZE/2, '9');
        MegaInt l = 0;
        MegaInt r = INF;
        while (r-l-1 != 0) {
            MegaInt m = (r + l) / 2;
            if (!(*this < m*x)) {
                l = m;
            } else {
                r = m;
            }
        }
        return l;
    }

    MegaInt operator/=(const MegaInt& x) {
        *this = *this/x;
        return *this;
    }

    long long operator%(long long x) {
        MegaInt t = *this - (*this / x) * x;
        long long ans = 0;
        for (int i = SIZE-1; i >= 0; --i) {
            ans *= 10;
            ans += t.digits[i];
        }
        return ans;
    }

    MegaInt operator%(const MegaInt& x) {
        MegaInt t = *this - (*this / x) * x;
        MegaInt ans = 0;
        for (int i = SIZE-1; i >= 0; --i) {
            ans *= 10;
            ans += t.digits[i];
        }
        return ans;
    }

//    long long operator%(const MegaInt& x) {
//        MegaInt t = *this - (*this/x)*x;
//        long long ans = 0;
//        for (int i = SIZE-1; i >= 0; --i) {
//            ans *= 10;
//            ans += t.digits[i];
//        }
//        return ans;
//    }

    friend std::ostream& operator<<(std::ostream& out, const MegaInt& x);


    bool operator ==(const MegaInt& other) {
        for (int i = 0; i < SIZE; ++i) {
            if (other.digits[i] != digits[i]) {
                return false;
            }
        }
        return true;
    }
    bool operator !=(const MegaInt& other) {
        return !(*this == other);
    }
    bool operator ==(long long x) {
        MegaInt y = x;
        return y == *this;
    }
    bool operator !=(long long x) {
        return !(*this == x);
    }
};

MegaInt operator*(const MegaInt& lhs, const MegaInt& rhs) {
    MegaInt result;
    for (int i = 0; i < lhs.SIZE; i++) {
        for (int j = 0; j < lhs.SIZE - i; j++) {
            result.digits[i + j] += lhs.digits[i] * rhs.digits[j];
        }
    }
    for (int i = 0; i < lhs.SIZE - 1; i++) {
        result.digits[i + 1] += result.digits[i] / lhs.BASE;
        result.digits[i] %= lhs.BASE;
    }

    return result;
}

std::ostream& operator<<(std::ostream& out, const MegaInt& x) {
    bool flag = false;
    if (!x.positive) {
        std::cout << '-';
    }
    for (int i = x.SIZE-1; i >= 0; --i) {
        flag |= x.digits[i];
        if (flag) {
            out << x.digits[i];
        }
    }
    if (!flag) {
        out << '0';
    }
    return out;
}
