
class BellmanFord{
private:
    struct edge{int from,to,cost;};
    int n;
    vector<int> used,reach;
    vector<edge> es;
    vector<vector<int> > g;
    void dfs(int v){
        if(used[v])return;
        used[v]++;
        for(int u: g[v])dfs(u);
    }
public:
    BellmanFord(){}
    BellmanFord(int size){
        n = size;
        g = vector<vector<int> >(size);
    }
    void add_edge(int a, int b, int c){
        edge e = {a,b,c};
        es.push_back(e);
        g[a].push_back(b);
    }
    int ans = 0;
    bool calc(int from, int to){//O(N^2+NM)
        reach = vector<int>(n,0);
        for(int i = 0; i < n; i++){
            used = vector<int>(n,0);
            dfs(i);
            reach[i] = used[to];
        }
        const int MAX = INF;//LINF
        vector<int> ds(n,MAX);
        ds[from] = 0;
        for(int i = 0; i < n; i++){
            bool update = 0;
            for(auto e :es){
                if(!reach[e.from] || !reach[e.to] || ds[e.from] == MAX)continue;
                if(ds[e.to] > ds[e.from] + e.cost){
                    ds[e.to] = ds[e.from] + e.cost;
                    update = 1;
                }
            }
            if(!update)break;
            if(i == n-1){
                ans = MAX;
                return false;//負閉路検出
            }
        }
        ans = ds[to];
        return true;//正常な値がansに入った
    }
};
