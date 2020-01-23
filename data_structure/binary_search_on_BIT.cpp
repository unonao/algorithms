/* binary_indexed_tree.cpp
    BIT 上で二分探索を行う。

    応用: 集合の中で w 番目に小さいものや、ある要素が何番目に小さいかが高速に分かる
        ・add(a,1): 集合への要素 a の追加(a 番目を 1 にする)
        ・add(a,-1): 集合への要素 a の削除(a 番目を 1 から 0 にする)
        ・sum(a): a が何番目(1はじまり)に小さいか
        ・lower_bound(w): w 番目(1はじまり)に小さい要素 a は何か
        値の範囲が N までとした時、メモリO(N), 計算量O(logN)だけかかる

    (a_1 + a_2 + ... + a_x >= w となるような最小の x を求めるのは、
    ナイーブにやると a_1 + a_2 + ... + a_i の計算を O(logn)回行うので、O((logn)^2)かかる。
    BIT 上で二分探索を行うようにすると、O(log(n)) で計算できる。)

    参考:
        http://hos.ac/slides/20140319_bit.pdf
    verified:
        https://atcoder.jp/contests/arc033/tasks/arc033_3
*/

#include <bits/stdc++.h>
using namespace std;

/* BIT: 区間和の更新や計算を行う構造体
    初期値：a_1 = a_2 = ... = a_n = 0
    クエリ：
    ・sum(i): a_1 + a_2 + ... + a_i を計算する
    ・add(i,a): a_i += a とする
    ・lower_bound(w): a_1 + a_2 + ... + a_x >= w となるような最小の x を求める(ただし a_i >= 0)
    計算量は全て O(logn)
*/
template <typename T>
struct BIT {
    int n;
    vector<T> bit;
    BIT(int n_) : n(n_ + 1), bit(n, 0) {}

    T sum(int i) {
        T s(0);
        for (int x = i; x > 0; x -= (x & -x)) {
            s += bit[x];
        }
        return s;
    }

    void add(int i, T a) {  // add a to i
        // The range of i is from 1 to n
        if (i == 0) {
            return;
        } else {
            for (int x = i; x <= n; x += (x & -x)) {
                bit[x] += a;
            }
        }
    }

    int lower_bound(int w) {
        if (w <= 0) {
            return 0;
        } else {
            int x = 0, r = 1;
            while (r < n) {
                r = r << 1;
            }
            for (int k = r; k > 0; k = k >> 1) {
                if (x + k <= n && bit[x + k] < w) {
                    w -= bit[x + k];
                    x += k;
                }
            }
            return x + 1;
        }
    }
    // [l,r)
    T query(int l, int r) { return sum(r - 1) - sum(l - 1); }
};

int main() {
    int q;
    cin >> q;
    BIT<int> bit(3e5);
    vector<int> T(q), X(q);
    for (int i = 0; i < q; i++) {
        cin >> T.at(i) >> X.at(i);
    }

    for (int i = 0; i < q; i++) {
        if (T[i] == 1) {
            bit.add(X[i], 1);
        } else if (T[i] == 2) {
            int a = bit.lower_bound(X[i]);
            cout << a << endl;
            bit.add(a, -1);
        }
    }

    return 0;
}
