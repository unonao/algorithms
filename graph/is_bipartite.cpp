/* is_bipartite.cpp
    二部グラフ判定を深さ優先探索（DFS）で行う

    verified: AtCoder CODE FESTIVAL 2017 qual B  C - 3 Steps
        https://code-festival-2017-qualb.contest.atcoder.jp/tasks/code_festival_2017_qualb_c
*/
#include <bits/stdc++.h>
using namespace std;

struct Edge {
    long long to;
};
using Graph = vector<vector<Edge>>;
using P = pair<long, long>;

bool dfs(const Graph &G, int v, int c, P &num, vector<int> &color) {
    bool ret = true;
    color[v] = c;
    if (c == 1) {
        num.first++;
    } else if (c == -1) {
        num.second++;
    }
    for (auto e : G[v]) {
        if (color[e.to] == 0 && !dfs(G, e.to, -c, num, color)) {
            ret = false;
        } else if (color[e.to] == c) {
            ret = false;
        }
    }
    return ret;
}

/* is_bipartite(G,nums): 二部グラフかどうか判定
    計算量：O(|V|+|E|)
    副作用：
        nums[i] := i 番目の連結成分の {左ノード数, 右ノード数}とする c = 1: 左、-1: 右」
*/
bool is_bipartite(const Graph &G, vector<P> &nums) {
    bool ret = true;
    int N = G.size();
    vector<int> color(N, 0);
    for (int i = 0; i < N; i++) {
        if (color[i] == 0) {
            P num = {0, 0};
            if (!dfs(G, i, 1, num, color)) {
                ret = false;
            }
            nums.push_back(num);
        }
    }
    return ret;
}

int main() {
    long long N, M;
    cin >> N >> M;
    Graph G(N);
    for (int i = 0; i < M; i++) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        G[a].push_back({b});
        G[b].push_back({a});
    }

    vector<P> nums;
    if (is_bipartite(G, nums)) {  // 完全二部グラフ
        long long ans = 0;
        for (auto i : nums) {  // 問題の制約から1つだけなはず
            ans += i.first * i.second;
        }
        cout << ans - M << endl;
    } else {  // 完全グラフ
        cout << N * (N - 1) / 2 - M << endl;
    }
    return 0;
}
