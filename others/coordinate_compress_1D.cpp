/* coordinate_compress_1D.cpp
    1Dの座標圧縮を行う
        Input: 5 3 3 1 6 1
        Output: 1 1 0 2 0

    verified: [AtCoder] ABC 036 C - 座圧
        https://atcoder.jp/contests/abc036/tasks/abc036_c
*/

#include <bits/stdc++.h>
using namespace std;

/* compress
    X を座標圧縮して書き換える（副作用）
    返り値: ソート済みの値
    計算量: O(n log n)
*/
template <typename T>
vector<T> compress(vector<T> &X) {
    vector<T> vals = X;
    sort(vals.begin(), vals.end());
    // 隣り合う重複を削除(unique), 末端のゴミを削除(erase)
    vals.erase(unique(vals.begin(), vals.end()), vals.end());
    for (int i = 0; i < (int)X.size(); i++) {
        X[i] = lower_bound(vals.begin(), vals.end(), X[i]) - vals.begin();
    }
    return vals;
}

int main() {
    int N;
    cin >> N;
    vector<int> a(N);
    for (int i = 0; i < N; i++) {
        cin >> a.at(i);
    }
    compress(a);
    for (auto b : a) {
        cout << b << "\n";
    }
}
