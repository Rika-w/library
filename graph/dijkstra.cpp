
typedef pair<int,int> pii;



class Dijkstra{
private:
    struct edge { int to, cost;};
    vector< vector<edge> > g;

public:
    Dijkstra(){};
    Dijkstra(int size){
        g.resize(size);
    }

    vi dist;

    void add(int a, int b, int c){//無向辺
        edge e1 = {b, c}, e2 = {a, c};
        g[a].push_back(e1);
        g[b].push_back(e2);//有向辺の場合はここをコメントアウトする
    }

    void calc(int s){
        priority_queue< pii, vector<pii>, greater<pii> > q;
        int n = g.size();
        dist = vi (n, INF);
        dist[s] = 0;
        q.push(pii(0, s));

        while(!q.empty()){
            pii p = q.top();
            q.pop();
            int v = p.second;
            if(dist[v] < p.first)continue; //更新されていたら何もしない
            for(int i = 0; i < g[v].size(); i++){
                edge e = g[v][i];
                if(dist[e.to] > dist[v] + e.cost){
                    dist[e.to] = dist[v] + e.cost;
                    q.push(pii(dist[e.to], e.to));
                }
            }
        }
    }

};

/*
使い方

Dijkstra g = Dijkstra(v); で頂点数vのグラフgを宣言
g.add(a,b,c); で g に頂点 a,b 間のコストcの辺(無向辺)を追加 (0-indexed)
g.calc(s); でグラフg上の始点sの最短距離を計算する
g.dist[i]; で頂点sから頂点iの最短距離を返す

*/


/*
2018/5/14
http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_1_A&lang=jp
辺は有向辺であることに注意
*/


int main(void) {
    int i,j;
    int n;
    int v,e,r;
    cin >> v >> e >> r;

    Dijkstra g = Dijkstra(v);

    rep(i,e){
        int a,b,c;
        cin >> a >> b >> c;
        g.add(a,b,c);
    }

    g.calc(r);

    rep(i,v){
        if(g.dist[i] == INF)
            cout << "INF" << endl;
        else
            cout << g.dist[i] << endl;
    }

}

