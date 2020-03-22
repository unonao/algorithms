/* mod_binomial_coefficient_dp.cpp
    (漸化式/DP で) nCk % p を求める（p は素数でなくても良い）

    制約：
        1≦ k ≦ n ≦ 5000
        p は素数である必要がない(The "mod p" do NOT have to be prime.)
    計算量：
        前処理 O(MAX_N*MAX_N)
        クエリ O(1)

    verified:
        AtCoder ABC021 D - 多重ループ (99点取得)
        https://abc021.contest.atcoder.jp/tasks/abc021_d
*/

#include <bits/stdc++.h>
using namespace std;

/* Comb：nCk % p の計算のための構造体
    前処理: O(MAX_N*MAX_N)
    nCk(n,k): nCk % p の計算。O(1)
*/
struct Comb {
    const int MAX_N = 5000;         // 最大値
    vector<vector<long long>> com;  // 前計算の結果を保存
    long long p;                    // p は素数でなくても良い
    Comb(long long _p) : p(_p) {
        init(p);
    }
    void init(long long p) {  // 動的計画法で前処理
        com.assign(MAX_N, vector<long long>(MAX_N));
        com[0][0] = 1;
        for (int i = 1; i < MAX_N; ++i) {
            com[i][0] = 1;
            for (int j = 1; j < MAX_N; j++) {
                com[i][j] = (com[i - 1][j - 1] + com[i - 1][j]) % p;
            }
        }
    }
    long long nCk(int n, int k) {
        assert(!(n < k));
        assert(!(n < 0 || k < 0));
        return com[n][k];
    }
};

int main() {
    Comb comb(1e9 + 7);
    long long n, k;
    cin >> n >> k;
    cout << comb.nCk(n + k - 1, k) << endl;
}
