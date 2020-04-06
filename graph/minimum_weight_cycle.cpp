/* minimum_weight_cycle.cpp
    グラフの最小の重みの閉路を求める
    最短距離を求めるのにダイクストラ法を使用

    verified: [AtCoder] ABC 142 F. Pure
        https://atcoder.jp/contests/abc142/tasks/abc142_f
*/

#include <bits/stdc++.h>
using namespace std;

template <typename T>
struct Edge {
    int to;
    T cost;
};
using Graph = vector<vector<Edge<long long>>>;  // 距離/コストの型 T を指定する
const long long INF = (1LL << 60);              // 型 T のINF (完全な最大値は取らないように)

/* dijkstra(G,s,dis,prev)
    入力：グラフ G, 開始点 s, 距離を格納する dis, 最短経路の前の点を記録するprev
    計算量：O(|E|log|V|)
    副作用：dis, prevが書き換えられる
*/
template <typename T>
void dijkstra(const Graph &G, int s, vector<T> &dis, vector<int> &prev) {
    using P = pair<T, int>;
    int N = G.size();
    dis.resize(N, INF);
    prev.resize(N, -1);
    priority_queue<P, vector<P>, greater<P>> pq;  // the least element is top. first:cost, second: node
    dis[s] = 0;
    pq.emplace(dis[s], s);
    while (!pq.empty()) {
        P p = pq.top();  // the least element
        pq.pop();
        int v = p.second;
        if (dis[v] < p.first) {
            continue;
        }
        for (auto &e : G[v]) {
            if (dis[e.to] > dis[v] + e.cost) {
                dis[e.to] = dis[v] + e.cost;
                prev[e.to] = v;
                pq.emplace(dis[e.to], e.to);
            }
        }
    }
}

/* get_path(pre, t)
    入力：得た pre, ゴール t
    出力： t への最短路のパス
*/
vector<int> get_path(const vector<int> &pre, int t) {
    vector<int> path;
    for (int cur = t; cur != -1; cur = pre[cur]) {
        path.push_back(cur);
    }
    reverse(path.begin(), path.end());
    return path;
}

vector<int> min_cycle;  // 最小の閉路に含まれる頂点
/* minimum_weight_cycle
    出力：閉路の重みの最小値、閉路がなければ INF
    最小の閉路に含まれる頂点は min_cycleに格納される
    計算量:
      重み付きグラフ(ダイクストラ法): O(EElogV)
*/
template <typename T>
T minimum_weight_cycle(Graph &G) {
    int V = (int)G.size();
    T ans = INF;
    for (int v = 0; v < V; v++) {
        for (int i = 0; i < (int)G[v].size(); i++) {
            Edge<T> e = G[v][i];
            G[v].erase(G[v].begin() + i);  // e を消す
            vector<T> dist;
            vector<int> pre;
            dijkstra<T>(G, e.to, dist, pre);  // 最短距離を求める
            if (ans > dist[v] + e.cost) {
                ans = dist[v] + e.cost;
                min_cycle = get_path(pre, v);
            }
            G[v].insert((G[v].begin() + i), e);  // e を戻す
        }
    }
    return ans;
}

int main() {
    int V, E;
    cin >> V >> E;
    if (E == 0) {
        cout << -1 << endl;
        return 0;
    }
    Graph G(V);
    for (int i = 0; i < E; i++) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        G[a].push_back({b, 1LL});
        // G[b].push_back({a});
    }

    long long ans = minimum_weight_cycle<long long>(G);

    if (ans == INF) {
        cout << -1 << endl;
        return 0;
    } else {
        cout << ans << "\n";
        for (auto i : min_cycle) {
            cout << i + 1 << "\n";
        }
    }

    return 0;
}
