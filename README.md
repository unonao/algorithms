# 競技プログラミングのためのアルゴリズム
競技プログラミングでよく使われるアルゴリズムをC++で実装しています。
コンテスト中に実装例を参考にしたり、ライブラリとして使用することを想定しています。そのため、単一のファイルで完結できるように、重複するコードが書かれている場合があります。

## 整数論(math_number_theory)
整数論に関係するアルゴリズムです。
#### 約数・倍数
- 最大公約数(gcd.cpp): Euclidの互除法で最大公約数を求める
- 拡張Euclidの互除法(gcd_extend.cpp): ax+by=gcd(a,b)の解を1つ求める
- 最小公倍数(lcm.cpp): gcdを利用して最小公倍数を求める
- 素因数分解した最小公倍数(lcm_prime.cpp): 素因数分解の形で最小公倍数を求める(オーバーフローする場合など)
- 約数列挙(divisor.cpp)

#### 素数
- 素数判定(is_prime.cpp)
- 素因数分解(prime_factorization)
- 素数の列挙(prime_table): エラトステネスの篩で n 以下の素数を列挙

## 組合せ論・mod(math_combinatorics)
組み合わせや数え上げに関係するアルゴリズムです。
#### 二項係数・mod
- modint(modint.cpp): modint構造体と二項係数ライブラリまとめ
- 二項係数(mod_binomial_coefficient.cpp): n<=10^7, k<=10^7, p(mod)は素数
- 小さい数での二項係数(mod_binomial_coefficient_dp.cpp): 1≦ k ≦ n ≦ 5000, p は素数である必要がない。漸化式を用いて求める。


## 解析学(calculus)
解析学に関係するアルゴリズムです。
#### 畳み込み
- 高速フーリエ変換を利用した畳み込み(fft.cpp): 畳み込み(sum(a[j]b[k-j]))を計算する

## 線形代数(math_linear_algebra)
未作成

## 幾何学(geometry)
未作成


## データ構造(data_structure)
様々なデータ構造です。
#### 素集合系(Union-Find Tree)
- rankによるUnion-Find木(union_find_tree_rank.cpp): 併合時の工夫をrankによって行う
- sizeによるUnion-Find木(union_find_tree_size.cpp): 併合時の工夫をsizeによって行う。集合の要素数が取得できる

#### セグメント木
- RMQ(range_minimum_query.cpp): 区間での最小要素を管理します

#### Binary Indexed Tree(BIT)
- BIT(binary_indexed_tree.cpp): 区間和の更新や計算を高速に行う。転倒数の計算にも使える
- BIT上での二分探索(binary_search_on_BIT.cpp): BITの拡張版。a_1 + a_2 + ... + a_x >= w となるような最小の x を求められる。集合の管理にも使用でき、「集合の中で w 番目に小さいもの」や「ある要素が何番目に小さいか」を高速に取得可能

## 木(tree)
木に特有のアルゴリズムやデータ構造です。
- LCA(lca_doubling.cpp): ダブリングにより最近共通祖先を求めるデータ構造


## グラフ理論(graph_theory)
#### 最短路
- 単一始点最短路(dijkstra.cpp): ダイクストラ法で単一視点最短路を求める。(負の辺を持たない)
- 全点間最短路(warshall_floyd.cpp): ワーシャルフロイド法で全点間最短路を求める。(負閉路の検出可)
#### 探索
- 二部グラフ判定(is_bipartite.cpp): DFSにより二部グラフか判定し、頂点の二つの部分集合の要素数も求める
