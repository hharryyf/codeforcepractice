#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
using namespace std;
const int maxn = 3e5 + 11;
const double PI = acos(-1.0);
const double eps = 1e-6;

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
        int i, len = 1;
        // init length of C
        while(len < 2 * N || len < 2 * M) len <<= 1;
        L = len;
        // init polynomial A and B   
        for(i = 0; i < N; ++i){
            A[i] = Complex(a[i], 0);
        }

        for(i = 0; i < M; ++i){
            B[i] = Complex(b[i], 0);
        }

        for (i = N; i < len; ++i) {
            A[i] = Complex(0, 0);   
        }       

        for (i = M; i < len; ++i) {
            B[i] = Complex(0, 0);
        }

        FFT(A , len , 1);
        FFT(B , len , 1);

        for(i = 0; i < len; ++i){
            C[i] = A[i] * B[i];
        }
        
        FFT(C , len , -1);
    }
};

DFT dt;
int a[maxn], b[maxn];
int cost[maxn >> 1][7][7];
char S[maxn], T[maxn];
int N, M;
void solve(char fi, char se) {
    int i;
    dt.init(N + 1, M + 1);
    for (i = 0 ; i < N; ++i) a[i] = (fi == S[i]);
    for (i = 0 ; i < M; ++i) b[i] = (se == T[i]);
    dt.multiply(a, b);
    for (i = 0 ; i < dt.L; ++i) {
        if (i >= M - 1 && i < N) {
            cost[i][fi - 'a'][se - 'a'] += (dt.C[i].x > 0.5);
        }
    }
}

int f[14];

void init() {
    int i;
    for (i = 0 ; i < 14; ++i) {
        f[i] = i;
    }
}

int find(int x) {
    if (f[x] == x) return x;
    return f[x] = find(f[x]);
}

void unionset(int x, int y) {
    x = find(x), y = find(y);
    f[x] = y;
}

int main() {
    int i, j, k;
    scanf("%s", S);
    scanf("%s", T);
    N = strlen(S), M = strlen(T);
    reverse(T, T + M);
    for (i = 0 ; i < 6; ++i) {
        for (j = 0; j < 6; ++j) {
            if (i != j) {
                solve(i + 'a', j + 'a');
            }
        }
    }

    for (i = M - 1; i < N; ++i) {
        init();
        int cnt = 0;
        for (j = 0 ; j < 6; ++j) {
            for (k = 0; k < 6; ++k) {
                if (cost[i][j][k] && find(j) != find(k)) {
                    unionset(j, k);
                    ++cnt;
                }
            }
        }
        printf("%d ", cnt);
    }
    return 0;
}