/* fft.cpp
    高速フーリエ変換と畳み込みのアルゴリズム

    verified:
        AtCoder ATC001 C - 高速フーリエ変換
        https://atcoder.jp/contests/atc001/tasks/fft_c
*/

#include <bits/stdc++.h>
using namespace std;

/*  fft(a, inv) : Cooley-Tukey FFT algorithm で高速フーリエ変換
    入力：複素数のベクトル a, 逆高速フーリエ変換かどうかを表す真偽値 inv
    出力：invがfalseなら、FFTの結果
          invがtrueなら、IFFTの結果
    計算量：O(NlogN)
*/
vector<complex<double>> fft(vector<complex<double>> a, bool inv = false) {
    int n = a.size();
    int h = 0;
    for (int i = 1; i < n; i *= 2) {
        h++;
    }
    for (int i = 0; i < n; i++) {  // swap for butterfly
        int j = 0;
        for (int k = 0; k < h; k++) {
            j |= (i >> k & 1) << (h - 1 - k);
        }
        if (i < j) {
            swap(a[i], a[j]);
        }
    }
    for (int block = 1; block < n; block *= 2) {
        for (int j = 0; j < block; j++) {
            complex<double> w = polar(1.0, (2 * M_PI) / (2 * block) * j * (inv ? 1 : -1));
            for (int k = 0; k < n; k += block * 2) {
                complex<double> s = a[j + k];
                complex<double> t = a[j + k + block] * w;
                a[j + k] = s + t;
                a[j + k + block] = s - t;
            }
        }
    }
    if (inv) {
        for (int i = 0; i < n; i++) {
            a[i] /= n;
        }
    }
    return a;
}
vector<complex<double>> fft(vector<double> a, bool inv = false) {
    vector<complex<double>> a_complex(a.size());
    for (int i = 0; i < a.size(); i++) {
        a_complex[i] = complex<double>(a[i], 0);
    }
    return fft(a_complex, inv);
}

/* convolve(a, b) : 畳み込み（sum(a[j]b[k-j])）を計算する
    入力： a, b のベクトル
    出力： sum(a[j]b[k-j])
    計算量：O(NlogN)
*/
vector<double> convolve(vector<double> a, vector<double> b) {
    int s = a.size() + b.size() - 1;
    int t = 1;
    while (t < s) {
        t *= 2;
    }
    a.resize(t);
    b.resize(t);
    vector<complex<double>> A = fft(a);
    vector<complex<double>> B = fft(b);
    vector<complex<double>> C(t);
    for (int i = 0; i < t; i++) {
        C[i] = A[i] * B[i];
    }
    vector<complex<double>> c = fft(C, true);
    a.resize(s);
    for (int i = 0; i < s; i++) {
        a[i] = c[i].real();  // 実部が答え
    }
    return a;
}

int main() {
    int N;
    cin >> N;
    vector<double> a(N + 1), b(N + 1);
    a[0] = b[0] = 0;
    for (int i = 0; i < N; i++) {
        cin >> a.at(i + 1) >> b.at(i + 1);
    }

    vector<double> ans = convolve(a, b);

    for (int i = 1; i < ans.size(); i++) {
        cout << (int)round(ans[i]) << endl;
    }

    return 0;
}
