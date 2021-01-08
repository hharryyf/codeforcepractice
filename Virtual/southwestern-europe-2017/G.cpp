#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1011;
const int inf = 0x3fffffff;

struct KM {
    // warning !! nx <= ny, otherwise, TLE!!!!!!
    int G[maxn][maxn];
    int m;
    int nx,ny;
    int link[maxn],lx[maxn],ly[maxn];
    int slack[maxn];
    bool visx[maxn],visy[maxn];
    
    bool dfs(int x) {
        visx[x]=1;
        for(int y=0;y<ny;y++){
            if(visy[y]) continue;
            int tmp=lx[x]+ly[y]-G[x][y];
            if(tmp==0){
                visy[y]=1;
                if(link[y]==-1||dfs(link[y])){
                    link[y]=x;
                    return true;
                }
            }
            else if(slack[y]>tmp) slack[y]=tmp;
        }
        return false;
    }
    
    int km() {
        memset(link,-1,sizeof(link));
        memset(ly,0,sizeof(ly));
        for(int i=0;i<nx;i++){
            lx[i]=-inf;
            for(int j=0;j<ny;j++){
                if(G[i][j]>lx[i]) lx[i]=G[i][j];
            }
        }
        for(int x=0;x<nx;x++){
            for(int i=0;i<ny;i++) slack[i]=inf;
            while(1){
                memset(visx,0,sizeof(visx));
                memset(visy,0,sizeof(visy));
                if(dfs(x)) break;
                int d=inf;
                for(int i=0;i<ny;i++){
                    if(!visy[i]&&d>slack[i]) d=slack[i];
                }
                for(int i=0;i<nx;i++){
                    if(visx[i]) lx[i]-=d;
                }
                for(int i=0;i<ny;i++){
                    if(visy[i]) ly[i]+=d;
                    else slack[i]-=d;
                }
            }
        }
        int res=0;
        for(int i=0;i<ny;i++){
            if(link[i]!=-1) res+=G[link[i]][i];
        }
        return res;
    }
};

KM mf;
struct point {
    int x, y;
};

point bottle[maxn], car[maxn];
point r;
int N, M;

int dist(point x, point y) {
    return abs(x.x - y.x) + abs(x.y - y.y);
}

int main() {
    int i, j, ok = 0, mn = inf, ans = 0;
    scanf("%d%d", &N, &M);
    for (i = 1; i <= N; ++i) scanf("%d%d", &bottle[i].x, &bottle[i].y);
    for (i = 1; i <= M; ++i) scanf("%d%d", &car[i].x, &car[i].y);
    scanf("%d%d", &r.x, &r.y);
    mf.nx = M, mf.ny = N;
    for (i = 1; i <= N; ++i) {
        ans = ans + 2 * dist(r, bottle[i]);
        for (j = 1; j <= M; ++j) {
            if (dist(car[j], bottle[i]) < dist(r, bottle[i])) {
                ok = 1;
                if (mf.nx > mf.ny) {
                    mf.G[i-1][j-1] = dist(r, bottle[i]) - dist(car[j], bottle[i]);
                } else {
                    mf.G[j-1][i-1] = dist(r, bottle[i]) - dist(car[j], bottle[i]);
                }
            }
            mn = min(mn, dist(car[j], bottle[i]) - dist(r, bottle[i]));
        }
    }

    if (mf.nx > mf.ny) swap(mf.nx, mf.ny);
    if (ok == 0) {
        ans = ans + mn;
    } else {
        ans = ans - mf.km();
    }

    printf("%d\n", ans);
    return 0;
}