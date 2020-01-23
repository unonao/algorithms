/* range_minimum_query.cpp
    セグメント木によって、区間での最小要素を管理します。

    内部では、木は配列として管理する。
    区間のサイズ n が2の倍数になるようINFで残りを埋めて、木の配列のサイズは 2*n になる。
    配列の i 番目の子は 2*i+1 or 2*i+2、親は (i-1)/2 になることを利用する。

    verified: AOJ DSL_2_A
        http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_A&lang=jp
 */

#include <bits/stdc++.h>
using namespace std;

/* RMQ：[0,n-1] について、区間ごとの最小値を管理する構造体
    update(i,x): i 番目の要素を x に更新。O(log(n))
    query(a,b): [a,b) での最小の要素を取得。O(log(n))
    ※ 先に値を set してから木を build すると、実はO(n)でできる(未作成)
*/
template <typename T>
struct RMQ {
    // the ranges of tree number is n*2-1
    // parent is (i-1)/2
    // child is 2*i+1 or 2*i+2
    const T INF = numeric_limits<T>::max();
    int n;
    vector<T> dat;
    RMQ(int n_) : n(), dat(n_ * 4, INF) {
        int x = 1;
        while (n_ > x) {
            x *= 2;
        }
        n = x;
    }

    void update(int i, T x) {
        i += n - 1;
        dat[i] = x;
        while (i > 0) {
            i = (i - 1) / 2;  // parent
            dat[i] = min(dat[i * 2 + 1], dat[i * 2 + 2]);
        }
    }

    // the minimum element of [a,b)
    T query(int a, int b) { return query_sub(a, b, 0, 0, n); }
    T query_sub(int a, int b, int k, int l, int r) {
        if (r <= a || b <= l) {
            return INF;
        } else if (a <= l && r <= b) {
            return dat[k];
        } else {
            T vl = query_sub(a, b, k * 2 + 1, l, (l + r) / 2);
            T vr = query_sub(a, b, k * 2 + 2, (l + r) / 2, r);
            return min(vl, vr);
        }
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
