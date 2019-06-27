#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;
#define INF 1e9

//ford-fulkerson
//O(FE)
//計算量が答えの出力（流れる量）に依存
#define MAX_V 10000
struct edge{ int to,cap,rev;};
vector<edge> G[MAX_V];
bool used[MAX_V];
void add_edge(int from, int to, int cap){
    G[from].push_back((edge){to,cap,G[to].size()});
    G[to].push_back((edge){from,0,G[from].size()-1});
}
int dfs(int v, int t, int f){
    if(v == t)return f;
    used[v] = true;
    for(int i = 0; i < G[v].size(); i++){
        edge &e = G[v][i];
        if(!used[e.to] && e.cap > 0){
            int d = dfs(e.to,t, min(f,e.cap));
            if(d > 0){
                e.cap -= d;
                G[e.to][e.rev].cap += d;
                return d;
            }
        }
    }
    return 0;
}

int max_flow(int s, int t){
    int flow = 0;
    while(1){
        memset(used,0,sizeof(used));
        int f = dfs(s, t, INF);
        if(f == 0)return flow;
        flow += f;
    }
}

int main(){
    int s = 0, t = 1,f = 1;
    add_edge(s,t,f);//sからtに流量fの辺をはる
    int ans = max_flow(s,t);//sからtの最大流を求める
}
