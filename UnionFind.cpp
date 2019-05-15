#include<iostream>
#include<vector>

using namespace std;

const int error = 1e9;

class UnionFind{

private:
    vector<int> data;

  public:
      UnionFind(){};
      UnionFind(int size){
          data = vector<int>(size, -1);
      }

    bool same(int x, int y){
        return find(x) == find(y);
    }

    bool unite(int x, int y){
        if(same(x,y)) return(false);
        x = find(x);
        y = find(y);
        if(data[x] > data[y]) swap(x, y);
        data[x] += data[y];
        data[y] = x;
        return(true);
    }

    int find(int x){
        if(data[x] < 0) return(x);
        return(data[x] = find(data[x]));
    }

    int size(int x){
        return(-data[find(x)]);
    }

};


/*
UnionFind　使い方

UnionFind uf = UnionFind(n); で n 要素のUF木を宣言
uf.unite(a,b); で x_a と x_b を繋ぐ（繋いであったらfalseが返る）
uf.find(x); で x の親の添え字を返す
uf.same(a,b); で a と b の親が等しいかを返す
uf.size(x); で x の連結成分の大きさを返す
*/


class WeightedUnionFind{

private:
    vector<int> rank,p,d;

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
        return find(x) == find(y);
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
};

/*
WeightedUnionFind　使い方

WeightedUnionFind wuf = WeightedUnionFind(n); で n 要素の重み付きUF木を宣言
wuf.relate(x,y,z); で a_y が a_x より z 大きいという関係を構築
wuf.find(x); で x の親の添え字を返す
wuf.same(x,y); で x と y の親が等しいかを返す
wuf.diff(x,y); a_x と a_y の差 (a_y - a_x) を返す (未定義の場合は error を返す)

*/


//Quick Find Weighted
//https://topcoder.g.hatena.ne.jp/iwiwi/20131226/1388062106
//O(NlogN)
//https://yukicoder.me/problems/no/416など

class QuickFind{

private:
    vector<int> i2g;          // i2g[i] := アイテム i の所属するグループの番号
    vector<vector<int> > g2i;  // g2i[g] := グループ g に所属するアイテムたち

public:
    QuickFind(){};
    QuickFind(int size){
        i2g.resize(size);
        g2i.resize(size);
        for (int i = 0; i < size; i++) {
        // 最初はアイテム i はグループ i に所属
            i2g[i] = i;
            g2i[i].assign(1, i);
        }
    }

    // アイテム ia の所属するグループとアイテム ib の所属するグループを 1 つにする
    void merge(int ia, int ib) {
        if(same(ia,ib))return;
        // ia の所属するグループが ib の所属するグループより小さくならないようにする
        if (g2i[i2g[ia]].size() < g2i[i2g[ib]].size()) {
            swap(ia, ib);
        }
        int ga = i2g[ia], gb = i2g[ib];
        // グループ gb に所属する全てのアイテムをグループ ga に移す
        for (int i = 0; i < g2i[gb].size(); i++) i2g[g2i[gb][i]] = ga;
        g2i[ga].insert(g2i[ga].end(), g2i[gb].begin(), g2i[gb].end());
        g2i[gb].clear();
    }

    // アイテム id と同じグループに所属しているアイテムを取得
    vector<int> get_group(int id){
        vector<int> ret;
        id = i2g[id];
        for(int i = 0; i < g2i[id].size(); i++)ret.push_back(g2i[id][i]);
        return ret;
    }

    // アイテム ia とアイテム ib は同じグループに所属しているか？
    bool same(int ia, int ib) {
        return i2g[ia] == i2g[ib];
    }
};


/*
QuickFind　使い方

QuickFind qf = QuickFind(n); で n 要素のUF木を宣言
qf.merge(a,b); で a の所属するグループと b の所属するグループを 1 つにする
qf.same(a,b); で a と b は同じグループに所属しているか？を返す
qf.get_group(x); で x と同じグループに所属しているものを返す
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
