#include <bits/stdc++.h>
#define x first
#define y second
using namespace std;

char a[505][505];
int N , M;

pair<int , int> pos[4];

int main(){
    cin >> N >> M;
    for(int i = 1; i <= N; ++i){
        cin >> (a[i] + 1);
    }
    // top left
    int f = 1;
    for(int i = 1; i <= N && f; ++i){
        for(int j = 1; j <= M && f; ++j){
            if(a[i][j] == 'X'){
                pos[0] = {i , j}; f = 0;
            }
        }
    }
    // top right
    f = 1;
    for(int i = 1; i <= N && f; ++i){
        for(int j = M; j >= 1 && f; --j){
            if(a[i][j] == 'X'){
                pos[1] = {i , j}; f = 0;
            }
        }
    }
    // bottom left
    f = 1;
    for(int i = N; i >= 1 && f; --i){
        for(int j = 1; j <= M && f; ++j){
            if(a[i][j] == 'X'){
                pos[2] = {i , j}; f = 0;
            }
        }
    }
    // bottom right
    f = 1;
    for(int i = N; i >= 1 && f; --i){
        for(int j = M; j >= 1 && f; --j){
            if(a[i][j] == 'X'){
                pos[3] = {i , j}; f = 0;
            }
        }
    }
    if(pos[0].x == 0 && pos[0].y == 0){
        // no X
        cout << "NO" << endl;
        return 0;
    }
    if(pos[0].x != pos[1].x){
        cout << "NO" << endl;
        return 0;
    }
    if(pos[2].x != pos[3].x){
        cout << "NO" << endl;
        return 0;
    }
    if(pos[0].y != pos[2].y){
        cout << "NO" << endl;
        return 0;
    }
    if(pos[1].y != pos[3].y){
        cout << "NO" << endl;
        return 0;
    }
    int ok = 1;
    for(int i = pos[0].x; i <= pos[2].x; ++i){
        for(int j = pos[0].y; j <= pos[3].y; ++j){
            ok &= a[i][j] == 'X';
        }
    }
    if(ok){
        cout << "YES" << endl;
    }
    else{
        cout << "NO" << endl;
    }
}