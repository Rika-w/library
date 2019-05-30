
class EulerTour{
private:
    int n;
    vector<vector<int> > g;
    vector<vector<int> > ind;//各頂点のインデックス

    void dfs(int now, int par){
        ind[now].push_back(v.size());
        v.push_back(now);
        for(int i = 0; i < g[now].size(); i++){
            if(g[now][i] != par){
                dfs(g[now][i],now);
            }
        }
        ind[now].push_back(v.size());
        v.push_back(now);
    }

public:
    vector<int> v;//オイラーツアーの頂点
    EulerTour(){}
    EulerTour(vector<vector<int> > in, int root){
        g = in;
        n = g.size();
        ind = vector<vector<int> > (n);
        dfs(root, -1);
    }
    void show(){
        rep(i,v.size())cout << " " << v[i]; cout << endl;
    }
    pii get_ind(int i){
        if(i >= n)return pii(INF,INF);
        return pii(ind[i][0], ind[i][1]);
    }

};
