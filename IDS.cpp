#include <bits/stdc++.h>
#include <windows.h>
#define N 3
#define N2 9
#define LMT 40
using namespace std;


int limit=0;
static const int dx[4] = {0,-1,0,1};
static const int dy[4] = {1,0,-1,0};

int tr[N][N] = {{1,2,3},{4,5,6},{7,8,0}};
//int tr[N][N] = {{1,2,3},{8,0,4},{7,6,5}};

struct Puzzle{
    int f[N][N];
    int space;
    int cost=0;
};

bool issolved(Puzzle in){
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            if(tr[i][j]!=in.f[i][j]){
                return false;
            }
        }
    }
    return true;
}

bool dfs(Puzzle in,int dpt){
    if(issolved(in)) return true;
    if(dpt>limit) return false;
    int sx = in.space/N;
    int sy = in.space%N;
    bool cst = false;
    for(int i=0;i<4;i++){
        int tx = sx + dx[i];
        int ty = sy + dy[i];
        Puzzle tp = in;
        if(tx>=N||ty>=N||tx<0||ty<0) continue;
        swap(tp.f[tx][ty],tp.f[sx][sy]);
        tp.space = tx*3+ty;
        cst = cst | dfs(tp,dpt+1);
        tp = in;
    }
    return cst;
}

int main(){

    Puzzle in;
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            cin >> in.f[i][j];
            if(in.f[i][j]==0){
                in.f[i][j]=0;
                in.space = i*3+j;
            }
        }
    }
    for(int i=0;i<3;i++){
        LARGE_INTEGER start, end,freq;
        QueryPerformanceFrequency(&freq);
        QueryPerformanceCounter(&start);
        QueryPerformanceCounter(&start);
        for(int i=0;i<LMT;i++){
            if(dfs(in,0)){
                break;
            }
            limit++;    
        }
        QueryPerformanceCounter(&end);
        cout << "Answer is:" << limit+1 << endl;
        cout << "solve time is:" << (double)(end.QuadPart-start.QuadPart)/freq.QuadPart << endl;
    }
    return 0;
}