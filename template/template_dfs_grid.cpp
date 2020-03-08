#include <bits/stdc++.h>
using namespace std;

using P = pair<int, int>;

int H, W;
vector<vector<char>> maze;  // 迷路の内容を保存する配列
vector<vector<bool>> seen;  // 既に通った場所なのかを記録しておく配列
P s;

// dfs
int dx[4] = {1, -1, 0, 0};  // dx,dy は次の探索場所への距離を表す（４方向分）
int dy[4] = {0, 0, 1, -1};
void dfs(P p) {
    seen[p.first][p.second] = true;
    for (int i = 0; i < 4; i++) {
        int ny = p.first + dy[i];                              // 次の探索場所の行番号
        int nx = p.second + dx[i];                             // 次の探索場所の列番号
        if (ny < 0 || H <= ny || nx < 0 || W <= nx) continue;  // 迷路の外に出るならスルー
        if (maze[ny][nx] == '#') continue;                     // 障害物があればスルー
        if (seen[ny][nx]) continue;                            //探索済みならスルー
        dfs(make_pair(ny, nx));
    }
}

int main() {
    cin >> H >> W;
    int sx, sy;
    cin >> sx >> sy;
    s = make_pair(sx, sy);

    maze.assign(H, vector<char>(W, '.'));
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            cin >> maze[i][j];
        }
    }

    seen.assign(H, vector<bool>(W, false));
    dfs(s);

    return 0;
}
