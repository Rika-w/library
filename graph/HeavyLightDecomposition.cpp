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
	void dfs2(int now, vector<long long> &cost){
		idx[now] = et;
		et++;
		rep(i,g[now].size())if(g[now][i].to != par[now]){
			edge e = g[now][i];
			if(i){
				head[e.to] = e.to;
			}else{
				head[e.to] = head[now];
			}
			cost.push_back(e.cost);
			dfs2(e.to,cost);
		}
	}

	class LazySegmentTree{
	private:
		int n;
		vector<long long> node, lazy;
		long long node_init = 0; // sum, max, update
		//long long node_init = LINF; // min
		long long lazy_init = 0; // default
		//long long lazy_init = LINF; // min, update (存在しない値)

		long long lazy_update(long long a,long long b){
			return a+b; // sum query
			//return max(a,b); // max query
			//return min(a,b); // min query
			//return b; // update query
		}

		long long node_update(long long a, long long b, int l, int r){ // lazy を node に反映
			return a+b;
			//return a + b; // min query
			//return b; // update query
			//return b * (r-l); // sum query
            //return max(a,b);
		}

	public:
        long long combine(long long a,long long b){
			return a+b; // sum query
			//return max(a,b); // max query
			//return min(a,b); // min query
		}

		LazySegmentTree(){}
		LazySegmentTree(vector<long long> in){
			n = 1;
			while(n < in.size())n <<= 1;
			node = vector<long long>(2*n, node_init);
			lazy = vector<long long>(2*n, lazy_init);
			for(int i = n-1+in.size()-1; i >= 0; i--){
				if(n-1 <= i)node[i] = in[i-(n-1)];
				else node[i] = combine(node[i*2+1], node[i*2+2]);
			}
		}
		void eval(int k, int l, int r){
			if(lazy[k] != lazy_init){
				node[k] = node_update(node[k], lazy[k], l, r);
				if(r - l > 1){
					lazy[2*k+1] = lazy_update(lazy[2*k+1], lazy[k]);
					lazy[2*k+2] = lazy_update(lazy[2*k+2], lazy[k]);
				}
				lazy[k] = lazy_init;
			}
		}
		void update(int a, int b, long long x, int k = 0, int l = 0, int r = -1){
			//cout <<"update" << a << " " << b << " " << x << " " << l << " " << r << endl;
			if(r < 0)r = n;
			eval(k,l,r);
			if(b <= l || r <= a)return;
			if(a <= l && r <= b){
				lazy[k] = lazy_update(lazy[k],x);///!!
				eval(k,l,r);
			}else{
				update(a,b,x,2*k+1,l,(l+r)/2);
				update(a,b,x,2*k+2,(l+r)/2,r);
				node[k] = combine(node[2*k+1], node[2*k+2]);
			}
		}
		long long query(int a, int b, int k = 0, int l = 0, int r = -1){
			if(r < 0)r = n;
			if(b <= l || r <= a)return node_init;
			eval(k,l,r);
			if(a <= l && r <= b)return node[k];
			return combine(query(a,b,2*k+1,l,(l+r)/2), query(a,b,2*k+2,(l+r)/2,r));
		}
		void show(){
			cout << "node :";
			for(int i = 0; i < 2*n-1; i++){
				if(i == n-1)cout << "     ";
				cout << " " << node[i];
			}
			cout << endl;
			cout << "lazy :";
			for(int i = 0; i < 2*n-1; i++){
				if(i == n-1)cout << "     ";
				cout << " " << lazy[i];
			}
			cout << endl;
		}
	};
	LazySegmentTree lst;
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
		vector<long long> cost;
		dfs2(root,cost);
		lst = LazySegmentTree(cost);
		//lst.show();
	}
	int lca(int u, int v){
		if(idx[u] > idx[v])swap(u,v);
		// u < v
		if(head[u] == head[v])return u;
		return lca(u,par[head[v]]);
	}

	int query(int u, int v){
		if(idx[u] > idx[v])swap(u,v);
		// u < v
		//cout << "query:" << u << " " << v << " " << head[v] << endl;
		if(head[u] == head[v])return lst.query(idx[u],idx[v]);
		return lst.combine(query(u,par[head[v]]),lst.query(idx[head[v]]-1,idx[v]));
	}
	void add(int u, int v, int x){
		if(idx[u] > idx[v])swap(u,v);
		// u < v
		//cout << "add:" << u << " " << v << " " << head[v] << endl;
		if(head[u] == head[v]){
			lst.update(idx[u],idx[v],x);
		}else{
			lst.update(idx[head[v]]-1,idx[v],x);
			add(u,par[head[v]],x);
		}
	}
	void add_par(int v, int x){//vとvの親の間の辺を+xする
		add(v, par[v],x);
	}
	void show(){
		cout << "idx:";
		for(auto x: idx)cout << " " << x;cout << endl;
		lst.show();
	}
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

//verify : http://judge.u-aizu.ac.jp/onlinejudge/review.jsp?rid=4654825#1
void grl5d(){
	int n;
	cin >> n;
	HeavyLightDecomposition hld(n);
	rep(i,n){
		int k;
		cin >> k;
		while(k--){
			int c;
			cin >> c;
			hld.add_edge(i,c,0);
		}
	}
	hld.build(0);
	int q;
	cin >> q;
	while(q--){
		int cond;
		cin >> cond;
		if(cond){
			int u;
			cin >> u;
			//0からuのsumを答える
			cout << hld.query(0,u) << endl;
		}else{
			int v, w;
			cin >> v >> w;
			//vとその親の間の辺を+wする
			hld.add_par(v,w);
			//hld.show();
		}
	}
}


int main(){
	//grl5c();
	grl5d();
}
