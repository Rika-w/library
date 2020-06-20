#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
#define rep(i,n) for(int i = 0; i < (n); i++)
#define int long long
typedef pair<int,int> pii;
typedef vector<int> vi;
#define INF 1e9

// 木のパスに対するクエリに答えられるオイラーツアー
// http://wk1080id.hatenablog.com/entry/2020/05/30/004858

//http://judge.u-aizu.ac.jp/onlinejudge/review.jsp?rid=4596943#1
//http://judge.u-aizu.ac.jp/onlinejudge/review.jsp?rid=4596992#1
class EulerTourQuery{
private:
    struct edge{int to,cost;};
    int n;
    vector<vector<edge>> g; //グラフの隣接リスト
    vector<int> v; //オイラーツアーの頂点配列
    vector<pair<int,int>> ind; //各頂点がオイラーツアー配列の何番目に最初/最後に訪れるか
    vector<int> cost; //オイラーツアーに対応する辺のコスト配列
    vector<int> depth; //オイラーツアーの各頂点の根からの深さ
    void dfs(int now, int par, int d){//今の頂点、親の頂点、根からの深さ
        ind[now].first = v.size();
        v.push_back(now);
        depth.push_back(d);
        for(int i = 0; i < g[now].size(); i++){
            edge e = g[now][i];
            if(e.to != par){
                cost.push_back(e.cost);
                dfs(e.to,now,d+1);
                v.push_back(now);
                depth.push_back(d+1);
                cost.push_back(-e.cost);
            }
        }
        ind[now].second = v.size()-1;
    }

    class SegTree{
    private:
        int n;
        vector<int> seg;
        int init = 0; //初期化の値（単位元）
        int combine(int a, int b){
            return a+b;
        }
    public:
        SegTree (){}
        SegTree(int size){
            n = 1;
            while(n < size) n <<= 1;
            seg = vector<int>(2*n, init);
        }
        SegTree(const vector<int> &in){
            n = 1;
            while(n < in.size()) n <<= 1;
            seg = vector<int>(2*n, init);
            for(int i = n-1 + in.size() - 1; i >= 0; i--){
                if(n-1 <= i)seg[i] = in[i-(n-1)];
                else seg[i] = combine(seg[i*2+1], seg[i*2+2]);
            }
        }
        //k-th(0-indexd) を a にする
        void update(int k, int a){
            k += n-1;
            seg[k] = a;
            while(k > 0){
                k = (k-1)/2;
                seg[k] = combine(seg[k*2+1], seg[k*2+2]);
            }
        }
        //k-th(0-indexd) を +a する
        void add(int k, int a){
            k += n-1;
            seg[k] += a;
            while(k > 0){
                k = (k-1)/2;
                seg[k] = combine(seg[k*2+1], seg[k*2+2]);
            }
        }
        //[a,b)について調べる
        int query(int a, int b, int k = 0, int l = 0, int r = -1){
            if(r == -1) r = n;
            if(r <= a || b <= l)return init;
            if(a <= l && r <= b)return seg[k];
            int vl = query(a, b, k*2+1, l, (l+r)/2);
            int vr = query(a, b, k*2+2, (l+r)/2, r);
            return combine(vl, vr);
        }
        void show(){
            rep(i,n-1)cout << " " << seg[i];cout << endl;
            for(int i = n-1; i < seg.size(); i++)cout << " " << seg[i];cout << endl;
        }
    };

