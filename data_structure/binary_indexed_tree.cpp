/* binary_indexed_tree.cpp
    BIT を用いて、区間和の更新や計算を高速に行う。

    verified: AOJ DSL_2_B
        http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_B&lang=jp


    応用: 転倒数の計算( i<j において a_i > a_j となる数を数える)
        j(0~n-1)について以下を繰り返す
            1. j-sum(a_j)を答えに加える
            2. add(a_j,1)
        sum(a_j)は i<j における a_i<= a_j となる数なので、 j-sum(a_j) で j を固定したときの転倒数が求まる
        計算量は O(n long n)

    応用: 集合の中で w 番目に小さいものや、ある要素が何番目に小さいかが高速に分かる
        ・add(a,1): 集合への要素 a の追加(a 番目を 1 にする)
        ・add(a,-1): 集合への要素 a の削除(a 番目を 1 から 0 にする)
        ・sum(a): a が何番目(1はじまり)に小さいか
        ・lower_bound(w): w 番目(1はじまり)に小さい要素 a は何か
        値の範囲が N までとした時、メモリO(N), 計算量O(logN)だけかかる

        verified: ARC033 C - データ構造
            https://atcoder.jp/contests/arc033/tasks/arc033_3
*/

#include <bits/stdc++.h>
using namespace std;

/* BIT: 区間和の更新や計算を行う構造体
    初期値は a_1 = a_2 = ... = a_n = 0
    ・add(i,x): a_i += x とする
    ・sum(i): a_1 + a_2 + ... + a_i を計算する
    ・query(l,r): [l,r) の区間の和を求める
    ・lower_bound(w): a_1 + a_2 + ... + a_x >= w となるような最小の x を求める(ただし a_i >= 0)
    計算量は全て O(logn)
*/
template <typename T>
struct BIT {
    int n;          // 要素数
    vector<T> bit;  // データの格納先
    BIT(int n_) : n(n_ + 1), bit(n, 0) {}

    void add(int i, T x) {
        for (int idx = i; idx < n; idx += (idx & -idx)) {
            bit[idx] += x;
        }
    }

    T sum(int i) {
        T s(0);
        for (int idx = i; idx > 0; idx -= (idx & -idx)) {
            s += bit[idx];
        }
        return s;
    }

    // [l,r)
    T query(int l, int r) { return sum(r - 1) - sum(l - 1); }

    int lower_bound(int w) {
        if (w <= 0) {
            return 0;
        } else {
            int x = 0, r = 1;
            while (r < n) r = r << 1;
            for (int len = r; len > 0; len = len >> 1) {
                if (x + len < n && bit[x + len] < w) {
                    w -= bit[x + len];
                    x += len;
                }
            }
            return x + 1;
        }
    }
};

int main() {
    int q;
    cin >> q;
    BIT<int> bit(2e5);
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
