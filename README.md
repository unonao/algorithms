# 競技プログラミングのためのアルゴリズム

競技プログラミングでよく使われるアルゴリズムを C++で実装しています。
コンテスト中に実装例を参考にしたり、ライブラリとして使用することを想定しています。そのため、単一のファイルで完結できるように、重複するコードが書かれている場合があります。

## 整数論(math_number_theory)

整数論に関係するアルゴリズムです。

#### 約数・倍数

- 最大公約数(gcd.cpp): Euclid の互除法で最大公約数を求める
- 拡張 Euclid の互除法(gcd_extend.cpp): ax+by=gcd(a,b)の解を 1 つ求める
- 最小公倍数(lcm.cpp): gcd を利用して最小公倍数を求める
- 素因数分解した最小公倍数(lcm_prime.cpp): 素因数分解の形で最小公倍数を求める(オーバーフローする場合など)
- 約数列挙(divisor.cpp)
- 約数の個数(divisor_num.cpp)
- べき乗(power.cpp)

#### 素数

- 素数判定(is_prime.cpp)
- 素因数分解(prime_factorization.cpp): O(√n)
- 前処理付き素因数分解(prime_factorization_spf.cpp): 初期化は O(N log log N)、クエリは O(log n)
- 素数の列挙(prime_table): エラトステネスの篩で n 以下の素数を列挙

## 組合せ論・mod(math_combinatorics)

組み合わせや数え上げに関係するアルゴリズムです。

#### mod

- modint(modint.cpp): modint 構造体と二項係数ライブラリまとめ

#### 二項係数(p は素数)

- 二項係数(mod_binomial_coefficient.cpp): 前処理 O(n)・クエリ O(1)。（n<=10^7, k<=10^7）
- n<=10^9 の二項係数(mod_binomial_coefficient_big.cpp): 前処理 O(k)・クエリ O(k)（n<=10^9, k<=10^7）
- n が固定の時の二項係数(mod_binomial_coefficient_big_static.cpp): 前処理 O(k)・クエリ O(1)（n<=10^9 で固定, k<=10^7）
- 素数 p が小さい時の二項係数(mod_binomial_coefficient_lucas.cpp): 前処理 O(p^2)・クエリ O(log n)（n,k<=10^18, p<=5000）。Lucas の定理を利用

#### 二項係数(p は素数でなくて良い)

- 小さい数での二項係数(mod_binomial_coefficient_dp.cpp): 前処理 O(n^2)・クエリ O(1)（1≦ k ≦ n ≦ 5000）

#### 二項係数(mod を取らない)

- 小さい数で mod を取らない二項係数(binomial_coefficient_for_small.cpp): n は 50 程度まで

#### その他

- 前計算ありベル数(bell_number_preprocess.cpp)
- スターリング数の和で計算するベル数(bell_number_stirling.cpp)
- 高々 k 個のブロックに分割(partition_number_at_most_k.cpp)
- 丁度 k 個のブロックに分割(partition_number_with_k.cpp)
- 二項係数による前計算あり第 2 種スターリング数(stirling_number_of_the_second_kind_binomial.cpp)
- DP による第 2 種スターリング数(stirling_number_of_the_second_kind_DP.cpp)

## 解析学(calculus)

解析学に関係するアルゴリズムです。

#### 畳み込み

- 高速フーリエ変換を利用した畳み込み(fft.cpp): 畳み込み(sum(a[j]b[k-j]))を計算する

## 線形代数(math_linear_algebra)

- 行列ライブラリ(Matrix.cpp)

## 幾何学(geometry)

- 基本(basic.cpp): 基本となる点, 線, 円, 多角形を定義
- 3 点の関係(ccw.cpp): 反時計, 時計回り, 一直線などの 3 点の関係を判定
- 点と直線との距離(distance_point_line.cpp)
- 点と三角形の包含関係(is_contain_in_triangle.cpp): 三角形に点が含まれるか判定する

## データ構造(data_structure)

様々なデータ構造です。

