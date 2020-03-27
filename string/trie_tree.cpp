/* trie_tree.cpp
    trie 木（prefix 関係の構造体。文字列検索を高速にできる）

    verify: Google Kick Start 2020 Round A  Bundling (14pts, 21pts)
        https://codingcompetitions.withgoogle.com/kickstart/round/000000000019ffc7/00000000001d3ff3
*/

#include <bits/stdc++.h>
using namespace std;

/* Trie 木： 文字の種類(char_size)、int型で0に対応する文字(base)
    insert(str): 文字列 str を Trie 木に挿入する
    search(str): 文字列 str が Trie 木にあるか判定する
    start_with(prefix):  prefix が一致する文字列が Trie 木にあるか判定する
    count(): 挿入した文字列の数を返す
    size(): Trie 木の頂点数を返す
    計算量：inset, search ともに O(M)（Mは文字列の長さ）
*/
template <int char_size, int base>
struct Trie {
    struct Node {
        vector<int> next;    // 子の頂点番号を格納。存在しなければ-1
        vector<int> accept;  // 末端がこの頂点になる文字列の str_id を保存
        int c;               // base からの間隔をint型で表現したもの
        int exist;           // いくつの文字列が子孫の頂点を形成しているか
        int common;          // いくつの文字列がこの頂点を共有しているか
        Node(int c_) : c(c_), exist(0), common(0) {
            next.assign(char_size, -1);
        }
        friend ostream &operator<<(ostream &os, const Node &n) { return os << "c:" << (char)(n.c + base) << " common:" << n.common << " exist:" << n.exist << " accept:" << (int)n.accept.size() << "\n"; }  // debug 用
    };
    vector<Node> nodes;  // trie 木本体
    int root;
    Trie() : root(0) {
        nodes.push_back(Node(root));
    }

    // 頂点の更新用関数
    void update(int node_id, int child_id, int str_id) {  // 子と自身を更新
        update_direct(node_id, str_id);
        ++nodes[node_id].exist;
        update_child(child_id, str_id);
    }
    void update_direct(int node_id, int str_id) {  // 自身を更新
        ++nodes[node_id].common;
    }
    void update_child(int child_id, int str_id) {  // 子を更新
    }

    // 文字列の挿入
    void insert(const string &str, int str_id) {
        int node_id = 0;
        for (int i = 0; i < (int)str.size(); i++) {
            int c = (int)(str[i] - base);
            int &next_id = nodes[node_id].next[c];
            if (next_id == -1) {  // 次の頂点が存在しなければ追加
                next_id = (int)nodes.size();
                nodes.push_back(Node(c));
            }
            update(node_id, next_id, str_id);
            node_id = next_id;
        }
        update_direct(node_id, str_id);
        nodes[node_id].accept.push_back(str_id);
    }
    void insert(const string &str) {
        insert(str, nodes[0].exist);
    }

    // 文字列の検索
    bool search(const string &str, bool prefix = false) {
        int node_id = 0;
        for (int i = 0; i < (int)str.size(); i++) {
            int c = (int)(str[i] - base);
            int &next_id = nodes[node_id].next[c];
            if (next_id == -1) {  // 次の頂点が存在しなければ終了
                return false;
            }
            node_id = next_id;
        }
        return (prefix) ? true : nodes[node_id].accept.size() > 0;
    }

    // str が prefix となる文字列が存在するかの検索
    bool start_with(const string &prefix) {
        return search(prefix, true);
    }

    // 挿入した文字列の数
    int count() const {
        return (nodes[0].exist);
    }
    // Trie木のノード数
    int size() const {
        return ((int)nodes.size());
    }

    /*
    // 文字列Sのプレフィックスに一致する文字列を検索する。一致した文字列ごとに関数fが呼び出される。
    void query(const string &str, const function<void(int)> &f, int str_index, int node_id) {
        for (auto &idx : nodes[node_id].accept) f(idx);
        if (str_index == str.size()) {
            return;
        } else {
            const int c = str[str_index] - base;
            if (nodes[node_id].nxt[c] == -1) return;
            query(str, f, str_index + 1, nodes[node_id].nxt[c]);
        }
    }
    void query(const string &str, const function<void(int)> &f) {
        query(str, f, 0, 0);
    }
    */

    int solve(int k, int node_id) {  // 全頂点を探索して、common/k の総和を返す
        int ret = 0;
        for (auto &next_id : nodes[node_id].next) {
            if (next_id == -1) continue;
            if (nodes[next_id].common >= k) {
                ret += nodes[next_id].common / k;
                ret += solve(k, next_id);
            }
        }
        return ret;
    }
};

int T;
int N, K;

int main() {
    cin >> T;
    vector<int> ans(T);
    for (int t = 0; t < T; t++) {
        cin >> N >> K;
        Trie<26, 'A'> trie;
        vector<string> S(N);
        for (int i = 0; i < N; i++) {
            cin >> S.at(i);
            trie.insert(S[i]);
            //cout << trie.search(S[i]) << endl;
        }
        ans[t] = trie.solve(K, 0);
    }

    for (int i = 0; i < T; i++) {
        cout << "Case #" << i + 1 << ": " << ans[i] << endl;
    }
    return 0;
}
