/* tree_diamiter.cpp
    木の直径を求める

    verified: AOJ GRL_5_A: Diameter of a Tree
        http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_5_A
 */

#include <bits/stdc++.h>
using namespace std;

template <typename T>
struct Edge {
    int to;
    T cost;
};
using Graph = vector<vector<Edge<long long>>>;  // cost の型を long long に指定

/* tree_diamiter : dfs を用いて重み付き木 T の直径を求める
    計算量: O(N)
*/
template <typename T>
pair<T, int> dfs(const Graph &G, int u, int par) {  // 最遠点間距離と最遠点を求める
    pair<T, int> ret = make_pair((T)0, u);
    for (auto e : G[u]) {
        if (e.to == par) continue;
        auto next = dfs<T>(G, e.to, u);
        next.first += e.cost;
        ret = max(ret, next);
    }
    return ret;
}
template <typename T>
T tree_diamiter(const Graph &G) {
    pair<T, int> p = dfs<T>(G, 0, -1);
    pair<T, int> q = dfs<T>(G, p.second, -1);
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
    cout << tree_diamiter<long long>(T) << endl;
}
