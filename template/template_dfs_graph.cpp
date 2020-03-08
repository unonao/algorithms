#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int to;
};
using Graph = vector<vector<Edge>>;

// 深さ優先探索
vector<bool> seen;  // 既に見たことがある頂点か記録
void dfs(const Graph &G, int v) {
    seen[v] = true;
    for (auto e : G[v]) {
        if (!seen[e.to]) {  // 訪問済みでなければ探索
            dfs(G, e.to);
        }
    }
}

int main() {
    // cin.tie(0);
    // ios::sync_with_stdio(false);

    int V, E;
    cin >> V >> E;
    int s, t;
    cin >> s >> t;

    Graph G(V);
    for (int i = 0; i < E; i++) {
        int a, b;
        cin >> a >> b;
        G[a].push_back({b});
        // G[b].push_back({a});
    }

    seen.assign(V, false);  // 初期化
    dfs(G, s);
    if (seen[t]) {
        cout << "yes" << endl;
    } else {
        cout << "no" << endl;
    }

    return 0;
}
