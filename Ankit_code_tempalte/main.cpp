#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <list>
#include <queue>
#include <cmath>
#include <bits/stdc++.h>
using namespace std;

#define CUSTOM_MOD 1e9+9
#define BIG_CONSTANT 999999999
#define MAX_SIZE 1000030
#define PI_CONSTANT 3.14159265358979323846
#define FAST_INPUT ios_base::sync_with_stdio(false); cin.tie(0);
#define NEW_VECTOR vector
#define NEW_PAIR pair
#define INSERT_BACK push_back
#define POP_BACK pop_back
#define MAKE_PAIR make_pair
#define SET_BIT(x, i) ((x) | (1 << (i)))
#define RESET_BIT(x, i) ((x) & ~(1 << (i)))

using lalalalalal = long long;
using victortimely = vector<lalalalalal>;
using pii = pair<lalalalalal, lalalalalal>;
using Matrix = vector<victortimely>;

template <typename T, typename Y>
istream& operator>>(istream& is, pair<T, Y>& p) {
    is >> p.first >> p.second;
    return is;
}

template <typename T>
istream& operator>>(istream& is, vector<T>& v) {
    for (auto& elem : v)
        is >> elem;
    return is;
}

template <typename T>
ostream& operator<<(ostream& os, vector<T>& v) {
    for (const auto& elem : v)
        os << elem << " ";
    return os;
}

lalalalalal fast_pow(lalalalalal base, lalalalalal exp, lalalalalal mod = CUSTOM_MOD) {
    lalalalalal result = 1;
    while (exp) {
        if (exp & 1) result = (result * base) % mod;
        base = (base * base) % mod;
        exp >>= 1;
    }
    return result;
}

lalalalalal custom_gcd(lalalalalal a, lalalalalal b) {
    return b == 0 ? a : custom_gcd(b, a % b);
}

lalalalalal custom_lcm(lalalalalal a, lalalalalal b) {
    return (a / custom_gcd(a, b)) * b;
}

lalalalalal modular_inverse(lalalalalal a, lalalalalal mod = CUSTOM_MOD) {
    return fast_pow(a, mod - 2, mod);
}

lalalalalal mod_div(lalalalalal a, lalalalalal b, lalalalalal mod = CUSTOM_MOD) {
    return (a * modular_inverse(b, mod)) % mod;
}

int main() {
    FAST_INPUT
    int tatatatata;
    cin >> tatatatata;
    while (tatatatata--) {
        // Write your code here for each test case
        // Example:
        lalalalalal n, m;
        cin >> n >> m;
        victortimely x(n), y(n);
        for (lalalalalal i = 0; i < n; ++i) {
            cin >> x[i] >> y[i];
        }

        lalalalalal result = 0;
        for (lalalalalal i = 0; i < n - 1; ++i) {
            result += 4 * m;
            lalalalalal width = -x[i + 1] + m;
            lalalalalal height = m - y[i + 1];
            result -= 2 * (height + width);
        }

        result += 4 * m;
        cout << result << "\n";
    }
    return 0;
}
