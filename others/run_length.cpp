/* run_length.cpp
    ランレングス圧縮のエンコードとデコードを行う

    verified: [AtCoder] ABC 019 B - 高橋くんと文字列圧縮
        https://atcoder.jp/contests/abc019/tasks/abc019_2
*/

#include <bits/stdc++.h>
using namespace std;

/* encode: ランレングス圧縮を行う
    str内には数字が出現しないと仮定
*/
string encode(const string& str) {
    int n = (int)str.size();
    string ret = "";
    for (int l = 0; l < n;) {
        int r = l + 1;
        for (; r < n && str[l] == str[r]; r++) {};
        ret.push_back(str[l]);
        string num_str = to_string(r - l);
        ret += num_str;
        l = r;
    }
    return ret;
}

/* decode: ランレングス圧縮の復元を行う
    元の文字列には数字が出現しないと仮定
*/
string decode(const string& str) {
    int n = (int)str.size();
    string ret = "";
    for (int l = 0; l < n;) {
        int r = l + 1;
        for (; r < n && '0' <= str[r] && str[r] <= '9'; r++) {};
        int num = stoi(str.substr(l + 1, r - l));
        for (int i = 0; i < num; i++) {
            ret.push_back(str[l]);
        }
        l = r;
    }
    return ret;
}

int main() {
    string S;
    cin >> S;
    string en = encode(S);
    cout << en << endl;
    string de = decode(en);
    cerr << de << endl;
}
