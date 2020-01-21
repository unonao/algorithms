/* is_prime.cpp
    素数判定
*/
#include <bits/stdc++.h>
using namespace std;

/*  is_prime(n)
    入力：整数 n
    出力：nが素数かの真偽値
    計算量：O(√n)
*/
bool is_prime(long long n) { // is n prime or not
    for (long long i = 2; i * i <= n; i++) {
        if (n % i == 0)
            return false;
    }
    return true;
}

int main() {
    int N;
    cin >> N;
    cout << is_prime(N) << endl;
}
