
struct edge { int to, cost;}
typedef pair<int,int> pii; //最短距離、頂点



vi dijkstra(int s, const vector<edge> &g){
    priority_queue< pii, vector<pii>, greater<pii> > q;
    int n = g.size();
    vi d(n, INF);
    d[s] = 0;
    q.push(pii(0, s));

    while(!q.empty()){
        pii p = q.top();
        q.pop();
        int v = p.second;
        if(d[v] < p.first)continue; //更新されていたら何もしない
        for(int i = 0; i < g[v].size(); i++){
            edge e = g[v][i];
            if(d[e.to] > d[v] + e.cost){
                d[e.to] = d[v] + e.cost;
                q.push(pii(d[e.to], e.to));
            }
        }
    }

    return d;

}
