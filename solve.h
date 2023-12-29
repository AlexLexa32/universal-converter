#ifndef SSCH_CONVERTOR_SOLVE_H
#define SSCH_CONVERTOR_SOLVE_H

#endif //SSCH_CONVERTOR_SOLVE_H

#pragma GCC optimize("Ofast,unroll-loops,mfma,mavx,mavx2")
#pragma GCC target("avx,avx2,fma")
#pragma GCC optimize("03")
#pragma once
#include <iostream>
#include <map>
#include "MegaInt.h"
#include "Fraction.h"

MegaInt power(int n, int k) {
    MegaInt ans = 1;
    for (int i = 0; i < k; ++i) {
        ans *= n;
    }
    return ans;
}

std::string int2string(int64_t a) {
    std::string ans;
    while (a) {
        ans.push_back(a%10+'0');
        a /= 10;
    }
    if (ans.empty()) {
        ans = "0";
    }
    std::reverse(ans.begin(), ans.end());
    return ans;
}

int sz(std::string s) {
    int ans = 0;
    for (int i = 0; i < s.size(); ++i) {
        if (s[i] == '[') {
            ++ans;
            while (s[i] != ']') {
                ++i;
            }
        } else {
            ans += (s[i] >= '0' && s[i] <= '9') || (s[i] >= 'A' && s[i] <= 'Z');
        }
    }
    return ans;
}

std::string solve(const std::string& a_s, const std::string& b_s, const std::string& c_s, int p, int q) {
    std::string ret;
    MegaInt a(a_s, p);
    int b_sz = sz(b_s);
    MegaInt b(b_s, p);
    int c_sz = sz(c_s);
    MegaInt c(c_s, p);
    Fraction x(a);
    Fraction y(b, power(p, b_sz));
    MegaInt rr = power(p, b_sz) * (power(p, c_sz) - 1);
    if (rr == 0) {
        rr = 1;
    }
    Fraction z(c, rr);
    x += y+z;
    a = x.num_/x.den_;
    x -= a;
    std::vector<long long> ans;
    while (a != 0) {
        ans.push_back(a%q);
        a /= q;
    }
    std::reverse(ans.begin(), ans.end());
    if ((int)ans.size() == 0) {
        ret += "0";
    }
    for (auto e : ans) {
        if (e >= 10 && e <= 'Z'-'A'+10) {
            char tmp = 'A'+e-10;
            ret.push_back(tmp);
        } else if (e > 'Z'-'A'+10) {
            ret += "[" + int2string(e) + "]";
        } else {
            ret += int2string(e);
        }
    }
    //std::cout << '.';
    std::map<Fraction, int> map;
    int i = 1;
    int r = -5;
    ans.resize(0);
    while (true) {
        if (x == 0) {
            break;
        }
        if (map[x] != 0) {
            r = map[x]-1;
            break;
        }
        map[x] = i;
        x *= q;
        a = x.num_/x.den_;
        x -= a;
        ans.push_back(a%(q*q));
        ++i;
    }
    if (!ans.empty()) {
        ret += '.';
    }
    i = 0;
    for (auto e : ans) {
        if (r == i && r != -5) {
            ret += '(';
        }
        if (e >= 10 && e <= 'Z'-'A'+10) {
            char tmp = 'A'+e-10;
            ret += tmp;
        } else if (e > 'Z'-'A'+10) {
            ret += + "[" + int2string(e) + "]";
        } else {
            ret += int2string(e);
        }
        ++i;
    }
    if (r != -5) {
        ret += ')';
    }
    //std::reve
    return ret;
}