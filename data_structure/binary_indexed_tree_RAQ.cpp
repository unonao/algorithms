/* binary_indexed_tree_RAQ.cpp
    BIT を用いた Range Add Query (RAQ)。区間への更新を行える

    verified: AOJ DSL_2_E
        http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_E&lang=ja
*/

#include <bits/stdc++.h>
using namespace std;

/* BIT: 区間和の更新や計算を行う構造体
    初期値は a_1 = a_2 = ... = a_n = 0
    ・add(l,r,x): [l,r) に x を加算する
    ・sum(i): a_1 + a_2 + ... + a_i を計算する
    ・query(l,r): [l,r) の区間の和を求める
    計算量は全て O(logn)
*/
template <typename T>
struct BIT {
    int n;             // 要素数
    vector<T> bit[2];  // データの格納先
    BIT(int n_) { init(n_); }
    void init(int n_) {
        n = n_ + 1;
        for (int p = 0; p < 2; p++) bit[p].assign(n, 0);
    }

    void add_sub(int p, int i, int x) {
        if (i == 0) {
            return;
        } else {
            for (int idx = i; idx < n; idx += (idx & -idx)) {
                bit[p][idx] += x;
            }
        }
    }
    void add(int l, int r, T x) {  // [l,r) に加算
        add_sub(0, l, -x * (l - 1));
        add_sub(0, r, x * (r - 1));
        add_sub(1, l, x);
        add_sub(1, r, -x);
    }

    T sum_sub(int p, int i) {
        T s(0);
        for (int idx = i; idx > 0; idx -= (idx & -idx)) {
            s += bit[p][idx];
        }
        return s;
    }
    T sum(int i) { return sum_sub(0, i) + sum_sub(1, i) * i; }

    // [l,r) の区間和を取得
    T query(int l, int r) { return sum(r - 1) - sum(l - 1); }
};

int main() {
    int n, q;
    cin >> n >> q;
    BIT<int> raq(n);

    vector<int> ans;
    for (int i = 0; i < q; i++) {
        int c;
        cin >> c;
        if (c == 0) {
            int s, t, x;
            cin >> s >> t >> x;
            raq.add(s, t + 1, x);
        } else if (c == 1) {
            int i;
            cin >> i;
            ans.push_back(raq.query(i, i + 1));
        }
    }
    for (auto i : ans) {
        cout << i << endl;
    }

    return 0;
}
