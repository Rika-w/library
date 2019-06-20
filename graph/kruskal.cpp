//O(ElogV)
#include <algorithm>


class UnionFind{

private:
    vector<int> rank,p;

    void makeSet(int x){
      p[x] = x;
      rank[x] = 0;
    }

  public:
      UnionFind(){};
      UnionFind(int size){
        rank.resize(size,0);
        p.resize(size,0);
        for(int i = 0; i < size; i++){
          makeSet(i);
        }
      }

    bool same(int x, int y){
      return  find(x) == find(y);
    }

    void unite(int x, int y){
      link(find(x), find(y));
    }

    int find(int x){
      if(x != p[x]) p[x] = find(p[x]);
      return p[x];
    }

private:
    void link(int x, int y){
      if(rank[x] > rank[y]){
        p[y] = x;
      }else{
        p[x] = y;
        if(rank[x] == rank[y]) rank[y]++;
      }
    }

};



//ここから

struct edge{
    int from, to, cost;

    bool operator<(const edge& e) const {
        return cost < e.cost;
    }

};

int kruskal(vector<edge> es, int v){

    sort(es.begin(), es.end());

     UnionFind uf(v);

     int ret = 0;

     for(int i = 0 ; i < es.size() ; i++){

         edge e = es[i];

         if(!uf.same(e.from, e.to)){
             uf.unite(e.from, e.to);
             ret += e.cost;
         }

     }

     return ret;

}

/*
使い方
kruskal(g,v); で辺集合g、頂点数vのグラフの最小全域木の重みを求める

*/

/*
2018/5/14
http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_2_A&lang=jp
*/

int main(void) {
    int i,j;
    int n;
    int v,e;
    cin >> v >> e;

    vector<edge> g;

    rep(i,e){
        edge t;
        cin >> t.from >> t.to >> t.cost;
        g.push_back(t);
    }

    cout << kruskal(g,v) << endl;

}
