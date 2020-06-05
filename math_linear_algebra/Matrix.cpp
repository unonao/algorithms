/* Matrix.cpp
    行列演算用ライブラリ

    verified:
    ・AOJ ITP1_7_D Matrix Multiplication
        http://judge.u-aizu.ac.jp/onlinejudge/review.jsp?rid=4551007#1
    ・AtCoder Educational DP contest R - Walk
        https://atcoder.jp/contests/dp/tasks/dp_r
*/
#include <bits/stdc++.h>
using namespace std;

/* Matrix
    + (行列との和): O(N^2)
    - (行列との差): O(N^2)
    * (行列との積): O(N^3)
    * (定数との積): O(N^2)
    pow (行列累乗): O(N^3 log k)
    未完成 det (行列式): O(N^3)
*/
template <typename T>
struct Matrix {
    int N, M;
    vector<vector<T>> A;
    Matrix(int N_) : N(N_), M(N_), A(N_, vector<T>(N_)) {}
    Matrix(int N_, int M_) : N(N_), M(M_), A(N_, vector<T>(M_)) {}
    void init_zeros() {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                A[i][j] = 0;
            }
        }
    }
    void init_ones() {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                A[i][j] = 1;
            }
        }
    }
    void init_I() {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                if (i != j) {
                    A[i][j] = 0;
                } else {
                    A[i][j] = 1;
                }
            }
        }
    }
    inline const vector<T> &operator[](int k) const {
        return (A.at(k));
    }
    inline vector<T> &operator[](int k) {
        return (A.at(k));
    }
    Matrix &operator+=(const Matrix &B) {
        assert(this->N == B.N && this->M == B.M);
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                (*this)[i][j] += B[i][j];
            }
        }
        return (*this);
    }
    Matrix &operator-=(const Matrix &B) {
        assert(this->N == B.N && this->M == B.M);
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                (*this)[i][j] -= B[i][j];
            }
        }
        return (*this);
    }
    Matrix &operator*=(const Matrix &B) {
        assert(this->M == B.N);
        int n = this->N;
        int m = B.M;
        int K = this->M;
        Matrix C(n, m);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                for (int k = 0; k < K; k++) {
                    C[i][j] += (*this)[i][k] * B[k][j];
                }
            }
        }
        (*this) = C;
        return (*this);
    }
    Matrix &operator*=(const T &x) {
        int n = this->N;
        int m = this->M;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                (*this)[i][j] = (*this)[i][j] * x;
            }
        }
        return (*this);
    }
    Matrix operator+(const Matrix &B) const { return Matrix(*this) += B; }
    Matrix operator-(const Matrix &B) const { return Matrix(*this) -= B; }
    Matrix operator*(const Matrix &B) const { return Matrix(*this) *= B; }
    Matrix operator*(const T &x) const { return Matrix(*this) *= x; }
    Matrix pow(long long k) const {
        assert(N == M);
        Matrix ret(N);
        Matrix mul = (*this);
        ret.init_I();
        while (k > 0) {
            if (k & 1) ret *= mul;
            mul *= mul;
            k >>= 1;
        }
        return ret;
    }
    friend ostream &operator<<(ostream &os, const Matrix &B) {
        int n = B.N;
        int m = B.M;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                os << B[i][j];
                if (j != m - 1) os << " ";
            }
            os << "\n";
        }
        return (os);
    }
    friend istream &operator>>(istream &is, Matrix &B) {
        int n = B.N;
        int m = B.M;
        T t;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                is >> t;
                B[i][j] = t;
            }
        }
        return (is);
    }
};

int main() {
    int n, m, l;
    cin >> n >> m >> l;
    Matrix<long long> A(n, m), B(m, l);
    cin >> A >> B;
    cout << A * B;
}
