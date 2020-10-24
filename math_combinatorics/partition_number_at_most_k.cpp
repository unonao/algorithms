/* partition_number_at_most_k.cpp
    計算量：O(nk)

    verified: AOJ DPL_5_L Balls and Boxes 10
    http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_5_L
*/

#include <bits/stdc++.h>
using namespace std;
const int MOD = 1000000007;  // 素数

int main() {
    long long N, K;
    cin >> N >> K;

    vector<vector<long long>> P(N + 1, vector<long long>(K + 1, 0));
    P[0][0] = 1;

    for (long long n = 0; n < N + 1; n++) {
        for (long long k = 1; k < K + 1; k++) {
            if (n - k >= 0) {
                P[n][k] = (P[n][k - 1] + P[n - k][k]) % MOD;
            } else {
                P[n][k] = P[n][k - 1];
            }
        }
    }

    cout << P[N][K] << endl;

    return 0;
}
