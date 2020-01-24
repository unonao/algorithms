/* ccw.cpp
    3点の位置関係を求める

    verified:
        AOJ Course CGL_1_C Points/Vectors - Counter-Clockwise
        http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_1_C&lang=jp
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

/* ccw(a,b,c)
    出力:
    1: a-bから見てcは反時計, -1: a-bから見てcは時計
    2: c-a-bで直線, -2: a-b-cで直線, 0: a-c-bで直線
*/
int ccw(const P& a, const P& b, const P& c) {
    if (cross(b - a, c - a) > EPS) return 1;         // 1: a-bから見てcは反時計
    if (cross(b - a, c - a) < -EPS) return -1;       //-1: a-bから見てcは時計
    if (dot(b - a, c - a) < -EPS) return 2;          // 2: c-a-bで直線
    if (norm(b - a) < norm(c - a) - EPS) return -2;  //-2: a-b-cで直線
    return 0;                                        // 0: a-c-bで直線
}

int main() {
    double px, py;
    cin >> px >> py;
    P a(px, py);
    cin >> px >> py;
    P b(px, py);
    int q;
    cin >> q;
    vector<P> cs(q);
    for (int i = 0; i < q; i++) {
        cin >> px >> py;
        P c(px, py);
        cs[i] = c;
    }
    for (int i = 0; i < q; i++) {
        P c = cs[i];
        if (ccw(a, b, c) == 1) {
            cout << "COUNTER_CLOCKWISE" << endl;
        } else if (ccw(a, b, c) == -1) {
            cout << "CLOCKWISE" << endl;
        } else if (ccw(a, b, c) == 2) {
            cout << "ONLINE_BACK" << endl;
        } else if (ccw(a, b, c) == -2) {
            cout << "ONLINE_FRONT" << endl;
        } else if (ccw(a, b, c) == 0) {
            cout << "ON_SEGMENT" << endl;
        }
    }
    return 0;
}
