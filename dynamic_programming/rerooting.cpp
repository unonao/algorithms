/* rerooting.cpp
    全方位木DP

// 一辺コスト1の木について、各頂点から最も遠い点までの距離
    struct DP {
        long long dp;
        DP(long long dp_ = -1) : dp(dp_) {}  // 頂点一つ(子が0)の部分木の時は-1,
    };
    function<DP(DP, DP)> fd = [](DP d1, DP d2) -> DP {  // dp 同士の二項演算
        return DP(max(d1.dp, d2.dp));                   //最大の深さ(根から最も遠い点までの距離)
    };
    function<DP(DP)> fr = [](DP d) -> DP {  // まとめたDPを用いて、新たな部分木のDPを計算する
        return DP(d.dp + 1);
    };

    verified: AOJ Traffic Tree
        http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1595
*/

#include <bits/stdc++.h>
using namespace std;

/* Rerooting:
    問題ごとに以下を書き換える
    - 型DP
    - 型DPに対する二項演算 fd
    - まとめたDPを用いて新たな部分木のDPを計算する fr
    計算量: O(N)
*/
struct Rerooting {
    // DP と演算の定義（問題ごとに書き換える）
    struct DP {
        long long dp;
        DP(long long dp_ = -1) : dp(dp_) {}  // 単位元はしっかり定義する(末端でもfrされるので注意)
    };
    function<DP(DP, DP)> fd = [](DP d1, DP d2) -> DP {  // dp 同士の二項演算
        return DP(max(d1.dp, d2.dp));                   //最大の深さ(根から最も遠い点までの距離)
    };
    function<DP(DP)> fr = [](DP d) -> DP {  // まとめたDPを用いて、新たな部分木のDPを計算する
        return DP(d.dp + 1);
    };

    struct Edge {
        int to;
        long long cost;
    };
    using Graph = vector<vector<Edge>>;

    vector<vector<DP>> dp;  // dp[v][i]: vから出るi番目の有向辺に対応する部分木のDP
    vector<DP> ans;         // ans[v]: 頂点vを根とする木の答え
    Graph G;

    Rerooting(int N) : dp(N), ans(N), G(N) {}

    void add_edge(int a, int b, long long c = 1) {
        G[a].push_back({b, c});
    }
    void build() {
        dfs(0);  // 普通に木DP
        bfs(0);  // 残りの部分木に対応するDPを計算
    }

    DP dfs(int v, int p = -1) {  // 頂点v, 親p
        DP dp_cum;
        int deg = G[v].size();
        dp[v] = vector<DP>(deg);
        for (int i = 0; i < deg; i++) {
            int u = G[v][i].to;
            if (u == p) continue;
            dp[v][i] = dfs(u, v);
            dp_cum = fd(dp_cum, dp[v][i]);
        }
        return fr(dp_cum);
    }
    void bfs(int v, const DP& dp_p = DP(), int p = -1) {
        int deg = G[v].size();
        for (int i = 0; i < deg; i++) {  // 前のbfsで計算した有向辺に対応する部分木のDPを保存
            if (G[v][i].to == p) dp[v][i] = dp_p;
        }

        vector<DP> dp_l(deg + 1), dp_r(deg + 1);  // 累積的なDP
        for (int i = 0; i < deg; i++) {
            dp_l[i + 1] = fd(dp_l[i], dp[v][i]);
        }
        for (int i = deg - 1; i >= 0; i--) {
            dp_r[i] = fd(dp_r[i + 1], dp[v][i]);
        }
        ans[v] = fr(dp_l[deg]);
        for (int i = 0; i < deg; i++) {
            int u = G[v][i].to;
            if (u == p) continue;
            bfs(u, fr(fd(dp_l[i], dp_r[i + 1])), v);
        }
    }
};

int main() {
    int N;
    cin >> N;
    Rerooting reroot(N);
    for (int i = 0; i < N - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        reroot.add_edge(u, v);
        reroot.add_edge(v, u);
    }
    reroot.build();
    for (int i = 0; i < N; i++) {
        cout << (N - 1) * 2 - reroot.ans[i].dp << "\n";
    }
}
