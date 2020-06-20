//EDPC V
//https://atcoder.jp/contests/dp/submissions/14120081
//逆元なしでできる
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
#include<complex>
#include <cassert>

using namespace std;

#define ll long long
#define ld long double
#define INF 1e9
#define LINF (ll)INF*INF
#define MOD 1000000007
#define rep(i,n) for(int i=0;i<(n);i++)
#define loop(i,a,n) for(int i=a;i<(n);i++)
#define all(in) in.begin(),in.end()
#define shosu(x) fixed<<setprecision(x)

#define int ll //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

const double PI=acos(-1);
const double EPS=1e-9; //うまくいかなかったらゆるめる

typedef vector<int> vi;
typedef vector<string> vs;
typedef pair<int,int> pii;
typedef pair<pii,int> ppi;
typedef pair<int,pii> pip;
typedef vector<pii> vp;
typedef vector<vi> vvi;

int gcd(int a, int b){if(b==0) return a;return gcd(b,a%b);}
int lcm(int a, int b){return a/gcd(a,b)*b;}

struct edge{
  int to, cost;
};
vector<vector<edge> >g;
vector<int> d;
int m;

void dfs(int now, int par){
    int ret = 1;
    for(auto e: g[now])if(e.to != par){
        dfs(e.to,now);
        ret *= d[e.to]+1;
        ret %= m;
    }
    d[now] = ret;
}

void dfs2(int now, int d_par, int par){
    vi d_child;
    for(auto e: g[now]){
        if(e.to == par){
            d_child.push_back(d_par+1);
        }else{
            d_child.push_back(d[e.to]+1);
        }
    }
    vi d_child_rev = d_child;
    rep(i,d_child.size()-1){
        d_child[i+1] *= d_child[i];
        d_child[i+1] %= m;
        d_child_rev[d_child.size()-i-2] *= d_child_rev[d_child.size()-i-1];
        d_child_rev[d_child.size()-i-2] %= m;
    }
    d[now] = d_child.back() % m;
    rep(i,g[now].size())if(g[now][i].to != par){
        edge e = g[now][i];
        int d_next = 1;
        if(i)d_next *= d_child[i-1];
        if(i+1 < g[now].size())d_next *= d_child_rev[i+1];
        d_next %= m;
        dfs2(e.to, d_next, now);
    }
}

signed main(void) {
    int n;
    cin >> n >> m;
    g.resize(n);
    d = vi(n,0);
    rep(i,n-1){
        int a,b,c;
        cin >> a >> b;
        a--,b--;
        edge e1 = {b,1};
        g[a].push_back(e1);
        edge e2 = {a,1};
        g[b].push_back(e2);
    }
    if(n == 1){
        cout << 1 << endl;
        return 0;
    }
    dfs(0,-1);
    //rep(i,n)cout << d[i] << endl;
    dfs2(0,0,-1);
    //rep(i,n)cout << d[i] << endl;
    rep(i,n){
        cout << d[i] << endl;
    }
}

/*逆元あり

// 全方位で木の直径を求める : http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_5_A&lang=jp
// http://judge.u-aizu.ac.jp/onlinejudge/review.jsp?rid=4549207#1

// 根からの距離と逆辺の数をもつ : https://atcoder.jp/contests/njpc2017/tasks/njpc2017_e
// https://atcoder.jp/contests/njpc2017/submissions/14086004

// 木の上で期待値DP : https://atcoder.jp/contests/s8pc-4/tasks/s8pc_4_d
// https://atcoder.jp/contests/s8pc-4/submissions/14109945

*/
