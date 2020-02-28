/* segment_tree.cpp
    任意のモノイドに対してセグメント木を構築する。

    モノイドXに対するセグメント木を構築するために、
        ・X上の二項演算 fx
        ・Xの単位元 ex
    を与える

    RMQ:
        auto fx = [](int x1, int x2) -> int { return min(x1, x2); };
        int ex = numeric_limits<int>::max();
        SegTree<int> rmq(n, fx, ex);
    区間gcd:
        using X = int;
        X ex = numeric_limits<int>::max();
        auto fx = [ex](X x1, X x2) -> X { return (x1 == ex) ? x2 : ((x2 == ex) ? x1 : gcd(x1, x2)); };
        SegTree<X> segGcd(n, fx, ex);

    unverified: AOJ DSL_2_A
        http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_A&lang=jp
 */

#include <bits/stdc++.h>
using namespace std;

/* SegTree<X>(n,fx,ex): モノイド(集合X, 二項演算fx, 単位元ex)についてサイズnで構築
    set(int i, X x), build(): i番目の要素をxにセット。まとめてセグ木を構築する。O(n)
    update(i,x): i 番目の要素を x に更新。O(log(n))
    query(a,b):  [a,b) 全てにfxを作用させた値を取得。O(log(n))
*/
template <typename X>
struct SegTree {
    using FX = function<X(X, X)>;
    int n;
    FX fx;
    const X ex;
    vector<X> dat;
    SegTree(int n_, FX fx_, X ex_) : n(), fx(fx_), ex(ex_), dat(n_ * 4, ex_) {
        int x = 1;
        while (n_ > x) {
            x *= 2;
        }
        n = x;
    }

    void set(int i, X x) { dat[i + n - 1] = x; }
    void build() {
        for (int k = n - 2; k >= 0; k--) dat[k] = fx(dat[2 * k + 1], dat[2 * k + 2]);
    }

    void update(int i, X x) {
        i += n - 1;
        dat[i] = x;
        while (i > 0) {
            i = (i - 1) / 2;  // parent
            dat[i] = fx(dat[i * 2 + 1], dat[i * 2 + 2]);
        }
    }

    // the minimum element of [a,b)
    X query(int a, int b) { return query_sub(a, b, 0, 0, n); }
    X query_sub(int a, int b, int k, int l, int r) {
        if (r <= a || b <= l) {
            return ex;
        } else if (a <= l && r <= b) {
            return dat[k];
        } else {
            X vl = query_sub(a, b, k * 2 + 1, l, (l + r) / 2);
            X vr = query_sub(a, b, k * 2 + 2, (l + r) / 2, r);
            return fx(vl, vr);
        }
    }
    /* debug */
    inline X operator[](int a) { return query(a, a + 1); }
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

    using X = int;
    auto fx = [](X x1, X x2) -> X { return min(x1, x2); };
    X ex = numeric_limits<int>::max();
    SegTree<X> rmq(n, fx, ex);

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
