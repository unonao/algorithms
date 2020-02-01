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

template <class FLOWTYPE>
struct Edge {
    int rev, from, to;  // rev:逆向きの辺の番号
    FLOWTYPE cap, icap;
    Edge(int r, int f, int t, FLOWTYPE c) : rev(r), from(f), to(t), cap(c), icap(c) {}
    /*
    // debug
    friend ostream& operator<<(ostream& s, const Edge& E) {
        if (E.cap > 0) {return s << E.from << "->" << E.to << '(' << E.cap << ')';
        } else {return s;}
    }
    */
};

template <class FLOWTYPE>
struct Graph {
    vector<vector<Edge<FLOWTYPE>>> list;

    Graph(int n = 0) : list(n) {}
    void init(int n = 0) {
        list.clear();
        list.resize(n);
    }
    void reset() {
        for (int i = 0; i < (int)list.size(); ++i)
            for (int j = 0; j < list[i].size(); ++j) list[i][j].cap = list[i][j].icap;
    }
    inline vector<Edge<FLOWTYPE>>& operator[](int i) { return list[i]; }
    inline const size_t size() const { return list.size(); }

    inline Edge<FLOWTYPE>& redge(Edge<FLOWTYPE> e) {  // 逆向きの辺を返す
        if (e.from != e.to)
            return list[e.to][e.rev];
        else
            return list[e.to][e.rev + 1];
    }

    void add_edge(int from, int to, FLOWTYPE cap) {  // 辺を加える
        list[from].push_back(Edge<FLOWTYPE>((int)list[to].size(), from, to, cap));
        list[to].push_back(Edge<FLOWTYPE>((int)list[from].size() - 1, to, from, 0));
    }

    void add_undirected_edge(int from, int to, FLOWTYPE cap) {
        list[from].push_back(Edge<FLOWTYPE>((int)list[to].size(), from, to, cap));
        list[to].push_back(Edge<FLOWTYPE>((int)list[from].size() - 1, to, from, cap));
    }

    /*
    // debug
    friend ostream& operator<<(ostream& s, const Graph& G) {
        s << endl;
        for (int i = 0; i < G.list.size(); ++i) {
            for (auto e : G.list[i]) {s << e << endl;}
        }return s;
    }*/
};

/* FordFulkerson: Ford-Fulkersonのアルゴリズムで最大流を求める構造体
    Ford-Fulkerson ff;
    ff.max_flow(G,s,t) でグラフGの最大流が求まる
    計算量: O(F|E|) (F:最大流の流量) (この最悪ケースになることはほぼ無い)
*/
template <class FLOWTYPE>
struct FordFulkerson {
    const FLOWTYPE INF = 1 << 30;
    vector<int> used;

    FordFulkerson(){};
    FLOWTYPE dfs(Graph<FLOWTYPE>& G, int v, int t, FLOWTYPE f) {
        if (v == t) return f;
        used[v] = true;
        for (auto& e : G[v]) {
            if (!used[e.to] && e.cap > 0) {
                int d = dfs(G, e.to, t, min(f, e.cap));
                if (d > 0) {
                    e.cap -= d;
                    G.redge(e).cap += d;
                    return d;
                }
            }
        }
        return 0;
    }
    FLOWTYPE max_flow(Graph<FLOWTYPE>& G, int s, int t) {
        int flow = 0;
        while (true) {
            used.assign(G.size(), 0);
            int f = dfs(G, s, t, INF);
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