/*
// AOJ 2200 r <= 10

class Dijkstra{
private:
    struct edge { int to, cost, land;};
    struct node {
        int rind, now, boat;
        bool operator >(node const& other) const {
            return rind > other.rind;
        }
        bool operator <(node const& other) const {
            return rind < other.rind;
        }
    };
    typedef pair<int,node> pin;
    vector< vector<edge> > g;

public:
    Dijkstra(){};
    Dijkstra(int size){
        g.resize(size);
    }

    int dist[10][200][200];

    void add(int a, int b, int cost, int land){//無向辺
        edge e1 = {b, cost, land}, e2 = {a, cost, land};
        g[a].push_back(e1);
        g[b].push_back(e2);//有向辺の場合はここをコメントアウトする
    }

    int calc(vi a){
        priority_queue< pin, vector<pin>, greater<pin> > q;
        int n = g.size();
        int r = a.size();
        rep(i,r)rep(j,n)rep(k,n)dist[i][j][k] = LINF;
        dist[0][a[0]][a[0]] = 0;
        node no = {0,a[0],a[0]};
        q.push(pin(0, no));

        while(!q.empty()){
            pin p = q.top();
            q.pop();
            node v = p.second;
            if(dist[v.rind][v.now][v.boat] < p.first)continue; //更新されていたら何もしない
            if(v.rind == r-1)continue;
            for(int i = 0; i < g[v.now].size(); i++){
                edge e = g[v.now][i];
                int x = v.rind + (e.to == a[v.rind+1]);
                if(e.land){//陸
                    if(dist[x][e.to][v.boat] > dist[v.rind][v.now][v.boat] + e.cost){
                        dist[x][e.to][v.boat] = dist[v.rind][v.now][v.boat] + e.cost;
                        node ne = {x, e.to, v.boat};
                        q.push(pin(dist[x][e.to][v.boat],ne));
                    }
                }
                if(e.land == 0 && v.now == v.boat){//海
                    if(dist[x][e.to][e.to] > dist[v.rind][v.now][v.boat] + e.cost){
                        dist[x][e.to][e.to] = dist[v.rind][v.now][v.boat] + e.cost;
                        node ne = {x, e.to, e.to};
                        q.push(pin(dist[x][e.to][e.to],ne));
                    }
                }
            }
        }

        int ret = LINF;
        rep(i,n)ret = min(ret, dist[r-1][a[r-1]][i]);
        return ret;
    }

};

signed main(void) {
    int n,m;
    while(cin >> n >> m, n){
        Dijkstra dij(n);
        rep(i,m){
            int a,b,c;
            string s;
            cin >> a >> b >> c >> s;
            a--,b--;
            dij.add(a, b, c, s == "L");
        }
        int r;
        cin >> r;
        vi in(r);
        rep(i,r)cin >> in[i],in[i]--;
        cout << dij.calc(in) << endl;
    }

}

*/
/*

AOJ2585

class Dijkstra{
private:
    struct edge { int to, cost, tim, com;};
    struct node {
        int ind, tim;
        bool operator >(node const& other) const {
            return tim > other.tim;
        }
        bool operator <(node const& other) const {
            return tim < other.tim;
        }
    };
    typedef pair<int,node> pin;
    vector< vector<edge> > g;
    int n;
public:
    Dijkstra(){};
    Dijkstra(int size){
        n = size;
        g.resize(n);
    }
    int dist[105][25];//頂点iに時刻jでいるときの最小コスト
    void add(int a, int b, int cost, int tim, int com){//無向辺
        edge e1 = {b, cost, tim, com}, e2 = {a, cost, tim, com};
        g[a].push_back(e1);
        g[b].push_back(e2);//有向辺の場合はここをコメントアウトする
    }
    int calc(int s, int t, int ma, int bit){
        priority_queue< pin, vector<pin>, greater<pin> > q;
        rep(i,n)rep(j,ma+1)dist[i][j] = LINF;
        dist[s][0] = 0;
        node no = {s,0};
        q.push(pin(0, no));
        while(!q.empty()){
            pin p = q.top();
            q.pop();
            int now = p.second.ind;
            int tim = p.second.tim;
            if(dist[now][tim] < p.first)continue; //更新されていたら何もしない
            for(int i = 0; i < g[now].size(); i++){
                edge e = g[now][i];
                int cost = e.cost;
                if(bit & (1<<e.com))cost = 0;
                int nexttime = tim + e.tim;
                if(ma < nexttime)continue;//ma以内に到達できない
                if(dist[e.to][nexttime] > dist[now][tim] + cost){
                    dist[e.to][nexttime] = dist[now][tim] + cost;
                    node ne = {e.to, nexttime};
                    q.push(pin(dist[e.to][nexttime],ne));
                }
            }
        }
        int ret = LINF;
        rep(i,ma+1)ret = min(ret, dist[t][i]);
        return ret;
    }
};

signed main(void) {
    int n,m,ma,k;
    while(cin >> n >> m >> ma >> k, n){
        Dijkstra dij(n);
        rep(i,m){
            int a,b,c,h,r;
            cin >> a >> b >> c >> h >> r;
            a--,b--;r--;
            dij.add(a,b,c,h,r);
        }
        int s,t;
        cin >> s >> t;
        s--,t--;
        int p;
        cin >> p;
        vi d(p);
        vector<vi> l(p);
        rep(i,p){
            int a;
            cin >> a >> d[i];
            rep(j,a){
                int b;
                cin >> b;
                b--;
                l[i].push_back(b);
            }
        }
        vi dp(1<<k,LINF);
        dp[0] = 0;
        rep(bit,1<<k){
            rep(j,p){
                int ne = bit;
                rep(k,l[j].size())ne |= (1<<l[j][k]);
                dp[ne] = min(dp[ne], dp[bit]+d[j]);
            }
        }
        int ans = LINF;
        rep(bit,1<<k){
            //パスポートを使って乗れる会社がbitのとき
            int cost = dp[bit];//パスポートの料金
            cost += dij.calc(s,t,ma,bit);//ma時間以内にsからtに向かうときの料金
            ans = min(ans, cost);
        }
        if(ans == LINF)cout << -1 << endl;
        else cout << ans << endl;
    }
}
*/
