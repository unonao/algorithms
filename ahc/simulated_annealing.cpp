/* simulated_annealing.cpp
    焼きなまし法によるヒューリスティックな解法のテンプレート

温度関数
    start_temp = (一回の遷移で動きうるスコア幅の最大値程度);
    end_temp = (一回の遷移で動きうるスコア幅の最小値程度);
    temp = (線形でstart_tempからend_tempに減少する);
遷移確率関数
    prob = exp((new_score-pre_score)/temp);

コツ
  - https://shindannin.hatenadiary.com/entry/2021/03/06/115415
  - https://github.com/hakomo/Simulated-Annealing-Techniques
*/

#include <bits/stdc++.h>
using namespace std;
#define debug(x) cerr << #x << ": " << x << '\n'
// 1次元 vector print
template <class T>
ostream &operator<<(ostream &s, vector<T> vec) {
    for (int i = 0; i < (int)vec.size(); ++i) {
        if (i > 0) {
            s << " ";
        }
        s << vec[i];
    }
    return s << endl;
}
// 2次元 vector print
template <class T>
ostream &operator<<(ostream &s, vector<vector<T>> vec2) {
    for (int i = 0; i < (int)vec2.size(); ++i) {
        s << vec2[i];
    }
    return s;
}
template <class T>
vector<T> make_vec(size_t a) {
    return vector<T>(a);
}
template <class T, class... Ts>
auto make_vec(size_t a, Ts... ts) {
    return vector<decltype(make_vec<T>(ts...))>(a, make_vec<T>(ts...));
}
template <class T>
bool chmax(T &a, const T &b) {
    if (a < b) {
        a = b;
        return 1;
    }
    return 0;
}
template <class T>
bool chmin(T &a, const T &b) {
    if (b < a) {
        a = b;
        return 1;
    }
    return 0;
}

bool is_power_of_two(int n) {
    return (n & (n - 1)) == 0;
}

using ll = long long;
using ull = unsigned long long;
const int INF = 1e9;

struct Rand {
    /*
    乱数生成
    */
    unsigned int x, y, z, w;
    Rand(void) {
        x = 123456789;
        y = 362436069;
        z = 521288629;
        w = (unsigned)time(NULL);
    }
    Rand(unsigned int seed) {
        x = 123456789;
        y = 362436069;
        z = 521288629;
        w = seed;
    }
    inline unsigned int get(void) {
        unsigned int t;
        t = (x ^ (x << 11));
        x = y;
        y = z;
        z = w;
        w = (w ^ (w >> 19)) ^ (t ^ (t >> 8));
        return w;
    }
    inline double getUni(void) {  // 一様乱数 [0,1)
        return (get() + 0.5) * (1.0 / UINT_MAX);
    }
    inline int get(int a) {  // [0, a) の int
        return (int)(a * getUni());
    }
    inline int get(int a, int b) {  // [a, b) の int
        return a + (int)((b - a) * getUni());
    }
    inline long long get(long long a) {  // [0, a) の long long
        return (long long)(a * getUni());
    }
    inline long long get(long long a, long long b) {  // [a, b) の long long
        return a + (long long)((b - a) * getUni());
    }
    inline double get(double a, double b) {  // [a, b) の double
        return a + (b - a) * getUni();
    }
};

// 制限時間(s)
double TIME_LIMIT = 1.9;
// 温度 (問題によって調整する)
double START_TEMP = 40;
double END_TEMP = 10;
// 追加: スコア差分の絶対値の総和と参照回数
double total_score_diff = 0.0;
int score_diff_count = 0;
// 乱数
Rand rnd;

// 状態
struct State {
    State() {
        init();
    }
    void init() {
        // 初期化: ランダムや貪欲などで最後まで1つ構成
    }
    int score() {
        // スコア計算: 現在の状態からスコアを計算
        return 1;
    }
    void transition_to_neighbour() {
        // 遷移関数: 軽い計算でなるべく小さい変化になるように状態を近傍へ変化
        // コツ：近傍の種類を増やしてそれぞれをどのように確率的に選択するのかを考える
    }
    void back_state() {
        // 遷移した状態を戻す
    }
};

State simulated_annealing() {
    // 時間
    double start_clock = clock();
    ll iteration_num = 0;

    // 状態
    State state;
    State best_state = state;
    int best_score = best_state.score();
    while (true) {  // 制限時間まで実行する
        // 時間オーバーか確認
        double now_clock = clock();
        iteration_num++;
        double elapsed_time = (now_clock - start_clock) / CLOCKS_PER_SEC;
        if (elapsed_time > TIME_LIMIT) break;

        // 近傍へ遷移
        int pre_score = state.score();
        state.transition_to_neighbour();
        int new_score = state.score();

        // ベストスコアを更新
        if (best_score < new_score) {  // スコア最大化の場合
            best_state = state;        // そのままコピーすると非常に時間がかかるので、差分更新できるようにするか要素が大きいものに関しては状態で持たない
            best_score = new_score;
        }

        // スコア差分の絶対値の総和と参照回数を更新
        total_score_diff += abs(new_score - pre_score);
        score_diff_count++;
        // 参照回数が2の累乗になったときに最高温度を更新
        if (is_power_of_two(score_diff_count)) {
            START_TEMP = total_score_diff / score_diff_count;
        }

        // 温度とスコアにより遷移するか決定
        double temp = START_TEMP + (END_TEMP - START_TEMP) * (elapsed_time / TIME_LIMIT);
        double prob = exp((new_score - pre_score) / temp);  // スコア最大化の場合
        if (prob > rnd.getUni()) {
            // 遷移したまま
        } else {
            // 戻す
            state.back_state();
        }
    }

    debug(iteration_num);
    cerr << best_score << endl;  // 値チェックに必要(最後に出力)
    return best_state;
}

int main() {
    // 入力
    //

    // State best_state = simulated_annealing();
    for (int i = 0; i < 20; i++) {
        cerr << rnd.getUni() << endl;
    }
    return 0;
}
