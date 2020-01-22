/* lcm_prime.cpp
    素因数分解の形で最小公倍数を求めるアルゴリズム
    （オーバーフローする場合などに使える）
*/

#include <bits/stdc++.h>
using namespace std;

map<long long, int> prime_factor(long long n) {  // 素因数分解
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

/* lcm_prime(vector<long long> vec)
    入力：整数のベクトル vec
    出力：すべての要素の最小公倍数を素因数分解したmap
*/
map<long long, int> lcm_prime(const vector<long long> &vec) {
    map<long long, int> ret;
    for (int i = 0; i < vec.size(); i++) {
        map<long long, int> prime_fac = prime_factor(vec[i]);
        for (auto p : prime_fac) {
            if (ret.find(p.first) != ret.end()) {
                ret[p.first] = max(ret[p.first], p.second);
            } else {
                ret[p.first] = p.second;
            }
        }
    }
    return ret;
}

int main() {
    int N;
    cin >> N;
    vector<long long> A(N);
    for (int i = 0; i < N; i++) {
        cin >> A.at(i);
    }
    map<long long, int> lp = lcm_prime(A);

    for (auto p : lp) {
        cout << p.first << ":" << p.second << endl;
    }
    return 0;
}
