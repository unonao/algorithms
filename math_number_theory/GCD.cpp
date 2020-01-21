/* GCD.cpp
    Euclidの互除法で、最大公約数を求めるアルゴリズム
*/

#include <bits/stdc++.h>
using namespace std;

/*  GCD(a,b)
    入力：整数 a, b
    出力：aとbの最大公約数
*/
long long GCD(long long a, long long b) {
    if (b == 0) {
        return a;
    } else {
        return GCD(b, a % b);
    }
}

int main() {
    int d = GCD(111, 30);
    cout << d << endl;
}
