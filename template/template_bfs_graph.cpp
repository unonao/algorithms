#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int to;
};
using Graph = vector<vector<Edge>>;

// 幅優先探索
vector<int> dist;  // 始点からの距離を記録
void bfs(const Graph &G, int s) {
    const int INF = 1e8;
    dist.assign((int)G.size(), INF);  // 初期化

    queue<int> que;
    que.emplace(s);  // sから探索する
    dist[s] = 0;
    while (que.size() != 0) {   // 幅優先探索
        int now = que.front();  // 現在の状態
        que.pop();
        for (auto e : G[now]) {
            if (dist[e.to] == INF) {  // 未探索の時のみ行う
                dist[e.to] = dist[now] + 1;
                que.emplace(e.to);
            }
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

    bfs(G, s);
    cout << dist[t] << endl;
    if (dist[t] > 0) {
        cout << "yes" << endl;
    } else {
        cout << "no" << endl;
    }

    return 0;
}
