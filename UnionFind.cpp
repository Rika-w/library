#include<iostream>
#include<vector>

using namespace std;

const int error = 1e9;

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


class WeightedUnionFind{

private:
    vector<int> rank,p,d;

  public:
      WeightedUnionFind(){};
      WeightedUnionFind(int size){
        rank.resize(size,0);
        p.resize(size,0);
        d.resize(size,0);
        for(int i = 0; i < size; i++){
          p[i] = i;
        }
      }

    bool same(int x, int y){
      return  find(x) == find(y);
    }

    void relate(int x, int y, int z){
      int px = find(x);
      int py = find(y);
      link(px, py, d[y] + z - d[x]);
      find(x);
      find(y);
    }

    int find(int x){
      if(x != p[x]){
        int par = find(p[x]);
        d[x] += d[p[x]];
        p[x] = par;
      }
      return p[x];
    }

    int diff(int x, int y){
      find(x);
      find(y);
      if(same(x,y)){
        return d[x] - d[y];
      }else{
        return error;
      }
    }
private:
    void link(int x, int y, int z){
      if(rank[x] > rank[y]){
        p[y] = x;
        d[y] = -z;
      }else{
        p[x] = y;
        d[x] = z;
        if(rank[x] == rank[y]) rank[y]++;
      }
    }

};


/*
使い方

UnionFind:

UnionFind uf = UnionFind(n); で n 要素のUF木を宣言
uf.unite(a,b); で x_a と x_b を繋ぐ
uf.find(x); で x の親の添え字を返す
uf.same(a,b); で a と b の親が等しいかを返す

WeightedUnionFind:

WeightedUnionFind wuf = WeightedUnionFind(n); で n 要素の重み付きUF木を宣言
wuf.relate(x,y,z); で a_y が a_x より z 大きいという関係を構築
wuf.find(x); で x の親の添え字を返す
wuf.same(x,y); で x と y の親が等しいかを返す
wuf.diff(x,y); a_x と a_y の差 (a_y - a_x) を返す (未定義の場合は error を返す)

*/



/*
2018/4/23
http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_1_A
*/
int main(){

    int n, a, b, q;
    int t;


    cin >> n >> q;
    UnionFind uf = UnionFind(n);

    for(int i = 0; i < q; i++){
      cin >> t >> a >> b;
      if(t == 0){
        uf.unite(a,b);
      }else{
        if(uf.same(a,b))cout << 1 << endl;
        else cout << 0 << endl;
      }
    }
    return 0;
}

/*
2018/4/23
http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_1_B
*/
/*
int main(){

    int n, q;

    cin >> n >> q;
    WeightedUnionFind wuf = WeightedUnionFind(n);

    for(int i = 0; i < q; i++){
      int t, x, y, z;
      cin >> t;
      if(t == 0){
        cin >> x >> y >> z;
        wuf.relate(x, y, z);
      }else{
        cin >> x >> y;
        int ans = wuf.diff(x, y);
        if(ans == error)
          cout << "?" << endl;
        else
          cout << ans << endl;
      }
    }
    return 0;
}
*/
