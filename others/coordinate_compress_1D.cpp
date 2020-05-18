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
    X を座標圧縮した結果を返す
    計算量: O(n log n)
*/
template <typename T>
vector<int> compress(const vector<T> &X) {
    vector<T> vals = X;
    sort(vals.begin(), vals.end());
    // 隣り合う重複を削除(unique), 末端のゴミを削除(erase)
    vals.erase(unique(vals.begin(), vals.end()), vals.end());
    vector<int> ret;
    for (int i = 0; i < (int)X.size(); i++) {
        int id = lower_bound(vals.begin(), vals.end(), X[i]) - vals.begin();
        ret.push_back(id);
    }
    return ret;
}

int main() {
    int N;
    cin >> N;
    vector<int> a(N);
    for (int i = 0; i < N; i++) {
        cin >> a.at(i);
    }
    for (auto b : compress(a)) {
        cout << b << "\n";
    }
}
