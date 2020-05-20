/* coordinate_compress_2D.cpp
    2Dの座標圧縮を行う

    verified: [AOJ] DSL_4_A Union of Rectangles
        http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_4_A&lang=ja
*/

#include <bits/stdc++.h>
using namespace std;

/* compress
    (X1,Y1),(X2,Y2)という二点で表されるもの（長方形や直線など）について、行か列の片方（X1とX2 or Y1とY2）を座標圧縮する（副作用）
    返り値: ソートされ重複要素を除いた値
    計算量: O(n log n)
*/
template <typename T>
vector<T> compress(vector<T> &C1, vector<T> &C2) {
    vector<T> vals;
    int N = (int)C1.size();
    for (int i = 0; i < N; i++) {
        for (T d = 0; d <= 1; d++) {  // その位置と、一つ隣を確保(隣を確保しないと空白が埋まってしまうことがある)
            T tc1 = C1[i] + d;
            T tc2 = C2[i] + d;
            vals.push_back(tc1);
            vals.push_back(tc2);
        }
    }
    // ソート
    sort(vals.begin(), vals.end());
    // 隣り合う重複を削除(unique), 末端のゴミを削除(erase)
    vals.erase(unique(vals.begin(), vals.end()), vals.end());
    for (int i = 0; i < N; i++) {
        C1[i] = lower_bound(vals.begin(), vals.end(), C1[i]) - vals.begin();
        C2[i] = lower_bound(vals.begin(), vals.end(), C2[i]) - vals.begin();
    }
    return vals;
}

int main() {
    int N;
    cin >> N;
    vector<long long> X1(N), Y1(N), X2(N), Y2(N);
    for (int i = 0; i < N; i++) {
        cin >> X1.at(i) >> Y1.at(i) >> X2.at(i) >> Y2.at(i);
    }
    vector<long long> X = compress(X1, X2);
    vector<long long> Y = compress(Y1, Y2);

    int w = (int)X.size();
    int h = (int)Y.size();
    vector<vector<int>> G(w, vector<int>(h));
    // imos法で塗りつぶし
    for (int i = 0; i < N; i++) {
        G[X1[i]][Y1[i]]++;
        G[X2[i]][Y2[i]]++;
        G[X1[i]][Y2[i]]--;
        G[X2[i]][Y1[i]]--;
    }
    for (int x = 1; x < w; x++) {
        for (int y = 0; y < h; y++) {
            G[x][y] += G[x - 1][y];
        }
    }
    for (int x = 0; x < w; x++) {
        for (int y = 1; y < h; y++) {
            G[x][y] += G[x][y - 1];
        }
    }

    long long ans = 0;
    for (int x = 0; x < w - 1; x++) {
        for (int y = 0; y < h - 1; y++) {
            if (G[x][y]) {
                ans += (X[x + 1] - X[x]) * (Y[y + 1] - Y[y]);
            }
        }
    }
    cout << ans << endl;
}
