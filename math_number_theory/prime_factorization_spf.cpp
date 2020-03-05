/* prime_factorization_spf.cpp
    前処理付き素因数分解

    verified: codeforces #511(Div.2) C. Enlarge GCD
        https://codeforces.com/contest/1047/problem/C
*/
#include <bits/stdc++.h>
using namespace std;

/*  PrimeFact
    init(N): 初期化。O(N log log N)
    get(n): クエリ。素因数分解を求める。O(log n)
 */
template <typename T>
struct PrimeFact {
    vector<T> spf;
    PrimeFact(T N) { init(N); }
    void init(T N) {
        spf.assign(N + 1, 0);
        for (T i = 0; i <= N; i++) spf[i] = i;
        for (T i = 2; i * i <= N; i++) {
            if (spf[i] == i) {
                for (T j = i * i; j <= N; j += i) {
                    if (spf[j] == j) {
                        spf[j] = i;
                    }
                }
            }
        }
    }
    map<T, T> get(T n) {
        map<T, T> m;
        while (n != 1) {
            m[spf[n]]++;
            n /= spf[n];
        }
        return m;
    }
};

int gcd(int a, int b) {
    if (b == 0) {
        return a;
    } else {
        return gcd(b, a % b);
    }
}

int main() {
    int N;
    cin >> N;
    vector<int> a(N);
    for (int i = 0; i < N; i++) {
        cin >> a.at(i);
    }

    int d = a[0];
    for (int i = 1; i < N; i++) {
        d = gcd(d, a[i]);
    }

    PrimeFact<int> pf(15000000);

    map<int, int> cnt;

    for (int i = 0; i < N; i++) {
        map<int, int> pf_i = pf.get(a[i] / d);
        for (auto p : pf_i) {
            cnt[p.first]++;
        }
    }

    int ans = -1;
    for (auto p : cnt) {
        // cout << p.first << " " << p.second << endl;
        if (ans < p.second) {
            ans = p.second;
        }
    }
    if (ans != -1) {
        cout << N - ans << endl;
    } else {
        cout << -1 << endl;
    }
    return 0;
}
