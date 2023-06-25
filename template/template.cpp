#include <bits/stdc++.h>
/*
// using ASL (use make)
#include <atcoder/all>
using namespace atcoder;
*/
#define ALL(obj) begin(obj), end(obj)
#define debug(x) cerr << #x << ": " << x << '\n'
using namespace std;
// 1次元 vector print
template <class T>
ostream &operator<<(ostream &s, vector<T> vec) {
    for (int i = 0; i < (int)vec.size(); ++i) {
        if (i > 0) {
            s << " ";
        }
        s << vec[i];
    }
    return s << endl;
}
// 2次元 vector print
template <class T>
ostream &operator<<(ostream &s, vector<vector<T>> vec2) {
    for (int i = 0; i < (int)vec2.size(); ++i) {
        s << vec2[i];
    }
    return s;
}
template <class T>
vector<T> make_vec(size_t a) {
    return vector<T>(a);
}
template <class T, class... Ts>
auto make_vec(size_t a, Ts... ts) {
    return vector<decltype(make_vec<T>(ts...))>(a, make_vec<T>(ts...));
}
template <class T>
bool chmax(T &a, const T &b) {
    if (a < b) {
        a = b;
        return 1;
    }
    return 0;
}
template <class T>
bool chmin(T &a, const T &b) {
    if (b < a) {
        a = b;
        return 1;
    }
    return 0;
}

using ll = long long;
using ull = unsigned long long;
const int INF = 1e9;
// const int MOD = 1e9 + 7;

int main() {
}
