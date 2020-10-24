/* bell_number_preprocess.cpp
    ベル数を求める（前計算あり）
    前処理: O(n)
    計算: O(k log n)

    verified: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_5_G&lang=ja
*/
#include <bits/stdc++.h>
using namespace std;
const int MOD = 1000000007;  // 素数
vector<long long> pre_sum, fact_inv, inv;

/*  init_bell :前処理
    計算量:O(n)
*/
void init_bell(int SIZE) {
    // 階乗の逆元を計算
    fact_inv.resize(SIZE + 5);
    inv.resize(SIZE + 5);
    fact_inv[0] = fact_inv[1] = 1;
    inv[1] = 1;
    for (int i = 2; i < SIZE + 5; i++) {
        inv[i] = MOD - inv[MOD % i] * (MOD / i) % MOD;
        fact_inv[i] = fact_inv[i - 1] * inv[i] % MOD;
    }
    // 目的の値を前計算
    pre_sum.resize(SIZE + 5);
    pre_sum[0] = 1;
    for (int i = 1; i < SIZE + 5; i++) {
        if (i % 2 == 1) {
            pre_sum[i] = (pre_sum[i - 1] + (MOD - fact_inv[i])) % MOD;
        } else {
            pre_sum[i] = (pre_sum[i - 1] + fact_inv[i]) % MOD;
        }
    }
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

/* ベル数を求める（事前にinit_bell の実行が必要）
    計算量：O(K log N)
*/
long long bell(long long N, long long K) {
    long long ret = 0;
    for (long long i = 0; i <= K; i++) {
        ret += (pow(i, N) * fact_inv[i]) % MOD * pre_sum[K - i] % MOD;
        ret %= MOD;
    }
    return ret;
}

int main() {
    init_bell(10000000);
    long long N, K;
    cin >> N >> K;

    cout << bell(N, K) << endl;

    return 0;
}
