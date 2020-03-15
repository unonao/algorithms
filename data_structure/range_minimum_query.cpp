/* range_minimum_query.cpp
    セグメント木によって、区間での最小要素を管理する。

    verified: AOJ DSL_2_A
        http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_A&lang=jp
    verified: codeforces #622 div2
        https://codeforces.com/contest/1313/submission/71736877
 */

#include <bits/stdc++.h>
using namespace std;

/* RMQ：[0,n-1] について、区間ごとの最小値を管理する構造体
    set(int i, T x), build(): i番目の要素をxにセット。まとめてセグ木を構築する。O(n)
    update(i,x): i 番目の要素を x に更新。O(log(n))
    query(a,b): [a,b) での最小の要素を取得。O(log(n))
    find_rightest(a,b,x): [a,b) で x以下の要素を持つ最右位置を求める。O(log(n))
    find_leftest(a,b,x): [a,b) で x以下の要素を持つ最左位置を求める。O(log(n))
*/
template <typename T>
struct RMQ {
    const T e = numeric_limits<T>::max();
    function<T(T, T)> fx = [](T x1, T x2) -> T { return min(x1, x2); };
    int n;
    vector<T> dat;
    RMQ(int n_) : n(), dat(n_ * 4, e) {
        int x = 1;
        while (n_ > x) {
            x *= 2;
        }
        n = x;
    }

    void set(int i, T x) { dat[i + n - 1] = x; }
    void build() {
        for (int k = n - 2; k >= 0; k--) dat[k] = fx(dat[2 * k + 1], dat[2 * k + 2]);
    }

    void update(int i, T x) {
        i += n - 1;
        dat[i] = x;
        while (i > 0) {
            i = (i - 1) / 2;  // parent
            dat[i] = fx(dat[i * 2 + 1], dat[i * 2 + 2]);
        }
    }

    // the minimum element of [a,b)
    T query(int a, int b) { return query_sub(a, b, 0, 0, n); }
    T query_sub(int a, int b, int k, int l, int r) {
        if (r <= a || b <= l) {
            return e;
        } else if (a <= l && r <= b) {
            return dat[k];
        } else {
            T vl = query_sub(a, b, k * 2 + 1, l, (l + r) / 2);
            T vr = query_sub(a, b, k * 2 + 2, (l + r) / 2, r);
            return fx(vl, vr);
        }
    }

    T find_rightest(int a, int b, int x) { return find_nearest_sub(a, b, x, 0, 0, n, true); }
    T find_leftest(int a, int b, int x) { return find_nearest_sub(a, b, x, 0, 0, n, false); }
    T find_nearest_sub(int a, int b, int x, int k, int l, int r, bool is_right) {
        if (dat[k] > x || r <= a || b <= l) {  // 自分の値がxより大きい or [a,b)が[l,r)の範囲外ならreturn -1
            return -1;
        } else if (k >= n - 1) {  // 自分が葉ならその位置をreturn
            return (k - (n - 1));
        } else {
            if (is_right) {
                int vr = find_nearest_sub(a, b, x, 2 * k + 2, (l + r) / 2, r, is_right);
                if (vr != -1) {  // 右の部分木を見て-1以外ならreturn
                    return vr;
                } else {  // 左の部分木を見て値をreturn
                    return find_nearest_sub(a, b, x, 2 * k + 1, l, (l + r) / 2, is_right);
                }
            } else {
                int vl = find_nearest_sub(a, b, x, 2 * k + 1, l, (l + r) / 2, is_right);
                if (vl != -1) {  // 左の部分木を見て-1以外ならreturn
                    return vl;
                } else {  // 右の部分木を見て値をreturn
                    return find_nearest_sub(a, b, x, 2 * k + 2, (l + r) / 2, r, is_right);
                }
            }
        }
    }
    /* debug */
    inline T operator[](int a) { return query(a, a + 1); }
    void print() {
        for (int i = 0; i < n; ++i) {
            cout << (*this)[i];
            if (i != n) cout << ",";
        }
        cout << endl;
    }
};

int main() {
    int n, q;
    cin >> n >> q;
    RMQ<int> rmq(n);
    vector<int> c(q), x(q), y(q);
    for (int i = 0; i < q; i++) {
        cin >> c.at(i) >> x.at(i) >> y.at(i);
    }

    for (int i = 0; i < q; i++) {
        if (c[i] == 0) {
            rmq.update(x[i], y[i]);
        } else if (c[i] == 1) {
            cout << rmq.query(x[i], y[i] + 1) << endl;
        }
    }
    return 0;
}
