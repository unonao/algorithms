/* topological_sort_DFS.cpp

    verified: AOJ GRL_4_B Topological Sort
    http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_4_B&lang=ja
*/

#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int to;
};
using Graph = vector<vector<Edge>>;

/* topo_sort(G): グラフG をトポロジカルソート
    返り値: トポロジカルソートされた頂点番号
    計算量: O(|E|+|V|)
    閉路の存在は分からない
    （大きなグラフではスタックオーバーフローの可能性があるので、dfsではなくbfsの方が良い）
 */
void dfs(const Graph &G, int v, vector<bool> &used, vector<int> &ans) {
    used[v] = true;
    for (auto e : G[v]) {
        if (!used[e.to]) {
            dfs(G, e.to, used, ans);
        }
    }
    ans.push_back(v);  // 帰りがけにpush_back
}
vector<int> topo_sort(const Graph &G) {  // bfs
    vector<int> ans;
    int n = (int)G.size();
    vector<bool> used(n, false);
    for (int v = 0; v < n; v++) {  // 未探索の頂点ごとにDFS
        if (!used[v]) dfs(G, v, used, ans);
    }
    reverse(ans.begin(), ans.end());  // 逆向きなのでひっくり返す
    return ans;
}

int main() {
    // cin.tie(0);
    // ios::sync_with_stdio(false);

    int V, E;
    cin >> V >> E;
    vector<int> s(E), t(E);
    for (int i = 0; i < E; i++) {
        cin >> s.at(i) >> t.at(i);
    }

    Graph G(V);
    for (int i = 0; i < E; i++) {
        G[s[i]].push_back({t[i]});
    }
    vector<int> sorted = topo_sort(G);

    for (auto v : sorted) {
        cout << v << endl;
    }

    return 0;
}
