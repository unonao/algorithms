#include <bits/stdc++.h>
#define LOOP(n) for (int _i = 0; _i < (n); _i++)
#define REP(i, n) for (int i = 0; i < (n); ++i)
#define RREP(i, n) for (int i = (n); i >= 0; --i)
#define FOR(i, r, n) for (int i = (r); i < (n); ++i)
#define ALL(obj) begin(obj), end(obj)
using namespace std;
using ll = long long;
using ull = unsigned long long;

int dp[1000][1000];
// dp[i][j] should be defined!
void print_2d_dp(int H, int W) {
    for (int i = 0; i < H; i++) {
        cout << i << ": ";
        for (int j = 0; j < W; j++) cout << dp[i][j] << " ";
        cout << endl;
    }
}

template <class T>
void print_2d(const vector<vector<T>> &A) {
    for (int i = 0; i < (int)A.size(); i++) {
        cout << i << ": ";
        for (int j = 0; j < (int)A[i].size(); j++) cout << A[i][j] << " ";
        cout << endl;
    }
}
