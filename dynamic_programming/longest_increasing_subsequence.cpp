/* longest_increasing_subsequence.cpp
    最長増加部分列の長さを動的計画法により求める
    （i<j かつ a_i < a_j (or a_i <= a_j) を満たす最長の部分列）

    dp[i] := 長さ i+1 の単調増加部分列の最終要素らにおける最小値
    （dp 自体も単調増加）

    verified: AOJ DPL_1_D
        http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_1_D
*/

#include <bits/stdc++.h>
using namespace std;

/* lis(seq):
    入力: 数列 seq, 広義かどうかを表す weak
    出力: 最長増加部分列の長さ
    計算量: O(NlogN)
*/
int lis(const vector<long long> &seq, bool weak = false) {
    int N = seq.size();
    const long long INF = 1LL << 60;
    vector<long long> dp(N + 5, INF);
    for (int i = 0; i < N; i++) {
        if (!weak) {
            *lower_bound(dp.begin(), dp.end(), seq[i]) = seq[i];
        } else {
            *upper_bound(dp.begin(), dp.end(), seq[i]) = seq[i];
        }
    }
    return (lower_bound(dp.begin(), dp.end(), INF) - dp.begin());
}

int main() {
    int n;
    cin >> n;
    vector<long long> a(n);
    for (int i = 0; i < n; i++) cin >> a.at(i);
    cout << lis(a) << endl;
}
