/* run_length_pair.cpp
    pair型を用いてランレングス圧縮のエンコードとデコードを行う

    verified: [AtCoder] ABC 019 B - 高橋くんと文字列圧縮
        https://atcoder.jp/contests/abc019/tasks/abc019_2
*/

#include <bits/stdc++.h>
using namespace std;

/* encode: ランレングス圧縮を行う
*/
vector<pair<char, int>> encode(const string& str) {
    int n = (int)str.size();
    vector<pair<char, int>> ret;
    for (int l = 0; l < n;) {
        int r = l + 1;
        for (; r < n && str[l] == str[r]; r++) {};
        ret.push_back({str[l], r - l});
        l = r;
    }
    return ret;
}

/* decode: ランレングス圧縮の復元を行う
*/
string decode(const vector<pair<char, int>>& code) {
    string ret = "";
    for (auto p : code) {
        for (int i = 0; i < p.second; i++) {
            ret.push_back(p.first);
        }
    }
    return ret;
}

int main() {
    string S;
    cin >> S;
    vector<pair<char, int>> en = encode(S);
    for (auto p : en) {
        cout << p.first << p.second << " ";
    }
    cout << endl;
    string de = decode(en);
    cerr << de << endl;
}
