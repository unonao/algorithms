/* max_flow_ford_fulkerson.cpp
    Ford-Fulkerson のアルゴリズムで最大流を求めるアルゴリズム
    計算量: O(F|E|) (F:最大流の流量) (この最悪ケースになることはほぼ無い)

    最大マッチングの求め方:
        シンクs, タンクt を加え、辺のcapを1としたグラフの最大流が、最大マッチングに等しい
        例: [AtCoder] ABC091 C - 2D Plane 2N Points
            https://atcoder.jp/contests/abc091/tasks/arc092_a

    verified: AOJ Course GRL_6_A Network Flow - Maximum Flow
        http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_6_A&lang=jp
*/

#include <bits/stdc++.h>
using namespace std;

template <class T>
struct Edge {
    int rev, from, to;  // rev:逆向きの辺の番号
    T cap, original_cap;
    Edge(int r, int f, int t, T c) : rev(r), from(f), to(t), cap(c), original_cap(c) {}
    /*
    // debug
    friend ostream& operator<<(ostream& s, const Edge& E) {
        if (E.cap > 0) {return s << E.from << "->" << E.to << '(' << E.cap << ')';
        } else {return s;}
    }
    */
};

template <class T>
struct Graph {
    vector<vector<Edge<T>>> G;
    Graph(int n = 0) : G(n) {}
    void init(int n = 0) {
        G.clear();
        G.resize(n);
    }
    void reset() {
        for (int i = 0; i < (int)G.size(); i++)
            for (int j = 0; j < G[i].size(); j++) G[i][j].cap = G[i][j].original_cap;
    }
    vector<Edge<T>>& operator[](int i) { return G[i]; }
    const size_t size() const { return G.size(); }

    Edge<T>& redge(Edge<T> e) {  // 逆向きの辺を返す
        return G[e.to][e.rev];   // 自己ループはないと仮定（あれば G[e.to][e.rev + 1] とする必要がある）
    }

    void add_edge(int from, int to, T cap) {  // 有向辺を加える
        G[from].push_back(Edge<T>((int)G[to].size(), from, to, cap));
        G[to].push_back(Edge<T>((int)G[from].size() - 1, to, from, 0));
    }

    void add_undirected_edge(int from, int to, T cap) {  // 無向辺を加える
        G[from].push_back(Edge<T>((int)G[to].size(), from, to, cap));
        G[to].push_back(Edge<T>((int)G[from].size() - 1, to, from, cap));
    }

    /*
    // debug
    friend ostream& operator<<(ostream& s, const Graph& G) {
        s << endl;
        for (int i = 0; i < G.G.size(); ++i) {
            for (auto e : G.G[i]) {s << e << endl;}
        }return s;
    }*/
};

/* FordFulkerson: Ford-Fulkersonのアルゴリズムで最大流を求める構造体
    Ford-Fulkerson ff;
    ff.max_flow(G,s,t) でグラフGの最大流が求まる
    副作用：G は最大流の残余ネットワークになる
    計算量: O(|f*||E|) (f*:最大流) (この最悪ケースになることはほぼ無い)
*/
template <class T>
struct FordFulkerson {
    const T INF = 1e9;
    vector<int> used;

    FordFulkerson(){};
    T dfs(Graph<T>& G, int v, int t, T f) {  // 増加可能経路を見つけて増加分のフローを返す
        if (v == t) return f;
        used[v] = true;
        for (auto& e : G[v]) {
            if (!used[e.to] && e.cap > 0) {
                T d = dfs(G, e.to, t, min(f, e.cap));
                if (d > 0) {
                    e.cap -= d;
                    G.redge(e).cap += d;
                    return d;
                }
            }
        }
        return 0;
    }
    T max_flow(Graph<T>& G, int s, int t) {
        T flow = 0;
        while (true) {
            used.assign(G.size(), 0);
            T f = dfs(G, s, t, INF);  // f が増加分のフロー
            if (f == 0) {
                return flow;
            } else {
                flow += f;
            }
        }
        return 0;
    }
};

int main() {
    int V, E;
    cin >> V >> E;
    Graph<int> G(V);
    for (int i = 0; i < E; i++) {
        int u, v, c;
        cin >> u >> v >> c;
        G.add_edge(u, v, c);
    }
    FordFulkerson<int> ff;
    cout << ff.max_flow(G, 0, V - 1) << endl;
}