#### 素集合系(Union-Find Tree)

- rank による Union-Find 木(union_find_tree_rank.cpp): 併合時の工夫を rank によって行う
- size による Union-Find 木(union_find_tree_size.cpp): 併合時の工夫を size によって行う。集合の要素数が取得できる

#### セグメント木

- RMQ(range_minimum_query.cpp): 一点更新 RMQ
- RMQ・RUQ(range_minimum_query_RUQ.cpp): 区間更新 RMQ
- RMQ・RAQ(range_minimum_query_RAQ.cpp): 区間加算 RMQ
- セグ木(segment_tree.cpp): モノイドに対して使える
- 遅延評価セグ木(segment_tree_lazy.cpp): 作用付きモノイドに対して使える
- 作用が区間に比例する遅延評価セグ木(segment_tree_lazy_proportional.cpp): 作用が区間に比例する場合に使える

#### Binary Indexed Tree(BIT)

- BIT(binary_indexed_tree.cpp): 区間和の更新や計算を高速に行う。転倒数の計算にも使える。集合の管理にも使用でき「集合の中で w 番目に小さいもの」や「ある要素が何番目に小さいか」を高速に取得可能
- BIT・RAQ(binary_indexed_tree_RAQ.cpp): 区間和の更新や計算を高速に行う。区間加算対応
- BIT2D(binary_indexed_tree_2D.cpp): 二次元対応した BIT

## グラフ理論(graph)

#### dfs・bfs

- トポロジカルソート(BFS)(topological_sort_BFS.cpp): BFS でトポロジカルソート
- トポロジカルソート(DFS)(topological_sort_DFS.cpp): DFS でトポロジカルソート
- 二部グラフ判定(is_bipartite.cpp): DFS により二部グラフか判定し、頂点の二つの部分集合の要素数も求める
- 橋・関節点列挙(low_link.cpp): グラフ上の橋と関節点を O(V+E)で列挙する

#### 最短路

- 単一始点最短路(bellman_ford.cpp): ベルマンフォード法で単一視点最短路を求める。(負の辺の存在可・負閉路の検出可)
- 単一始点最短路(dijkstra.cpp): ダイクストラ法で単一視点最短路を求める。(負の辺を持たない)
- 全点間最短路(warshall_floyd.cpp): ワーシャルフロイド法で全点間最短路を求める。(負閉路の検出可)

#### その他

- 隣接リストの最小全域木(minimum_spanning_tree_kruskal.cpp): クラスカル法によって最小全域木を求める
- 隣接行列の最小全域木(minimum_spanning_tree_prim.cpp): プリム法によって最小全域木を求める
- 最小重み閉路(minimum_wight_cycle.cpp): コストが最小の閉路を求める

## グラフのネットワークフロー(graph_flow)

#### 最大流

- 最大流(max_flow_ford_fulkerson.cpp): Ford-Fulkerson のアルゴリズムで最大流を求める。これを利用して最大二部マッチングを求めることも可

## 木(graph_tree)

木に特有のアルゴリズムやデータ構造です。

- LCA(lca_doubling.cpp): ダブリングにより最近共通祖先(Lowest Common Ancestor)を求める。2 頂点間の距離を求めたり、ある点がパス上に存在するかを対数時間で判定できる。
- 木の直径(tree_diamiter.cpp): 木の直径を求める

## 動的計画法(dynamic_programming)

#### 典型的

- 最長増加部分列(longest_increasing_subsequence.cpp): LIS を求める。広義単調でも可
- 最長減少部分列(longest_decreasing_subsequence.cpp): LDS?を求める。広義減少でも可
- 全方位木 DP(rerooting.cpp)

## 文字列(string)

- トライ木(trie_tree.cpp)

## その他(others)

- 1D 座標圧縮(coordinate_compress_1D.cpp)
- 2D 座標圧縮(coordinate_compress_2D.cpp)
- ランレングス圧縮(run_length.cpp)
- pair 型を用いたランレングス圧縮(run_length_pair.cpp)
