/* prime_factorization.cpp
    素因数分解
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
    if (n != 1)
        ret[n] = 1;
    return ret;
}

int main() {
    int N;
    cin >> N;
    map<long long, int> prime_fac = prime_factor(N);

    for (auto p : prime_fac) {
        cout << p.first << ":" << p.second << endl;
    }
    return 0;
}
