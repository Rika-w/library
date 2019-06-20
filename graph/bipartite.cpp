
class Bipartite{
private:
    vector<vi> g;
    bool c; //is bipartite graph
    int n;
    vector<int> used;
    int cnt[2];

    void dfs(int now){
        cnt[used[now]]++;
        rep(i,g[now].size()){
            int ne = g[now][i];
            if(used[ne] == -1){
                used[ne] = 1 - used[now];
                dfs(ne);
            }else if(used[ne] == used[now]){
                c = false;
                return;
            }
        }
    }

public:
    Bipartite(){};
    Bipartite(int size){
        n = size;
        g = vector<vector<int> > (size);
        used = vector<int> (size);
    }

    void add(int a,int b){//無向辺を追加
        g[a].push_back(b);
        g[b].push_back(a);//有向辺の場合はここをコメントアウト
    }
    vector<pii> p;

    bool is_bipartite(){//二部グラフ判定
        p.clear();
        c = true;
        rep(i,n) used[i] = -1;
        rep(i,n)if(used[i]==-1){
            used[i] = 0;
            cnt[0] = cnt[1] = 0;
            dfs(i);
            if(c==false) return false;
            p.push_back(pii(cnt[0],cnt[1]));
        }

        return true;
    }

    vector<int> split(){//2つにわけるときの分け方
        vector<int> ret;
        if(is_bipartite() == false)return ret;
        int N = p.size();
        set<int> st;
        st.insert(0);
        rep(i,N){
            set<int> nst;
            for(set<int>::iterator itr = st.begin(); itr != st.end(); ++itr){
                nst.insert(*itr + p[i].first);
                nst.insert(*itr + p[i].second);
            }
            st = nst;
        }
        for(set<int>::iterator itr = st.begin(); itr != st.end(); ++itr) ret.push_back(*itr);
        return ret;
    }

};

/*
使い方
Bipartite bi(n);で n 頂点のグラフをつくる
bi.add(a,b);で a,b間に辺をはる
bi.is_bipartite() で二部グラフかどうか判定する、このときbi.pには各連結成分での分けた時の頂点数が入っている
bi.split() で二部グラフだった場合は、分けた時の頂点数の候補がvectorで返ってくる（二部グラフでないときは空）
*/


//http://judge.u-aizu.ac.jp/onlinejudge/review.jsp?rid=3295999#1
//http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2885

signed main(void) {
    int i,j;
    int n,m;
    while(cin >> n >> m, n){
        Bipartite bi(n);
        rep(i,m){
            int a,b;
            cin >> a >> b;
            bi.add(a-1,b-1);
        }
        vi p = bi.split(),ans;
        rep(i,p.size())if(p[i] % 2 == 0)ans.push_back(p[i]/2);
        sort(all(ans));
        cout << ans.size() << endl;
        rep(i,ans.size())cout << ans[i] << endl;
    }
}


/*

#define MAX_N 705

vector<vi> g(MAX_N);
bool c = true; //is bipartite graph

int used[MAX_N];
int cnt[2];

void dfs(int now){
    cnt[used[now]]++;
    rep(i,g[now].size()){
        int ne = g[now][i];
        if(used[ne] == -1){
            used[ne] = 1 - used[now];
            dfs(ne);
        }else if(used[ne] == used[now]){
            c = false;
            return;
        }
    }
}

vector<pii> p;

bool is_bipartite(int n){
    rep(i,n) used[i] = -1;
    rep(i,n)if(used[i]==-1){
        used[i] = 0;
        cnt[0] = cnt[1] = 0;
        dfs(i);
        if(c==false) return false;
        p.push_back(pii(cnt[0],cnt[1]));
    }

    return true;
}*/
/*
二部グラフ判定
使い方
    gに有向辺をいれておく
    is_bipartite(n)でn頂点のグラフgの二部グラフ判定
    二部グラフの場合はpにそれぞれの連結成分を二部彩色したときの頂点数が入る
*/

/*
https://beta.atcoder.jp/contests/arc099/tasks/arc099_c
https://beta.atcoder.jp/contests/arc099/submissions/2929829
*/
/*
int main(void) {
    int i,j;
    int n, m;
    cin >> n >> m;
    int d[700][700];
    rep(i,n)rep(j,n)d[i][j]=1;
    rep(i,m){
        int a,b;
        cin >> a >> b;
        a--,b--;
        d[a][b]--;
        d[b][a]--;
    }
    rep(i,n)rep(j,n)if(d[i][j]==1 && i!=j){
        g[i].push_back(j);
    }


    if(is_bipartite(n) == false){
        cout << -1 << endl;
        return 0;
    }

    int dp[705][705] = {};
    dp[0][0] = 1;
    rep(i,p.size())rep(j,705)if(dp[i][j]){
        dp[i+1][j+p[i].first]++;
        dp[i+1][j+p[i].second]++;
    }
    int ans = INF;
    rep(i,n+1)if(dp[p.size()][i]){
        ans = min(ans, i*(i-1)/2 + (n-i)*(n-i-1)/2);
    }
    cout << ans << endl;
}
*/
