/* is_contain_in_triangle.cpp
    点が三角形に含まれているか判定する

    verified:
        AOJ 0143
        http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0143
*/

#include <bits/stdc++.h>
using namespace std;

using D = double;

// P: 点,座標
using P = std::complex<D>;
namespace std {
bool operator<(const P& a, const P& b) { return real(a) != real(b) ? real(a) < real(b) : imag(a) < imag(b); }
bool operator>(const P& a, const P& b) { return real(a) != real(b) ? real(a) > real(b) : imag(a) > imag(b); }
}  // namespace std
D dot(const P& a, const P& b) { return real(conj(a) * b); }    // 内積
D cross(const P& a, const P& b) { return imag(conj(a) * b); }  // 外積
D norm(const P& a) { return dot(a, a); }

const D PI = std::acos(-1);
const D EPS = 1e-10;
const D INF = 1e12;

int sgn(D a) { return (a < -EPS) ? -1 : (a > EPS) ? 1 : 0; }  // 比較

/* ccw(a,b,c)
    出力:
    1: a-bから見てcは反時計, -1: a-bから見てcは時計
    2: c-a-bで直線, -2: a-b-cで直線, 0: a-c-bで直線
*/
int ccw(const P& a, const P& b, const P& c) {
    if (sgn(cross(b - a, c - a)) == 1) return 1;         // 1: a-bから見てcは反時計
    if (sgn(cross(b - a, c - a)) == -1) return -1;       //-1: a-bから見てcは時計
    if (sgn(dot(b - a, c - a)) == -1) return 2;          // 2: c-a-bで直線
    if (sgn(norm(c - a) - norm(b - a)) == 1) return -2;  //-2: a-b-cで直線
    return 0;                                            // 0: a-c-bで直線
}

/* is_contain_in_triangle(p, a,b,c)
    p が 三角形abc に含まれていれば true を返す
*/
bool is_contain_in_triangle(const P& p, const P& a, const P& b, const P& c) {
    int r1 = ccw(p, b, c), r2 = ccw(p, c, a), r3 = ccw(p, a, b);
    if (r1 == r2 && r2 == r3 && (r1 == 1 || r1 == -1)) return true;
    return false;
}

int main() {
    int n;
    cin >> n;
    vector<int> ans(n);
    for (int i = 0; i < n; i++) {
        D x, y;
        P p[3];
        for (int j = 0; j < 3; j++) {
            cin >> x >> y;
            P tmp(x, y);
            p[j] = tmp;
        }
        cin >> x >> y;
        P k(x, y);
        cin >> x >> y;
        P s(x, y);

        if (is_contain_in_triangle(k, p[0], p[1], p[2]) ^ is_contain_in_triangle(s, p[0], p[1], p[2])) {
            ans[i] = 1;
        } else {
            ans[i] = 0;
        }
    }

    for (int i = 0; i < n; i++) {
        if (ans[i]) {
            cout << "OK\n";
        } else {
            cout << "NG\n";
        }
    }
    return 0;
}
