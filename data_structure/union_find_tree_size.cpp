/*  union_find_tree_size.cpp
    素集合系を union-find tree で管理するライブラリ
    併合時の工夫：union by size

    verified: AtCoder ABC157 D - Friend Suggestions
        https://atcoder.jp/contests/abc157/tasks/abc157_d
*/

#include <bits/stdc++.h>
using namespace std;

/* UnionFind：素集合系管理の構造体(union by size)
    isSame(x, y): x と y が同じ集合にいるか。 計算量はならし O(α(n))
    unite(x, y): x と y を同じ集合にする。計算量はならし O(α(n))
    treeSize(x): x を含む集合の要素数。
*/
struct UnionFind {
    vector<int> size, parents;
    UnionFind() {}
    UnionFind(int n) {  // make n trees.
        size.resize(n, 0);
        parents.resize(n, 0);
        for (int i = 0; i < n; i++) {
            makeTree(i);
        }
    }
    void makeTree(int x) {
        parents[x] = x;  // the parent of x is x
        size[x] = 1;
    }
    bool isSame(int x, int y) { return findRoot(x) == findRoot(y); }
    bool unite(int x, int y) {
        x = findRoot(x);
        y = findRoot(y);
        if (x == y) return false;
        if (size[x] > size[y]) {
            parents[y] = x;
            size[x] += size[y];
        } else {
            parents[x] = y;
            size[y] += size[x];
        }
        return true;
    }
    int findRoot(int x) {
        if (x != parents[x]) {
            parents[x] = findRoot(parents[x]);
        }
        return parents[x];
    }
    int treeSize(int x) { return size[findRoot(x)]; }
};

int main() {
    int N, M, K;
    cin >> N >> M >> K;
    UnionFind uf(N);              // Union-Find Tree で考える
    vector<int> edges_num(N, 0);  // 自身から出る辺の数
    vector<int> A(M), B(M);
    for (int i = 0; i < M; i++) {
        cin >> A.at(i) >> B.at(i);
        A[i]--, B[i]--;
        edges_num[A[i]]++;
        edges_num[B[i]]++;
        uf.unite(A[i], B[i]);
    }
    vector<int> C(K), D(K);
    for (int i = 0; i < K; i++) {
        cin >> C.at(i) >> D.at(i);
        C[i]--, D[i]--;
    }

    vector<int> ans(N);
    for (int i = 0; i < N; i++) {
        ans[i] = uf.treeSize(i) - 1 - edges_num[i];
    }
    for (int i = 0; i < K; i++) {  // 同じ連結成分にあるブロック関係を引く
        if (uf.isSame(C[i], D[i])) {
            ans[C[i]]--;
            ans[D[i]]--;
        }
    }

    for (int i = 0; i < N; i++) {
        cout << ans[i];
        if (i != (int)ans.size() - 1) cout << " ";
    }
    cout << endl;

    return 0;
}
