/* is_prime.cpp
    素数判定

    verified: AOJ ALDS1_1_C Prime Numbers
        http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_1_C&lang=ja
*/
#include <bits/stdc++.h>
using namespace std;

/*  is_prime(n)
    入力：整数 n
    出力：nが素数かの真偽値
    計算量：O(√n)
*/
bool is_prime(long long n) {  // is n prime or not
    for (long long i = 2; i * i <= n; i++) {
        if (n % i == 0) return false;
    }
    return true;
}

int main() {
    int N;
    cin >> N;
    int ans = 0;
    for (int i = 0; i < N; i++) {
        int k;
        cin >> k;
        if (is_prime(k)) ans++;
    }
    cout << ans << endl;
}
