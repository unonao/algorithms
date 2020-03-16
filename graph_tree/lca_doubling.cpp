/* lca_doubling.cpp
    最近共通祖先(LCA:Lowest Common Ancestor)をダブリングにより求める
    (u,v の2^k先の親が同じかどうかを二分探索で調べる)

    verified: AOJ GRL_5_C
        http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_5_C
 */

#include <bits/stdc++.h>
using namespace std;

struct Edge {
    long long to;
};
using Graph = vector<vector<Edge>>;

/* LCA(G, root): 木 G に対する根を root として Lowest Common Ancestor を求める構造体
    query(u,v): u と v の LCA を求める。計算量 O(logn)
    dist(u,v): u と v の距離を求める。計算量 O(logn)
    is_on_path(u,v,a): u, v を繋ぐパス上に a が存在するかを判定する。計算量 O(logn)
    前処理: O(nlogn)時間, O(nlogn)空間
*/
struct LCA {
    vector<vector<int>> parent;  // parent[k][u]:= u の 2^k 先の親
    vector<int> depth;           // root からの深さ
    LCA(const Graph &G, int root = 0) { init(G, root); }
    void init(const Graph &G, int root = 0) {
        int V = G.size();
        int K = 1;
        while ((1 << K) < V) K++;
        parent.assign(K, vector<int>(V, -1));
        depth.assign(V, -1);
        dfs(G, root, -1, 0);
        for (int k = 0; k + 1 < K; k++) {
            for (int v = 0; v < V; v++) {
                if (parent[k][v] < 0) {
                    parent[k + 1][v] = -1;
                } else {
                    parent[k + 1][v] = parent[k][parent[k][v]];
                }
            }
        }
    }
    void dfs(const Graph &G, int v, int p, int d) {
        parent[0][v] = p;
        depth[v] = d;
        for (auto e : G[v]) {
            if (e.to != p) dfs(G, e.to, v, d + 1);
        }
    }
    int query(int u, int v) {
        if (depth[u] < depth[v]) swap(u, v);  // u の方が深いとする
        int K = parent.size();
        for (int k = 0; k < K; k++) {
            if ((depth[u] - depth[v]) >> k & 1) {
                u = parent[k][u];
            }
        }
        if (u == v) return u;
        for (int k = K - 1; k >= 0; k--) {
            if (parent[k][u] != parent[k][v]) {
                u = parent[k][u];
                v = parent[k][v];
            }
        }
        return parent[0][u];
    }
    int dist(int u, int v) { return depth[u] + depth[v] - 2 * depth[query(u, v)]; }
    bool is_on_path(int u, int v, int a) { return dist(u, a) + dist(a, v) == dist(u, v); }
};

int main() {
    int n;
    cin >> n;
    Graph G(n);
    for (int i = 0; i < n; i++) {
        int k;
        cin >> k;
        for (int j = 0; j < k; j++) {
            int c;
            cin >> c;
            G[i].push_back({c});
            G[c].push_back({i});
        }
    }
    int q;
    cin >> q;
    vector<int> u(q), v(q);
    for (int i = 0; i < q; i++) {
        cin >> u.at(i) >> v.at(i);
    }

    LCA lca(G, 0);

    for (int i = 0; i < q; i++) {
        cout << lca.query(u[i], v[i]) << endl;
    }
}
