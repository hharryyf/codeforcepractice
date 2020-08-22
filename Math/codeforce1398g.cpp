#include <bits/stdc++.h>
using namespace std;
const int maxn = 4e5 + 20;
const double PI = acos(-1.0);
const double eps = 1e-6;
int N, Q;
int a[maxn >> 1];
int ans[1000005];

struct DFT {
    struct Complex{
        double x , y;
        Complex(){}
        Complex(double x_ , double y_) : x(x_) , y(y_) {}
        Complex operator - (const Complex& oth) const {
            return Complex(x - oth.x , y - oth.y);
        }
        Complex operator + (const Complex& oth) const {
            return Complex(x + oth.x , y + oth.y);
        }
        Complex operator * (const Complex& oth) const {
            return Complex(x * oth.x - y * oth.y , x * oth.y + y * oth.x);
        }
    };

    Complex A[maxn << 2] , B[maxn << 2] , C[maxn << 2];
    int N , M , L;
    void init(int n , int m){
        N = n; M = m;
    }

    void change(Complex y[] , int len) {
        int i, j, k;
        for (i = 1, j = len >> 1; i < len - 1; i++) {
            if (i < j) swap(y[i], y[j]);
            k = len / 2;
            while (j >= k) {
                j = j - k;
                k = k / 2;
            }
            if (j < k) j += k;
        }
    }

    void FFT(Complex y[] , int len , int on) {
        change(y, len);
        for (int h = 2; h <= len; h <<= 1) {
            Complex wn(cos(2 * PI / h), sin(on * 2 * PI / h));
            for (int j = 0; j < len; j += h) {
                Complex w(1, 0);
                for (int k = j; k < j + h / 2; k++) {
                    Complex u = y[k];
                    Complex t = w * y[k + h / 2];
                    y[k] = u + t;
                    y[k + h / 2] = u - t;
                    w = w * wn;
                }
            }
        }
        if (on == -1) {
            for (int i = 0; i < len; i++) {
                y[i].x /= len;
            }
        }
    }

    void multiply(int a[] , int b[]) {
        int len = 1;
        // init length of C
        while(len < 2 * N || len < 2 * M) len <<= 1;
        L = len;
        // init polynomial A and B   
        for(int i = 0; i < N; ++i){
            A[i] = Complex(a[i] == 1 , 0);
        }

        for(int i = 0; i < M; ++i){
            B[i] = Complex(b[i] == 1 , 0);
        }
       
        FFT(A , len , 1);
        FFT(B , len , 1);

        for(int i = 0; i < len; ++i){
            C[i] = A[i] * B[i];
        }
        
        FFT(C , len , -1);
    }
};

DFT dt;
int fst[maxn << 2], sec[maxn << 2];
set<int> st;

int main() {
    int i, X, Y, K;
    memset(ans, -1, sizeof(ans));
    scanf("%d%d%d", &N, &X, &Y);
    for (i = 0 ; i <= N; ++i) {
        scanf("%d", &a[i]);
    }

    K = X;
    dt.init(2 * X + 1, 2 * X + 1);

    // we want to find all possible values of a[i] - a[j]
    // we consider the transform r = K - a[i], t = a[i]
    // then convolt(x^r, y^t) can give us the answer
    for (i = 0 ; i <= N; ++i) {
        ++fst[K - a[i]];
        ++sec[a[i]];
    }

    dt.multiply(fst, sec);

    for (i = 0 ; i < dt.L; ++i) {
        if (dt.C[i].x > eps && i > K) {
            st.insert(2 * (i - K) + 2 * Y);
        }
    }

    for (auto &s : st) {
        for (i = s; i <= 1000000; i += s) {
            ans[i] = s;
        }
    }

    scanf("%d", &Q);
    while (Q-- > 0) {
        int v;
        scanf("%d", &v);
        printf("%d\n", ans[v]);
    }
    return 0;
}