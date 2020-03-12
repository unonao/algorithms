/* tree_diamiter.cpp
    木の直径を求める

    verified: AOJ GRL_5_A: Diameter of a Tree
        http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_5_A
 */

#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int to;
    long long cost;
};
using Graph = vector<vector<Edge>>;

/* tree_diamiter : dfs を用いて重み付き木 T の直径を求める
*/
pair<long long, int> dfs(const Graph &G, int u, int par) {
    pair<long long, int> ret = make_pair(0LL, u);
    for (auto e : G[u]) {
        if (e.to == par) continue;
        auto next = dfs(G, e.to, u);
        next.first += e.cost;
        ret = max(ret, next);
    }
    return ret;
}
long long tree_diamiter(const Graph &G) {
    auto p = dfs(G, 0, -1);
    auto q = dfs(G, p.second, -1);
    return q.first;
}

int main() {
    int n;
    cin >> n;
    Graph T(n);
    for (int i = 0; i < n - 1; i++) {
        int s, t, w;
        cin >> s >> t >> w;
        T[s].push_back({t, w});
        T[t].push_back({s, w});
    }
    cout << tree_diamiter(T) << endl;
}
