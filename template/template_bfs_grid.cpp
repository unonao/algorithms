#include <bits/stdc++.h>
using namespace std;

using P = pair<int, int>;
int H, W;
vector<vector<char>> maze;  // 迷路の内容を保存する配列
vector<vector<int>> dist;   // 距離を記録しておく配列
P s, g;

// 幅優先探索
void bfs(P s) {
    const int INF = 1e8;
    dist.assign(H, vector<int>(W, INF));  // 初期化

    queue<pair<int, int>> que;
    que.emplace(s);
    dist[s.first][s.second] = 0;
    while (que.size() != 0) {
        pair<int, int> now = que.front();
        que.pop();
        int dy[4] = {0, 0, 1, -1};  // dx,dy は次の探索場所への距離を表す（４方向分）
        int dx[4] = {1, -1, 0, 0};
        for (int i = 0; i < 4; i++) {
            int ny = now.first + dy[i];
            int nx = now.second + dx[i];
            if (ny < 0 || H <= ny || nx < 0 || W <= nx) continue;
            if (maze[ny][nx] == '#') continue;  // 障害物があればスルー
            if (dist[ny][nx] != INF) continue;
            que.push(make_pair(ny, nx));
            dist[ny][nx] = dist[now.first][now.second] + 1;
        }
    }
}

int main() {
    // cin.tie(0);
    // ios::sync_with_stdio(false);

    cin >> H >> W;
    int sx, sy, gx, gy;
    cin >> sy >> sx;
    cin >> gy >> gx;
    sy--, sx--, gy--, gx--;  // 0始まりに直す
    s = make_pair(sy, sx);
    g = make_pair(gy, gx);

    maze.assign(H, vector<char>(W, '.'));  // 初期化
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) cin >> maze[i][j];
    }

    bfs(s);
    cout << dist[g.first][g.second] << endl;

    return 0;
}
