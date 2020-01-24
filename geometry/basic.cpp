/* basic.cpp 未作成
    幾何ライブラリの基本ファイル

    基本思想
        ・complex型を利用して簡潔に
        ・double型で計算。整数も double で計算して EPS を適切に設定して対処する

    参考：
    https://github.com/drken1215/algorithm
    https://dai1741.github.io/maximum-algo-2012/cpp/geometry/geometries2d.h
    http://www.prefield.com/algorithm/
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

int main() {
    P a(1.0, 2.0), b(2.0, 5.0);
    double r = 1.0;
    C cir(a, r);
    cout << cir << endl;
    L l(a, b);
    cout << l << endl;
    return 0;
}