    class SegTreePair{
    private:
        int n;
        vector<pii> seg;
        //minクエリ
        pii init = pii(INF,INF); //初期化の値（単位元）
        pii combine(pii a, pii b){
            if(a.first == b.first && a.second < b.second)return a;
            if(a.first < b.first)return a;
            return b;
        }
        /*
        //maxクエリ
        pii init = pii(-INF,-INF); //初期化の値（単位元）
        pii combine(pii a, pii b){
            if(a.first == b.first && a.second < b.second)return a;
            if(a.first > b.first)return a;
            return b;
        }
        */
    public:
        SegTreePair (){}
        SegTreePair(const vi &in){
            n = 1;
            while(n < in.size())n <<= 1;
            seg = vector<pii>(2*n,init);
            for(int i = n-1 + in.size() - 1; i >= 0; i--){
                if(n-1 <= i)seg[i] = pii(in[i-(n-1)], i-(n-1));
                else seg[i] = combine(seg[i*2+1], seg[i*2+2]);
            }
        }
        //k番目の値を+aする
        void add(int k, int a){
            k += n-1;
            seg[k].first += a;
            while(k > 0){
                k = (k-1)/2;
                seg[k] = combine(seg[k*2+1], seg[k*2+2]);
            }
        }
        //[a,b)について調べる
        pii query(int a, int b, int k = 0, int l = 0, int r = -1){
            if(r == -1) r = n;
            if(r <= a || b <= l)return init;
            if(a <= l && r <= b)return seg[k];
            pii vl = query(a, b, k*2+1, l, (l+r)/2);
            pii vr = query(a, b, k*2+2, (l+r)/2, r);
            return combine(vl, vr);
        }
    };


    SegTree stsum;
    SegTreePair stmin;

public:
    EulerTourQuery(int size){
        n = size;
        g.resize(n);
        ind.resize(n);
    }
    void add_edge(int a, int b, int c){
        g[a].push_back({b,c});
        g[b].push_back({a,c});
    }
    void build(int root){
        dfs(root,-1,0);
        stsum = SegTree(cost);
        stmin = SegTreePair(depth);
    }

    void add(int v, int x){
        //頂点vの親との辺を+xする
        //頂点vが最初に出てくる場所とその1つ前を考えればよい
        //vに根を渡してはいけない！！
        int idx1 = ind[v].first-1;
        int idx2 = ind[v].second;
        stsum.add(idx1,x);
        stsum.add(idx2,-x);
        cost[idx1] += x;
        cost[idx2] -= x;
    }

    void update(int v, int x){
        //頂点vの親との辺をxにする
        int idx1 = ind[v].first-1;
        int idx2 = ind[v].second;
        cost[idx1] = x;
        cost[idx2] = -x;
        stsum.update(idx1,x);
        stsum.update(idx2,-x);
    }
    int sum(int v){
        //st.show();
        //cout << "!" << ind[v].first << endl;
        int ret = stsum.query(0,ind[v].first);
        return ret;
    }
    int lca(int u,int v){
        pair<int,int> p = stmin.query(ind[u].first, ind[v].first+1);
        return p.second;
    }
    int query(int u,int v){
        int x = lca(u,v);
        int ret = sum(u) + sum(v) - 2*sum(x);
        return ret;
    }


    void show(){
        //オイラーツアーの頂点
        cout << "v :  ";
        for(int i = 0; i < v.size(); i++)cout << v[i] << " ";cout << endl;
        //対応する辺
        cout << "cost:";
        for(int i = 0; i < cost.size(); i++)cout << " " << cost[i];cout << endl;
        //各頂点の最初のインデックス
        for(int i = 0; i < ind.size(); i++)cout << ind[i].first << " " << ind[i].second << endl;
    }
};


signed main(){
    int n;
    cin >> n;
    EulerTourQuery et(n);
    rep(i,n){
        int k;
        cin >> k;
        rep(j,k){
            int c;
            cin >> c;
            et.add_edge(i,c,0);
        }
    }
    et.build(0);
    //et.show();
    int q;
    cin >> q;
    while(q--){
        int ind;
        cin >> ind;
        if(ind){
            int u;
            cin >> u;
            //根からuまでの辺のコストの総和を出力
            cout << et.query(0,u) << endl;
        }else{
            int v,w;
            cin >> v >> w;
            //vとその親の間の辺を+wする
            et.add(v,w);
            //et.show();
        }
    }
}
