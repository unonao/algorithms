/* mod_binomial_coefficient_dp.cpp
    (漸化式/DP で)modでの二項係数を求める

    制約：
        1≦ k ≦ n ≦ 5000
        p は素数である必要がない(The "mod p" do NOT have to be prime.)

    verified:
        AtCoder ABC021 D - 多重ループ (99点取得)
        https://abc021.contest.atcoder.jp/tasks/abc021_d
*/

#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 5000;
const long long MOD = 1000000007;

long long Com[MAX_N][MAX_N];

/* init_nCk:二項係数のための前処理
    計算量:O(MAX_N*MAX_N)
*/
void init_nCk() {
    memset(Com, 0, sizeof(Com));
    Com[0][0] = 1;
    for (int i = 1; i < MAX_N; ++i) {
        Com[i][0] = 1;
        for (int j = 1; j < MAX_N; j++) {
            Com[i][j] = (Com[i - 1][j - 1] + Com[i - 1][j]) % MOD;
        }
    }
}

/*  nCk :MODでの二項係数を求める(前処理 int_nCk が必要)
    計算量:O(1)
*/
long long nCk(int n, int k) {
    assert(!(n < k));
    assert(!(n < 0 || k < 0));
    return Com[n][k];
}

int main() {
    init_nCk();
    long long n, k;
    cin >> n >> k;
    cout << nCk(n + k - 1, k) << endl;
}
