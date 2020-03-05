/* binary_indexed_tree_2D.cpp
    2次元に対応させたBIT

    verified: AOJ Taiyaki-Master and Eater
        http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2842
*/

#include <bits/stdc++.h>
using namespace std;

/* BIT2D:
    初期値は全て 0
    ・add(h,w,x): (h,w) に x を加算する
    ・sum(h,w): 1≦i≦h かつ 1≦j≦w の範囲の合計値を求める
    ・query(h1,w1,h2,w2): h1≦i<h2 かつ w1≦j<w2 の範囲の合計値を求める(1-indexed)
    計算量は全て O(logW * logH)
*/
template <typename T>
struct BIT2D {
    int H, W;
    vector<vector<T>> bit;  // データの格納先
    BIT2D(int H_, int W_) { init(H_, W_); }
    void init(int H_, int W_) {
        H = H_ + 1;
        W = W_ + 1;
        bit.assign(H, vector<T>(W, 0));
    }

    void add(int h, int w, T x) {
        for (int i = h; i < H; i += (i & -i)) {
            for (int j = w; j < W; j += (j & -j)) {
                bit[i][j] += x;
            }
        }
    }
    // 1≦i≦h かつ 1≦j≦w
    T sum(int h, int w) {
        T s(0);
        for (int i = h; i > 0; i -= (i & -i)) {
            for (int j = w; j > 0; j -= (j & -j)) {
                s += bit[i][j];
            }
        }
        return s;
    }

    // h1≦i<h2 かつ w1≦j<w2
    T query(int h1, int w1, int h2, int w2) {
        return sum(h2 - 1, w2 - 1) - sum(h2 - 1, w1 - 1) - sum(h1 - 1, w2 - 1) + sum(h1 - 1, w1 - 1);
    }

    /* debug */
    void print() {
        for (int i = 1; i < H; ++i) {
            for (int j = 1; j < W; ++j) cout << query(i, j, i + 1, j + 1) << ",";
            cout << endl;
        }
    }
};

int main() {
    int H, W, T, Q;
    cin >> H >> W >> T >> Q;
    BIT2D<int> baking(H, W), baked(H, W);
    queue<tuple<int, int, int>> que;

    for (int i = 0; i < Q; i++) {
        int t, c, h, w;
        cin >> t >> c >> h >> w;
        while (!que.empty()) {
            tuple<int, int, int> tup = que.front();
            if (get<0>(tup) <= t) {
                que.pop();
                baking.add(get<1>(tup), get<2>(tup), -1);
                baked.add(get<1>(tup), get<2>(tup), 1);
            } else {
                break;
            }
        }

        if (c == 0) {
            baking.add(h, w, 1);
            que.push(make_tuple(t + T, h, w));
        } else if (c == 1) {
            if (baked.query(h, w, h + 1, w + 1) == 1) baked.add(h, w, -1);
        } else if (c == 2) {
            int h2, w2;
            cin >> h2 >> w2;
            cout << baked.query(h, w, h2 + 1, w2 + 1) << " " << baking.query(h, w, h2 + 1, w2 + 1) << endl;
        }
    }
    return 0;
}
