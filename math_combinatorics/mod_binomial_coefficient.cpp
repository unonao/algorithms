/* mod_binomial_coefficient.cpp
    modでの二項係数を求める

    制約：
        n<=10^7
        k<=10^7
        p(mod)は素数

    verified:
        AtCoder ABC021 D - 多重ループ
        https://abc021.contest.atcoder.jp/tasks/abc021_d
*/

#include <bits/stdc++.h>
using namespace std;
const int MOD = 1e9 + 7;

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

/*  nCk :MODでの二項係数を求める（前処理 int_nCk が必要）
    計算量:O(1)
*/
long long nCk(int n, int k) {
    assert(!(n < k));
    assert(!(n < 0 || k < 0));
    return fact[n] * (fact_inv[k] * fact_inv[n - k] % MOD) % MOD;
}

int main() {
    init_nCk(10000000);
    long long n, k;
    cin >> n >> k;
    cout << nCk(n + k - 1, k) << endl;
}
