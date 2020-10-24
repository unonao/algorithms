/* partition_number_with_k.cpp
    計算量：O(nk)

    verified: AOJ DPL_5_L Balls and Boxes 12
    http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_5_L
*/

#include <bits/stdc++.h>
using namespace std;
const int MOD = 1000000007;  // 素数

int main() {
    long long N, K;
    cin >> N >> K;

    vector<vector<long long>> p(N + 1, vector<long long>(K + 1, 0));
    p[0][0] = 1;

    for (long long n = 1; n < N + 1; n++) {
        for (long long k = 1; k < K + 1; k++) {
            if (n - k >= 0) {
                p[n][k] = (p[n - 1][k - 1] + p[n - k][k]) % MOD;
            } else {
                p[n][k] = p[n - 1][k - 1];
            }
        }
    }

    cout << p[N][K] << endl;

    return 0;
}
