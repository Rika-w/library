
class Dinic{
private:
    struct edge{int to,cap,rev;};
    vector<vector<edge> > g;
    vector<int> level,iter;
    int n;

    void bfs(int s){//sからの最短距離を計算する
        level = vector<int>(n,-1);
        queue<int> que;
        level[s] = 0;
        que.push(s);
        while(!que.empty()){
            int v = que.front();
            que.pop();
            for(int i = 0; i < g[v].size(); i++){
                edge &e = g[v][i];
                if(e.cap > 0 && level[e.to] < 0){
                    level[e.to] = level[v] + 1;
                    que.push(e.to);
                }
            }
        }
    }

    int dfs(int v, int t, int f){//増加パスを探す
        if(v == t)return f;
        for(int &i = iter[v]; i < g[v].size(); i++){
            edge &e = g[v][i];
            if(e.cap > 0 && level[v] < level[e.to]){
                int d = dfs(e.to, t, min(f,e.cap));
                if(d > 0){
                    e.cap -= d;
                    g[e.to][e.rev].cap += d;
                    return d;
                }
            }
        }
        return 0;
    }

public:

    Dinic(){}
    Dinic(int size){
        n = size;
        g = vector<vector<edge> >(n);
    }

    void add_edge(int from, int to, int cap){
        g[from].push_back((edge){to,cap,g[to].size()});
        g[to].push_back((edge){from,0,g[from].size()-1});
    }

    int max_flow(int s, int t){//sからtへの最大流  O(EV^2)
        int flow = 0;
        while(1){
            bfs(s);
            if(level[t] < 0)return flow;
            iter = vector<int>(n,0);
            int f;
            while((f = dfs(s, t, INF)) > 0){
                flow += f;
            }
        }
    }

};

void GRL6a(){
    int n,m;
    cin >> n >> m;
    Dinic dinic(n);
    rep(i,m){
        int a,b,c;
        cin >> a >> b >> c;
        dinic.add_edge(a,b,c);
    }
    cout << dinic.max_flow(0,n-1) << endl;
}
signed main(void) {
    GRL6a();
}
