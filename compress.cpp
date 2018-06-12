//http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_4_A&lang=jp
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cmath>
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
#define MOD 1000000007
#define rep(i,n) for(i=0;i<n;i++)
#define loop(i,a,n) for(i=a;i<n;i++)
#define all(in) in.begin(),in.end()
#define shosu(x) fixed<<setprecision(x)

typedef vector<int> vi;
typedef pair<int,int> pii;

int grid[5005][5005];

void compress(vi &v){
  sort(all(v));
  v.erase(unique(all(v)),v.end());
}

void cumulativesum(int h,int w){
  int i,j;
  rep(i,h)rep(j,w-1) grid[i][j+1]+=grid[i][j];//yoko
  rep(j,w)rep(i,h-1) grid[i+1][j]+=grid[i][j];//tate
}

int sum(int i,int j,int k,int l){//y,xで渡す（小大
  return grid[k][l]-grid[i][l]-grid[k][j]+grid[i][j];
}

int main(void) {
  int i,j;
  int n;
  cin>>n;
  pair<pii,pii> p[5000];
  vi x,y;
  rep(i,n){
    cin>>p[i].first.first>>p[i].first.second>>p[i].second.first>>p[i].second.second;
    x.push_back(p[i].first.first);
    x.push_back(p[i].second.first);
    y.push_back(p[i].first.second);
    y.push_back(p[i].second.second);
  }

  compress(x);
  compress(y);

  rep(i,n){
    int lx=lower_bound(all(x),p[i].first.first)-x.begin();
    int ly=lower_bound(all(y),p[i].first.second)-y.begin();
    int rx=lower_bound(all(x),p[i].second.first)-x.begin();
    int ry=lower_bound(all(y),p[i].second.second)-y.begin();

    grid[lx][ly]++;
    grid[rx][ry]++;
    grid[lx][ry]--;
    grid[rx][ly]--;
  }

  cumulativesum(5000,5000);//累積和


  ll ans=0;
  rep(i,2*n)rep(j,2*n)
    if(grid[j][i]) ans+=(x[j+1]-x[j])*(y[i+1]-y[i]);

  cout<<ans<<endl;
}
