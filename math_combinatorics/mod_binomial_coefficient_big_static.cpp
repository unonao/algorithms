/* mod_binomial_coefficient_big_static.cpp
    modでの二項係数を求める

    制約：
        n<=10^9
        n は固定
        k<=10^7
        p(mod)は素数
    計算量：
        前処理 O(k)
        クエリ O(1)

    verified:
        AtCoder ABC021 D - 多重ループ
        https://abc021.contest.atcoder.jp/tasks/abc021_d
*/

#include <bits/stdc++.h>
using namespace std;
const int MOD = 1e9 + 7;

vector<long long> fact_inv, inv, Com;

/*  init_nCk :二項係数のための前処理
    計算量:O(n)
*/
void init_nCk(int n, int SIZE) {
    fact_inv.resize(SIZE + 5);
    inv.resize(SIZE + 5);
    fact_inv[0] = fact_inv[1] = 1;
    inv[1] = 1;
    for (int i = 2; i < SIZE + 5; i++) {
        inv[i] = MOD - inv[MOD % i] * (MOD / i) % MOD;
        fact_inv[i] = fact_inv[i - 1] * inv[i] % MOD;
    }
    Com.resize(SIZE + 5);
    Com[0] = 1;
    for (int i = 1; i < SIZE + 5; i++) {
        Com[i] = Com[i - 1] * ((n - i + 1) * inv[i] % MOD) % MOD;
    }
}

/*  nCk :MODでの二項係数を求める(前処理 int_nCk が必要)
    計算量:O(1)
*/
long long nCk(int k) {
    assert(!(k < 0));
    return Com[k];
}

int main() {
    long long n, k;
    cin >> n >> k;
    init_nCk(n + k - 1, 10000000);
    cout << nCk(k) << endl;
}
