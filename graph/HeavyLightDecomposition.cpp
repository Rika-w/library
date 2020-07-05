#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
#define rep(i,n) for(int i = 0; i < (n); i++)

class HeavyLightDecomposition{
private:
	struct edge{int to,cost;};
	int n;
	vector<vector<edge>> g;
	vector<int> sub;//部分木のサイズ
	vector<int> par,depth;
	vector<int> head;//自分の所属するheavyパスの先頭
	vector<int> idx;//オイラーツアーの番号
	void dfs(int now){
		sub[now] = 1;
		int ma = 0;
		for(auto& e: g[now])if(e.to != par[now]){
			par[e.to] = now;
			depth[e.to] = depth[now] + 1;
			dfs(e.to);
			sub[now] += sub[e.to];
			if(sub[g[now][0].to] < sub[e.to])swap(g[now][0],e);//g[now][0]に部分木が最大であるようなものが来る
		}
	}
	int et = 0;
	void dfs2(int now){
		idx[now] = et;
		et++;
		rep(i,g[now].size())if(g[now][i].to != par[now]){
			edge e = g[now][i];
			if(i){
				head[e.to] = e.to;
			}else{
				head[e.to] = head[now];
			}
			dfs2(e.to);
		}
	}
public:
	HeavyLightDecomposition(int sz){
		n = sz;
		g.resize(n);
		sub.resize(n);
		par.resize(n);
		head.resize(n);
		depth.resize(n);
		idx.resize(n);
	}
	void add_edge(int a, int b, int c){
		g[a].push_back({b,c});
		g[b].push_back({a,c});
	}
	void build(int root){
		par[root] = -1;
		depth[root] = 1;
		dfs(root);
		head[root] = root;
		dfs2(root);
	}
	int lca(int u, int v){
		if(idx[u] > idx[v])swap(u,v);
		// u < v
		if(head[u] == head[v])return u;
		return lca(u,par[head[v]]);
	}
	/*
	int query_sum(int u, int v){
		int x = lca(u,v);


	}
	void add(int v, int x){

	}
	*/
};

//LCA verify : http://judge.u-aizu.ac.jp/onlinejudge/review.jsp?rid=4643677#1
void grl5c(){
	int n;
	cin >> n;
	HeavyLightDecomposition hld(n);
	rep(i,n){
		int k;
		cin >> k;
		rep(_,k){
			int t;
			cin >> t;
			hld.add_edge(i,t,1);
		}
	}
	hld.build(0);
	int q;
	cin >> q;
	while(q--){
		int u,v;
		cin >> u >> v;
		cout << hld.lca(u,v) << endl;
	}
}

int main(){
	grl5c();
}
