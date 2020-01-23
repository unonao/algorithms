/*  union_find_tree_rank.cpp
    素集合系を union-find tree で管理するライブラリ
    併合時の工夫：union by rank

    verified: AOJ DSL_1_A
        http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_1_A
*/

#include <bits/stdc++.h>
using namespace std;

/* UnionFind：素集合系管理の構造体(union by rank)
    isSame(x, y): x と y が同じ集合にいるか。 計算量はならし O(α(n))
    unite(x, y): x と y を同じ集合にする。計算量はならし O(α(n))
*/
struct UnionFind {  // The range of node number is from 0 to n-1
    //'rank[x]' is a rank of the union find tree the root of which is x.
    //'parents[x]' is the parent of x
    vector<int> rank, parents;
    // constructor
    UnionFind() {}
    UnionFind(int n) {  // make n trees.
        rank.resize(n, 0);
        parents.resize(n, 0);
        for (int i = 0; i < n; i++) {
            makeTree(i);
        }
    }
    // make a union find tree
    void makeTree(int x) {
        parents[x] = x;  // the parent of x is x
        rank[x] = 0;
    }

    // check whether the root of x is the same as that of y
    bool isSame(int x, int y) { return findRoot(x) == findRoot(y); }

    // unite two tree
    void unite(int x, int y) {
        x = findRoot(x);
        y = findRoot(y);
        if (rank[x] > rank[y]) {
            parents[y] = x;
        } else {
            parents[x] = y;
            if (rank[x] == rank[y]) {
                rank[y]++;
            }
        }
    }

    // travel the parents of tree recursivily to find root
    int findRoot(int x) {
        if (x != parents[x]) {
            parents[x] = findRoot(parents[x]);  // change the x's parent to the root of tree.
        }
        return parents[x];
    }
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
