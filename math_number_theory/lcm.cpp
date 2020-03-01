/* lcm.cpp
    gcdを利用して最小公倍数を求めるアルゴリズム

    verified: AtCoder ABC070 C - Multiple Clocks
        https://atcoder.jp/contests/abc070/tasks/abc070_c
*/

#include <bits/stdc++.h>
using namespace std;

long long gcd(long long a, long long b) {
    if (b == 0) {
        return a;
    } else {
        return gcd(b, a % b);
    }
}

/*  lcm (a, b) : 2整数版
    入力：整数 a, b
    出力：aとbの最小公倍数
*/
long long lcm(long long a, long long b) {
    long long d = gcd(a, b);
    return a / d * b;
}

/* lcm (vec) : ベクトルでの多整数版
    入力：整数のベクトル vec
    出力：すべての要素の最小公倍数
    注意：最小公倍数がオーバーフローする時は素因数分解を使う
*/
long long lcm(const vector<long long> &vec) {
    long long l = vec[0];
    for (int i = 0; i < (int)vec.size() - 1; i++) {
        l = lcm(l, vec[i + 1]);
    }
    return l;
}

int main() {
    int N;
    cin >> N;
    vector<long long> A(N);
    for (int i = 0; i < N; i++) {
        cin >> A.at(i);
    }
    cout << lcm(A) << endl;
}
