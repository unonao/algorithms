/* stirling_number_of_the_second_kind_DP.cpp
    DPで第2種スターリング数を求める

    計算量: O(nk)

    verified: AOJ DPL_5_I Balls and Boxes 9
    http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_5_I
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

    cout << S[N][K] << endl;

    return 0;
}
