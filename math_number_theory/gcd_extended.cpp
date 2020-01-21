/* gcd_extended.cpp
    拡張Euclidの互除法で、2変数1次方程式の特殊解を求めるアルゴリズム
*/

#include <bits/stdc++.h>
using namespace std;

/*  gcd_ext(a,b,x,y)
    入力：整数 a, b
    出力：aとbの最大公約数
    副作用：xとyに、ax+by=gcd(a,b)の特殊解を格納する
    計算量：O(log(a)) (a>=bのとき)
*/
long long gcd_ext(long long a, long long b, long long &x, long long &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    } else {
        long long d = gcd_ext(b, a % b, y, x);
        y -= a / b * x;
        return d;
    }
}

int main() {
    long long x, y;
    int d = gcd_ext(111, 30, x, y);
    cout << d << endl;
    cout << x << ", " << y << endl;
}
