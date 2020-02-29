/* prime_table.cpp
    エラトステネスの篩で素数かどうかの情報を保存

    verified: AOJ Prime Gap
        http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1276#
*/
#include <bits/stdc++.h>
using namespace std;

/*  prime_table(n)
    入力：整数 n
    出力：nまでの数字が素数か判定したテーブル
    計算量：O(nloglogn)
*/
vector<bool> prime_table(int n) {
    vector<bool> prime(n + 1, true);
    if (n >= 0) prime[0] = false;
    if (n >= 1) prime[1] = false;
    for (int i = 2; i * i <= n; i++) {
        if (!prime[i]) continue;
        for (int j = i * i; j <= n; j += i) {
            prime[j] = false;
        }
    }
    return prime;
}

int main() {
    vector<bool> p_table = prime_table(2000000);
    int N;
    while (cin >> N) {
        if (N == 0) break;
        int pre = N, next = N;
        while (!p_table[pre]) pre--;
        while (!p_table[next]) next++;
        cout << next - pre << endl;
    }
}
