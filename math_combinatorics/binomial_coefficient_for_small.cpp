/* binomial_coefficient_for_small.cpp
    n が非常に小さく MOD を取る必要がない場合の nCk

    verified: [AtCoder] AGC 017 A - Biscuits
        https://atcoder.jp/contests/agc017/tasks/agc017_a
*/
#include <bits/stdc++.h>
using namespace std;

/* nCk for small n
    n は 50 程度まで
    計算量: O(k)
*/
long long nCk(int n, int k) {
    long long ret = 1;
    for (int i = 0; i < k; i++) {
        ret = ret * (n - i) / (i + 1);
    }
    return ret;
}

int main() {
    int N, P;
    cin >> N >> P;
    vector<int> A(N);
    vector<long long> cnt(2, 0);
    for (int i = 0; i < N; i++) {
        cin >> A.at(i);
        A.at(i) %= 2;
        cnt.at(A[i])++;
    }

    long long ans = 0;
    for (int i = P; i <= cnt[1]; i += 2) {
        ans += nCk(cnt[1], i) * (1LL << cnt[0]);
    }
    cout << ans << endl;
}
