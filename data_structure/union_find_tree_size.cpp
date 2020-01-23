/*  union_find_tree_size.cpp
    素集合系を union-find tree で管理するライブラリ
    併合時の工夫：union by size
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
    void unite(int x, int y) {
        x = findRoot(x);
        y = findRoot(y);
        if (size[x] > size[y]) {
            parents[y] = x;
            size[x] += size[y];
        } else {
            parents[x] = y;
            size[y] += size[x];
        }
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
    int N;             // the number of nodes
    int Q;             // the number of query
    vector<int> P;     // p is a "same" or "unite" command.
    vector<int> A, B;  // a and b are nodes.

    cin >> N >> Q;
    UnionFind uft(N);  // make trees

    for (int i = 0; i < Q; i++) {
        int p, a, b;
        cin >> p >> a >> b;
        P.push_back(p);
        A.push_back(a);
        B.push_back(b);
    }

    for (int i = 0; i < Q; i++) {
        if (P[i] == 0)
            uft.unite(A[i], B[i]);
        else if (P[i] == 1) {
            if (uft.isSame(A[i], B[i]))
                cout << "1\n";
            else
                cout << "0\n";
        }
    }
    return 0;
}
