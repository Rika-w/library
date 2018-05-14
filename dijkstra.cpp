
typedef pair<int,int> pii;


struct edge { int to, cost;};

class Dijkstra{
private:
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
