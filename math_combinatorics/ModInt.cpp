/* Modint.cpp
    modが絡む計算を整数の計算のようにするための構造体。
    二項係数付き

    verified:
        AtCoder ABC127 E - Cell Distance
        https://atcoder.jp/contests/abc127/tasks/abc127_e
*/

#include <bits/stdc++.h>
using namespace std;

template <int mod>
struct ModInt {
    int val;
    ModInt() : val(0) {}
    ModInt(long long x) : val(x >= 0 ? x % mod : (mod - (-x) % mod) % mod) {}
    int getmod() { return mod; }
    ModInt &operator+=(const ModInt &p) {
        if ((val += p.val) >= mod) {
            val -= mod;
        }
        return *this;
    }
    ModInt &operator-=(const ModInt &p) {
        if ((val += mod - p.val) >= mod) {
            val -= mod;
        }
        return *this;
    }
    ModInt &operator*=(const ModInt &p) {
        val = (int)(1LL * val * p.val % mod);
        return *this;
    }
    ModInt &operator/=(const ModInt &p) {
        *this *= p.inverse();
        return *this;
    }
    ModInt operator-() const { return ModInt(-val); }
    ModInt operator+(const ModInt &p) const { return ModInt(*this) += p; }
    ModInt operator-(const ModInt &p) const { return ModInt(*this) -= p; }
    ModInt operator*(const ModInt &p) const { return ModInt(*this) *= p; }
    ModInt operator/(const ModInt &p) const { return ModInt(*this) /= p; }
    bool operator==(const ModInt &p) const { return val == p.val; }
    bool operator!=(const ModInt &p) const { return val != p.val; }
    ModInt inverse() const {
        int a = val, b = mod, u = 1, v = 0, t;
        while (b > 0) {
            t = a / b;
            swap(a -= t * b, b);
            swap(u -= t * v, v);
        }
        return ModInt(u);
    }
    ModInt pow(long long n) const {
        ModInt ret(1), mul(val);
        while (n > 0) {
            if (n & 1) ret *= mul;
            mul *= mul;
            n >>= 1;
        }
        return ret;
    }
    friend ostream &operator<<(ostream &os, const ModInt &p) { return os << p.val; }
    friend istream &operator>>(istream &is, ModInt &a) {
        long long t;
        is >> t;
        a = ModInt<mod>(t);
        return (is);
    }
    static int get_mod() { return mod; }
};
const int MOD = 1000000007;  // if inv is needed, this shold be prime.
using modint = ModInt<MOD>;

/* Comb：modintで二項係数を計算する構造体
    前処理：O(n)
    二項係数の計算：O(1)
    制約：
        n<=10^7
        k<=10^7
        p(mod)は素数
*/
template <class T>
struct Comb {
    vector<T> fact_, fact_inv_, inv_;
    // Comb() {}
    Comb(int SIZE) : fact_(SIZE, 1), fact_inv_(SIZE, 1), inv_(SIZE, 1) { init(SIZE); }
    void init(int SIZE) {
        fact_.assign(SIZE, 1), fact_inv_.assign(SIZE, 1), inv_.assign(SIZE, 1);
        int mod = fact_[0].getmod();
        for (int i = 2; i < SIZE; i++) {
            fact_[i] = fact_[i - 1] * i;
            inv_[i] = -inv_[mod % i] * (mod / i);
            fact_inv_[i] = fact_inv_[i - 1] * inv_[i];
        }
    }
    T nCk(int n, int k) {
        assert(!(n < k));
        assert(!(n < 0 || k < 0));
        return fact_[n] * fact_inv_[k] * fact_inv_[n - k];
    }
    T nHk(int n, int k) {
        assert(!(n < 0 || k < 0));
        return nCk(n + k - 1, k);
    }
    T fact(int n) {
        assert(!(n < 0));
        return fact_[n];
    }
    T fact_inv(int n) {
        assert(!(n < 0));
        return fact_inv_[n];
    }
    T inv(int n) {
        assert(!(n < 0));
        return inv_[n];
    }
};

Comb<modint> comb(1000000);

int main() {
    long long N, M, K;
    cin >> N >> M >> K;
    modint sum = 0;
    for (int i = 0; i <= N - 1; ++i) {
        for (int j = 0; j <= M - 1; ++j) {
            modint tmp = modint(N - i) * modint(M - j) * modint(i + j);
            if (i != 0 && j != 0) {
                tmp *= 2;
            }
            sum += tmp;
        }
    }
    cout << sum * comb.nCk(N * M - 2, K - 2) << endl;
    return 0;
}
