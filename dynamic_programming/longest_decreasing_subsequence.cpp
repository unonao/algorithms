/* longest_decreasing_subsequence.cpp
    最長減少部分列の長さを動的計画法により求める
    （i<j かつ a_i > a_j (or a_i >= a_j) を満たす最長の部分列）

    dp[i] := 長さ i+1 の単調減少部分列の最終要素らにおける最大値
    （dp 自体も単調減少）

    verified: AtCoder ABC134 E - Sequence Decomposing
        https://atcoder.jp/contests/abc134/tasks/abc134_e
*/

#include <bits/stdc++.h>
using namespace std;

/* lds(seq):
    入力: 数列 seq, 広義かどうかを表す weak
    出力: 最長減少部分列の長さ
    計算量: O(NlogN)
*/
int lds(const vector<long long> &seq, bool weak = false) {
    int N = seq.size();
    const long long INF = 1LL << 60;
    vector<long long> dp(N + 5, -INF);
    for (int i = 0; i < N; i++) {
        if (!weak) {
            *lower_bound(dp.begin(), dp.end(), seq[i], greater<long long>()) = seq[i];
        } else {
            *upper_bound(dp.begin(), dp.end(), seq[i], greater<long long>()) = seq[i];
        }
    }
    return (lower_bound(dp.begin(), dp.end(), -INF, greater<long long>()) - dp.begin());
}

int main() {
    int n;
    cin >> n;
    vector<long long> a(n);
    for (int i = 0; i < n; i++) cin >> a.at(i);
    cout << lds(a, true) << endl;
}
