#include <bits/stdc++.h>
#include <windows.h>
#define N 3
#define N2 9
#define LMT 40
#define TMS 1
using namespace std;

static const int dx[4] = {0,-1,0,1};
static const int dy[4] = {1,0,-1,0};

int tr[N][N] = {{1,2,3},{4,5,6},{7,8,0}};
//int tr[N][N] = {{1,2,3},{8,0,4},{7,6,5}};

struct Puzzle{
    int f[N][N];
    int space,df,befspace;
    int cost=0;
    bool operator < (const Puzzle &p) const {
        for(int i=0;i<N;i++){
            for(int j=0;j<N;j++){
                if(f[i][j]==p.f[i][j]) continue;
                return f[i][j] < p.f[i][j];
            }
        }
        return false;
    }
};

struct state{
    Puzzle pzl;
    int cst;
    bool operator < (const state &s) const{
        return cst > s.cst;
    }
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

int value(Puzzle in){
    int ret = 0;
    /*for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            if(tr[i][j]!=in.f[i][j]){
                ret++;
            }
        }
    }*/
    return ret;
}

int bfs(Puzzle in){
    priority_queue<state> q;
    state init;
    map<Puzzle,bool> V;
    in.df = value(in);
    init.pzl = in;
    init.cst = value(in);
    V[in] = true;
    q.push(init);
    while(!q.empty()){
        state tpst = q.top();q.pop();
        Puzzle tp = tpst.pzl;
        //if(tp.df==0) return tp.cost;
        V[tp] = true;
        int sx = tp.space/N;
        int sy = tp.space%N;
        for(int i=0;i<4;i++){
            int tx = sx + dx[i];
            int ty = sy + dy[i];
            if(tx>=N||ty>=N||tx<0||ty<0) continue;
            if(tx*N+ty==tp.befspace) continue;
            Puzzle tmp = tp;
            swap(tmp.f[tx][ty],tmp.f[sx][sy]);
            tmp.space = tx*N+ty;
            tmp.befspace = tp.space;
            if(issolved(tmp)) return tmp.cost;
            if(!V[tmp]){
                tmp.cost++;
                tmp.df = value(tmp);
                state tmpst;
                tmpst.pzl = tmp;
                tmpst.cst = value(tmp)+tmp.cost;
               q.push(tmpst);
            }
        }
    }
    return -1;
}

int main(){

    Puzzle in;
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            cin >> in.f[i][j];
            if(in.f[i][j]==0){
                in.f[i][j]=0;
                in.space = i*N+j;
            }
        }
    }
    if(issolved(in)){
        cout << 0 << endl;
        exit(0);
    }
    for(int i=0;i<TMS;i++){
        LARGE_INTEGER start, end,freq;
        QueryPerformanceFrequency(&freq);
        QueryPerformanceCounter(&start);
        int ans = bfs(in);
        QueryPerformanceCounter(&end);
        cout << "Answer is:" << ans+1 << endl;
        cout << "solve time is:" << (double)(end.QuadPart-start.QuadPart)/freq.QuadPart << endl;
    }
    return 0;
}