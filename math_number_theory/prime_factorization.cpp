/* prime_factorization.cpp
    素因数分解

    verified: AOJ NTL_1_A
        http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=NTL_1_A&lang=ja
*/
#include <bits/stdc++.h>
using namespace std;

/*  prime_factor(n)
    入力：整数 n
    出力：nの素因数分解
    計算量：O(√n)前後
*/
map<long long, int> prime_factor(long long n) {
    map<long long, int> ret;
    for (long long i = 2; i * i <= n; i++) {
        while (n % i == 0) {
            ret[i]++;
            n /= i;
        }
    }
    if (n != 1) ret[n] = 1;
    return ret;
}

int main() {
    int N;
    cin >> N;
    map<long long, int> prime_fac = prime_factor(N);

    cout << N << ":";
    for (auto p : prime_fac) {
        for (int i = 0; i < p.second; i++) {
            cout << " " << p.first;
        }
    }
    cout << endl;
    return 0;
}
