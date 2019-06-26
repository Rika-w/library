#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cmath>
#include<cctype>
#include<math.h>
#include<string>
#include<string.h>
#include<stack>
#include<queue>
#include<vector>
#include<utility>
#include<set>
#include<map>
#include<stdlib.h>
#include<iomanip>

using namespace std;

#define ll long long
#define ld long double
#define EPS 0.0000000001
#define INF 1e9
#define LINF (ll)INF*INF
#define MOD 1000000007
#define rep(i,n) for(int i=0;i<(n);i++)
#define loop(i,a,n) for(int i=a;i<(n);i++)
#define all(in) in.begin(),in.end()
#define shosu(x) fixed<<setprecision(x)

#define int ll //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

typedef vector<int> vi;
typedef vector<string> vs;
typedef pair<int,int> pii;
typedef vector<pii> vp;

int gcd(int a, int b){
    if(b==0) return a;
    return gcd(b,a%b);
}
int lcm(int a, int b){
    return a/gcd(a,b)*b;
}

class LCA{
private:
    int n,h;
    struct edge { int to, cost;};
    vector< vector<edge> > g;
    vector<vector<int> > par;
    vector<int> dist,dep;

    void dfs(int now, int p, int d, int cost){
        par[0][now] = p;
        dep[now] = d;
        dist[now] = cost;
        for(int i = 0; i < g[now].size(); i++){
            int ne = g[now][i].to;
            if(ne != p) dfs(ne, now, d + 1, cost + g[now][i].cost);
        }
    }

public:

    LCA(){}

    LCA(int size){
        n = size;
        g.resize(n);
        dist.resize(n,0);
        dep.resize(n,0);
        h = 1;
        while((1<<h) <= n)h++;
        par.assign(h,vector<int>(n,-1));
    }

    void add(int a, int b, int c){//無向辺
        edge e1 = {b, c}, e2 = {a, c};
        g[a].push_back(e1);
        g[b].push_back(e2);//有向辺の場合はここをコメントアウトする
    }

    void build(int root = 0){
        dfs(root,-1,0,0);
        for(int k = 0; k+1 < h; k++){
            for(int v = 0; v < n; v++){
                if(par[k][v] < 0) par[k+1][v] = -1;
                else par[k+1][v] = par[k][par[k][v]];
            }
        }
    }

    int lca(int a, int b){//頂点ABのLCAのindex
        if(dep[a] > dep[b]) swap(a,b);
        for(int k = 0; k < h; k++){
            if((dep[b] - dep[a]) >> k & 1){
                b = par[k][b];
            }
        }
        if(a == b) return a;
        for(int k = h-1; k >= 0; k--){
            if(par[k][a] != par[k][b]){
                a = par[k][a];
                b = par[k][b];
            }
        }
        return par[0][a];
    }

    int distance(int a, int b){//頂点ABのパスの長さ
        return dist[a] + dist[b] - dist[lca(a,b)]*2;
    }

};

//AOJ http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_5_C
//http://judge.u-aizu.ac.jp/onlinejudge/review.jsp?rid=3689481#1
void GRL5C(){
    int n;
    cin >> n;
    LCA lca(n);
    rep(i,n){
        int k;
        cin >> k;
        rep(j,k){
            int to;
            cin >> to;
            lca.add(i,to,1);
        }
    }
    lca.build();
    int q;
    cin >> q;
    while(q--){
        int a,b;
        cin >> a >> b;
        cout << lca.lca(a,b) << endl;
    }
}

signed main(void) {

    GRL5C();

}
//一応
//https://atcoder.jp/contests/abc014/tasks/abc014_4
