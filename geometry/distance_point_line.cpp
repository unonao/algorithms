/* distance_point_line.cpp

    verified: [AtCoder] ARC 042 B - アリの高橋くん
        https://atcoder.jp/contests/arc042/tasks/arc042_b
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

using G = std::vector<P>;  // 単純多角形
const D PI = std::acos(-1);
const D EPS = 1e-10;
const D INF = 1e12;

// 比較
int sgn(D a) { return (a < -EPS) ? -1 : (a > EPS) ? 1 : 0; }

struct L : vector<P> {  // 線分, 直線
    L(const P& a, const P& b) { push_back(a), push_back(b); }
    friend ostream& operator<<(ostream& os, const L& l) { return os << l[0] << "-" << l[1]; }
};

struct C {  // 円(p:中心, r:半径)
    P p;
    double r;
    C(const P& p_, double r_) : p(p_), r(r_) {}
    friend ostream& operator<<(ostream& os, const C& cir) { return os << "p:" << cir.p << ", r:" << cir.r; }
};

/* dist(p,l) :
    点 p と直線 l との距離を求める
*/
D dist(P p, L l) {
    return abs(cross(l[1] - l[0], p - l[0])) / abs(l[1] - l[0]);
}

int main() {
    D x, y;
    cin >> x >> y;
    P s(x, y);
    int N;
    cin >> N;
    vector<P> ps(N);
    for (int i = 0; i < N; i++) {
        D a, b;
        cin >> a >> b;
        ps[i] = P(a, b);
    }
    ps.push_back(ps[0]);

    D ans = INF;
    for (int i = 0; i < N; i++) {
        ans = min(ans, dist(s, L(ps[i], ps[i + 1])));
    }
    cout << setprecision(12) << ans << endl;

    return 0;
}
