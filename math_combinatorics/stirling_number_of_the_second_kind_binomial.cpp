/* stirling_number_of_the_second_kind_binomial.cpp
    第2種スターリング数を求める

    前処理: O(n)
    スターリング数: O(k log n)

    verified: AOJ DPL_5_I Balls and Boxes 9
    http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_5_I
*/

#include <bits/stdc++.h>
using namespace std;
const int MOD = 1000000007;  // 素数
vector<long long> fact, fact_inv, inv;

/*  init_nCk :二項係数のための前処理
    計算量:O(n)
*/
void init_nCk(int SIZE) {
    fact.resize(SIZE + 5);
    fact_inv.resize(SIZE + 5);
    inv.resize(SIZE + 5);
    fact[0] = fact[1] = 1;
    fact_inv[0] = fact_inv[1] = 1;
    inv[1] = 1;
    for (int i = 2; i < SIZE + 5; i++) {
        fact[i] = fact[i - 1] * i % MOD;
        inv[i] = MOD - inv[MOD % i] * (MOD / i) % MOD;
        fact_inv[i] = fact_inv[i - 1] * inv[i] % MOD;
    }
}

/*  nCk :MODでの二項係数を求める(前処理 int_nCk が必要)
    計算量:O(1)
*/
long long nCk(int n, int k) {
    assert(!(n < k));
    assert(!(n < 0 || k < 0));
    return fact[n] * (fact_inv[k] * fact_inv[n - k] % MOD) % MOD;
}

// べき乗
long long pow(long long x, long long n) {
    long long ret = 1;
    while (n > 0) {
        if (n & 1) ret = ret * x % MOD;
        x = x * x % MOD;
        n >>= 1;
    }
    return ret;
}

long long S(long long n, long long k) {
    long long ret = 0;
    for (long long i = 0; i <= k; i++) {
        if ((k - i) % 2 == 0) {
            ret = ret + nCk(k, i) * pow(i, n) % MOD;
            ret %= MOD;
        } else {
            ret = ret + (MOD - nCk(k, i) * pow(i, n) % MOD);
            ret %= MOD;
        }
    }
    ret = ret * fact_inv[k] % MOD;
    return ret;
}

int main() {
    init_nCk(10000000);
    long long N, K;
    cin >> N >> K;

    cout << S(N, K) << endl;

    return 0;
}
