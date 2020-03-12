/* dijkstra.cpp
    ダイクストラ法で、ある頂点から各頂点への最短距離を求めるアルゴリズム
    負の辺が含まれる場合はうまく計算出来ないので、ベルマンフォード法を用いる

    verified: AOJ GRL_1_A
        http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_1_A&lang=jp
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

/* get_path(prev, t)
    入力：dijkstra で得た prev, ゴール t
    出力： t への最短路のパス
*/
vector<int> get_path(const vector<int> &prev, int t) {
    vector<int> path;
    for (int cur = t; cur != -1; cur = prev[cur]) {
        path.push_back(cur);
    }
    reverse(path.begin(), path.end());
    return path;
}

int main() {
    int V, E, r;
    cin >> V >> E >> r;
    Graph G(V);
    for (int i = 0; i < E; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        G[a].push_back({b, c});
    }
    vector<long long> dis;
    vector<int> prev;
    dijkstra(G, r, dis, prev);
    for (int i = 0; i < V; i++) {
        if (dis[i] != INF) {
            cout << dis[i] << endl;
        } else {
            cout << "INF" << endl;
        }
    }

    return 0;
}
