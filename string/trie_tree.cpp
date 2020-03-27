/* trie_tree.cpp
    trie 木（prefix 関係の構造体。単語検索を高速にできる）

    verify: Google Kick Start 2020 Round A  Bundling (14pts, 21pts)
        https://codingcompetitions.withgoogle.com/kickstart/round/000000000019ffc7/00000000001d3ff3
*/

#include <bits/stdc++.h>
using namespace std;

/* Trie 木： 文字の種類(char_size)、int型で0に対応する文字(base)
    insert(word): 単語 word を Trie 木に挿入する
    search(word): 単語 word が Trie 木にあるか判定する
    start_with(prefix):  prefix が一致する単語が Trie 木にあるか判定する
    count(): 挿入した単語の数を返す
    size(): Trie 木の頂点数を返す
    計算量：insert, search ともに O(M)（Mは単語の長さ）
*/

template <int char_size, int base>
struct Trie {
    struct Node {            // 頂点を表す構造体
        vector<int> next;    // 子の頂点番号を格納。存在しなければ-1
        vector<int> accept;  // 末端がこの頂点になる単語の word_id を保存
        int c;               // base からの間隔をint型で表現したもの
        int common;          // いくつの単語がこの頂点を共有しているか
        Node(int c_) : c(c_), common(0) {
            next.assign(char_size, -1);
        }
        friend ostream &operator<<(ostream &os, const Node &n) { return os << "c:" << (char)(n.c + base) << " common:" << n.common << " accept:" << (int)n.accept.size() << "\n"; }  // debug 用
    };
    vector<Node> nodes;  // trie 木本体
    int root;
    Trie() : root(0) {
        nodes.push_back(Node(root));
    }

    // 単語の挿入
    void insert(const string &word, int word_id) {  // 単語:str と 単語の番号: str_id
        int node_id = 0;
        for (int i = 0; i < (int)word.size(); i++) {
            int c = (int)(word[i] - base);
            int &next_id = nodes[node_id].next[c];
            if (next_id == -1) {  // 次の頂点が存在しなければ追加
                next_id = (int)nodes.size();
                nodes.push_back(Node(c));
            }
            ++nodes[node_id].common;
            node_id = next_id;
        }
        ++nodes[node_id].common;
        nodes[node_id].accept.push_back(word_id);  // 単語の終端なので、頂点に番号を入れておく
    }
    void insert(const string &word) {
        insert(word, nodes[0].common);
    }

    // 単語とprefixの検索
    bool search(const string &word, bool prefix = false) {
        int node_id = 0;
        for (int i = 0; i < (int)word.size(); i++) {
            int c = (int)(word[i] - base);
            int &next_id = nodes[node_id].next[c];
            if (next_id == -1) {  // 次の頂点が存在しなければ終了
                return false;
            }
            node_id = next_id;
        }
        return (prefix) ? true : nodes[node_id].accept.size() > 0;  // 最後の頂点が受理状態か確認
    }

    // prefix を持つ単語が存在するかの検索
    bool start_with(const string &prefix) {
        return search(prefix, true);
    }

    // 挿入した単語の数
    int count() const {
        return (nodes[0].common);
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
