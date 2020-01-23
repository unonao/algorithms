/* binary_indexed_tree.cpp
    BIT を用いて、区間和の更新や計算を高速に行う。

    応用: 転倒数の計算( i<j において a_i > a_j となる数を数える)
        j(0~n-1)について以下を繰り返す
            1. j-sum(j)を答えに加える
            2. add(a[j],1)
        sum(j)は i<j における a_i<= a_j となる数なので、 j-sum(j) で j を固定したときの転倒数が求まる

    参考：http://hos.ac/slides/20140319_bit.pdf
    verified: AOJ DSL_2_B
        http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_B&lang=jp
*/

#include <bits/stdc++.h>
using namespace std;

/* BIT: 区間和の更新や計算を行う構造体
    初期値は a_1 = a_2 = ... = a_n = 0
    ・add(i,a): a_i += a とする
    ・sum(i): a_1 + a_2 + ... + a_i を計算する
    ・query(l,r): [l,r) の区間の和を求める
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

    void add(int i, T a) {
        if (i == 0) {
            return;
        } else {
            for (int x = i; x <= n; x += (x & -x)) {
                bit[x] += a;
            }
        }
    }
    // [l,r)
    T query(int l, int r) { return sum(r - 1) - sum(l - 1); }
};

int main() {
    int n, q;
    cin >> n >> q;
    BIT<int> bit(2e5);
    vector<int> c(q), x(q), y(q);
    for (int i = 0; i < q; i++) {
        cin >> c.at(i) >> x.at(i) >> y.at(i);
    }

    for (int i = 0; i < q; i++) {
        if (c[i] == 0) {
            bit.add(x[i], y[i]);
        } else if (c[i] == 1) {
            cout << bit.query(x[i], y[i] + 1) << endl;
        }
    }

    return 0;
}
