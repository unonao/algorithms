/* bell_number_stirling.cpp
    ベル数を求める
    計算: O(kn)

    verified: AOJ DPL_5_G Balls and Boxes 7
    http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_5_G
*/

#include <bits/stdc++.h>
using namespace std;
const int MOD = 1000000007;  // 素数

int main() {
    long long N, K;
    cin >> N >> K;

    vector<vector<long long>> S(N + 1, vector<long long>(K + 1, 0));
    S[0][0] = 1;

    for (long long n = 1; n < N + 1; n++) {
        for (long long k = 1; k < K + 1; k++) {
            S[n][k] = (k * S[n - 1][k] + S[n - 1][k - 1]) % MOD;
        }
    }

    long long ans = 0;
    for (int k = 0; k <= K; k++) {
        ans = (ans + S[N][k]) % MOD;
    }
    cout << ans << endl;

    return 0;
}
