/* low_link.cpp
    グラフの関節点・橋の列挙をする

    verified: AOJ GRL_3_A
        http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_3_A
    verified: AOJ GRL_3_B
        http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_3_B
*/
#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int to;
};
using Graph = vector<vector<Edge>>;
using P = pair<long, long>;

/* Lowlink: グラフの関節点・橋を列挙する構造体
    作成: O(E+V)
    関節点の集合: vector<int> aps
    橋の集合: vector<P> bridges
*/
struct LowLink {
    vector<int> aps;  // articulation points
    vector<P> bridges;

    const Graph &G;
    vector<int> used, ord, low;
    LowLink(const Graph &G_) : G(G_) {
        used.assign(G.size(), 0);
        ord.assign(G.size(), 0);
        low.assign(G.size(), 0);
        int k = 0;
        for (int i = 0; i < G.size(); i++) {
            if (!used[i]) k = dfs(i, k, -1);
        }
    }

    int dfs(int id, int k, int par) {
        used[id] = true;
        ord[id] = k++;
        low[id] = ord[id];
        bool is_aps = false;
        int count = 0;
        for (auto &e : G[id]) {
            if (!used[e.to]) {
                count++;
                k = dfs(e.to, k, id);
                low[id] = min(low[id], low[e.to]);
                if (par != -1 && ord[id] <= low[e.to]) is_aps = true;
                if (ord[id] < low[e.to]) bridges.emplace_back(min(id, e.to), max(id, e.to));
            } else if (e.to != par) {
                low[id] = min(low[id], ord[e.to]);
            }
        }
        if (par == -1 && count >= 2) is_aps = true;
        if (is_aps) aps.push_back(id);
        return k;
    }
};

/*
//verified: AOJ GRL_3_A
//    http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_3_A
int main() {
    long long V, E;
    cin >> V >> E;
    Graph G(V);
    for (int i = 0; i < E; i++) {
        int s, t;
        cin >> s >> t;
        G[s].push_back({t});
        G[t].push_back({s});
    }

    LowLink lowlink(G);

    sort(lowlink.aps.begin(), lowlink.aps.end());
    for (auto i : lowlink.aps) {
        cout << i << endl;
    }
    return 0;
}
*/

/*
// verified: AOJ GRL_3_B
//    http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_3_B
*/
int main() {
    long long V, E;
    cin >> V >> E;
    Graph G(V);
    for (int i = 0; i < E; i++) {
        int s, t;
        cin >> s >> t;
        G[s].push_back({t});
        G[t].push_back({s});
    }

    LowLink lowlink(G);

    sort(lowlink.bridges.begin(), lowlink.bridges.end());
    for (auto e : lowlink.bridges) {
        cout << e.first << " " << e.second << endl;
    }
    return 0;
}
