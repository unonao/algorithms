#include <bits/stdc++.h>
#define LOOP(n) for (int _i = 0; _i < (n); _i++)
#define REP(i, n) for (int i = 0; i < (n); ++i)
#define RREP(i, n) for (int i = (n); i >= 0; --i)
#define FOR(i, r, n) for (int i = (r); i < (n); ++i)
#define ALL(obj) begin(obj), end(obj)
#define debug(x) cerr << #x << ": " << x << '\n'

using namespace std;
using ll = long long;
using ull = unsigned long long;

// 1次元 vector
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
template <class T>  // 2次元 vector
ostream &operator<<(ostream &s, vector<vector<T>> vec2) {
    for (int i = 0; i < (int)vec2.size(); ++i) {
        s << vec2[i];
    }
    return s;
}

// set
template <class T>
ostream &operator<<(ostream &s, set<T> se) {
    for (auto i : se) {
        s << "(" << i << ") ";
    }
    return s << endl;
}

// map
template <class T1, class T2>
ostream &operator<<(ostream &s, map<T1, T2> ma) {
    for (auto p : ma) {
        s << "(" << p.first << "->" << p.second << ") ";
    }
    return s << endl;
}

// pair
template <class T1, class T2>
ostream &operator<<(ostream &s, pair<T1, T2> p) {
    s << "(" << p.first << "->" << p.second << ") ";
    return s << endl;
}

int dp[1000][1000];
// dp[i][j] should be defined!
void print_2d_dp(int H, int W) {
    for (int i = 0; i < H; i++) {
        cout << i << ": ";
        for (int j = 0; j < W; j++) cout << dp[i][j] << " ";
        cout << endl;
    }
}

int main() {
    vector<int> A = {1, 2, 3, 4};
    vector<vector<int>> B = {{1, 2, 2}, {3, 4, 5}, {6, 7}};
    cerr << A;
    cerr << B;
    set<int> se;
    se.insert(1);
    se.insert(100);
    map<int, int> ma;
    ma[1] = 10;
    ma[23] = 1;
    cerr << se;
    cerr << ma;
    cerr << make_pair(1, 4);
}
