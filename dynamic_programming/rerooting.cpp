/* rerooting.cpp
    全方位木DP

    // 根rから最も遠い点までの距離を求める
    struct DP {  // 単位元はしっかり定義する(末端でもadd_rootされるので注意)
        long long dp;
        DP(long long dp_ = 0) : dp(dp_) {}
    };
    function<DP(DP, DP, long long)> merge = [](DP dp_cum, DP d, long long cost) -> DP {  // d:辺eに対応する部分木のdpの値  cost:eのコスト
        return DP(max(dp_cum.dp, d.dp + cost));                                       //最大の深さ(根から最も遠い点までの距離)
    };
    function<DP(DP)> add_root = [](DP d) -> DP {  // まとめたDPを用いて、新たな部分木のDPを計算する
        return d;
    };

    verified:
    - AOJ GRL_5_A: Diameter of a Tree
        http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_5_A
    - [AtCoder] Typical DP Contest N - 木
        https://tdpc.contest.atcoder.jp/submissions/11405065
    - [AtCoder] ABC 160 F - Distributing Integers （上とほぼ同じ）
        https://atcoder.jp/contests/abc160/submissions/11405183

    - AOJ 1595: Traffic Tree
        http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1595
*/

#include <bits/stdc++.h>
using namespace std;

/* Rerooting: 全方位木 DP
    問題ごとに以下を書き換える
    - 型DPと単位元
    - 型DPに対する二項演算 merge
    - まとめたDPを用いて新たな部分木のDPを計算する add_root
    計算量: O(N)
*/
struct Rerooting {
    /* start 問題ごとに書き換え */
    struct DP {  // DP の型
        long long dp;
        DP(long long dp_) : dp(dp_) {}
    };
    const DP identity = DP(0);                                                           // 単位元はしっかり定義する(末端でもadd_rootされるので注意)
    function<DP(DP, DP, long long)> merge = [](DP dp_cum, DP d, long long cost) -> DP {  // d:辺eに対応する部分木のdpの値  cost:eのコスト
        return DP(max(dp_cum.dp, d.dp + cost));
    };
    function<DP(DP)> add_root = [](DP d) -> DP {  // まとめたDPを用いて、新たな部分木のDPを計算する
        return d;
    };
    /* end 問題ごとに書き換え */

    // グラフの定義
    struct Edge {
        int to;
        long long cost;
    };
    using Graph = vector<vector<Edge>>;

    vector<vector<DP>> dp;  // dp[v][i]: vから出るi番目の有向辺に対応する部分木のDP
    vector<DP> ans;         // ans[v]: 頂点vを根とする木の答え
    Graph G;

    Rerooting(int N) : G(N) {
        dp.resize(N);
        ans.assign(N, identity);
    }

    void add_edge(int a, int b, long long c = 1) {
        G[a].push_back({a, b, c});
    }
    void build() {
        dfs(0);            // 普通に木DP
        bfs(0, identity);  // 残りの部分木に対応するDPを計算
    }

    DP dfs(int v, int p = -1) {  // 頂点v, 親p
        DP dp_cum = identity;
        int deg = G[v].size();
        dp[v] = vector<DP>(deg, identity);
        for (int i = 0; i < deg; i++) {
            int u = G[v][i].to;
            if (u == p) continue;
            dp[v][i] = dfs(u, v);
            dp_cum = merge(dp_cum, dp[v][i], G[v][i].cost);
        }
        return add_root(dp_cum);
    }
    void bfs(int v, const DP& dp_p, int p = -1) {
        int deg = G[v].size();
        for (int i = 0; i < deg; i++) {  // 前のbfsで計算した有向辺に対応する部分木のDPを保存
            if (G[v][i].to == p) dp[v][i] = dp_p;
        }

        vector<DP> dp_l(deg + 1, identity), dp_r(deg + 1, identity);  // 累積的なDP
        for (int i = 0; i < deg; i++) {
            dp_l[i + 1] = merge(dp_l[i], dp[v][i], G[v][i].cost);
        }
        for (int i = deg - 1; i >= 0; i--) {
            dp_r[i] = merge(dp_r[i + 1], dp[v][i], G[v][i].cost);
        }
        ans[v] = add_root(dp_l[deg]);
        for (int i = 0; i < deg; i++) {
            int u = G[v][i].to;
            if (u == p) continue;
            bfs(u, add_root(merge(dp_l[i], dp_r[i + 1], 0)), v);  // 累積同士のmergeなので、edgeは適当に
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
        cout << (N - 1) * 2 - reroot.ans[i].dp << endl;
    }
}
