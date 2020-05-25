#include<iostream>
#include<vector>
#include<cmath>
using namespace std;
#define int long long


//1点更新区間取得クエリ
//Range Minimum query
//Range Maximum query
//Range Sum Query
class SqrtDecompositionGetSegment{
private:
    int n; //元の配列のサイズ
    int sz; //1つのバケットが担当する区間の長さ
    int num; //バケットの個数
    vector<int> v,bucket;
    int init;

    int combine(int a, int b){
        //return min(a,b);
        //return max(a,b);
        return a+b;
    }

    int idx(int i){
        return i/sz;
    }
    void build(){
        sz = sqrt(n);
        num = (n + sz-1)/sz;
        bucket = vector<int>(num,init);
        //bucketの更新
        for(int i = 0; i < n; i++){
            bucket[idx(i)] = combine(bucket[idx(i)], v[i]);
        }
    }
    void recalc(int id){
        bucket[id] = init;
        for(int i = id*sz; i < min((id+1)*sz,n); i++){
            bucket[id] = combine(bucket[id], v[i]);
        }
    }
public:
    SqrtDecompositionGetSegment(){
    }
    SqrtDecompositionGetSegment(int size, int initial){
        n = size;
        init = initial;
        v = vector<int> (n,init);
        build();
    }
    SqrtDecompositionGetSegment(vector<int> in, int initial){
        n = in.size();
        init = initial;
        v = in;
        build();
    }
    void update(int ind, int x){
        //v[ind]をxに変更する
        v[ind] = x;
        recalc(idx(ind));
    }
    void add(int ind, int x){
        //v[ind]にxを足す
        v[ind] += x;
        recalc(idx(ind));
    }
    int query_min(int l, int r){
        //[l,r)の最小値を求める
        int ret = init;
        int lid = idx(l);
        int rid = idx(r);
        if(lid == rid){
            for(int i = l; i < r; i++){
                ret = min(ret, v[i]);
            }
            return ret;
        }
        for(int i = l; i < (lid+1)*sz; i++){
            ret = min(ret, v[i]);
        }
        for(int i = lid+1; i < rid; i++){
            ret = min(ret, bucket[i]);
        }
        for(int i = rid*sz; i < r; i++){
            ret = min(ret, v[i]);
        }
        return ret;
    }
    int query_sum(int l, int r){
        //[l,r)の総和を求める
        int ret = init;
        int lid = idx(l);
        int rid = idx(r);
        if(lid == rid){
            for(int i = l; i < r; i++){
                ret += v[i];
            }
            return ret;
        }
        for(int i = l; i < (lid+1)*sz; i++){
            ret += v[i];
        }
        for(int i = lid+1; i < rid; i++){
            ret += bucket[i];
        }
        for(int i = rid*sz; i < r; i++){
            ret += v[i];
        }
        return ret;
    }
    void show(){
        cout << endl;
        cout << "n = " << n;
        cout << ", sz = " << sz;
        cout << ", num = " << num;
        cout << endl;
        cout << "v:";
        for(int i = 0; i < n; i++)cout << " " << v[i];cout << endl;
        cout << "bucket:";
        for(int i = 0; i < num; i++)cout << " " << bucket[i];cout << endl;
        cout << endl;
    }
};


//区間更新1点参照
class SqrtDecompositionUpdateSegment{
private:
    int n; //元の配列のサイズ
    int sz; //1つのバケットが担当する区間の長さ
    int num; //バケットの個数
    vector<int> v,bucket;
    vector<bool> change;
    int init;

    int combine(int a, int b){
        //return min(a,b);//min
        //return max(a,b);//max
        return a+b;//sum
        //return b;//update
    }

    int idx(int i){
        return i/sz;
    }
    void build(){
        sz = sqrt(n);
        num = (n + sz-1)/sz;
        bucket = vector<int>(num,init);
        change = vector<bool>(num,0);
    }
    void recalc(int id){
        bucket[id] = init;
        for(int i = id*sz; i < min((id+1)*sz,n); i++){
            bucket[id] = combine(bucket[id], v[i]);
        }
    }
public:
    SqrtDecompositionUpdateSegment(){
    }
    SqrtDecompositionUpdateSegment(int size, int initial){
        n = size;
        init = initial;
        v = vector<int> (n,init);
        build();
    }
    SqrtDecompositionUpdateSegment(vector<int> in, int initial){
        n = in.size();
        init = initial;
        v = in;
        build();
    }
    void update_range(int l, int r, int x){
        //[l,r)にxを適用する
        int lid = idx(l);
        int rid = idx(r);
        //cout << "!" << lid << " " << rid << endl;
        if(lid == rid){
            for(int i = lid*sz; i < min((lid+1)*sz,n); i++){
                if(change[lid])v[i] = combine(v[i], bucket[lid]);
                if(l <= i && i < r)v[i] = combine(v[i], x);
            }
            change[lid] = false;
            bucket[lid] = init;
        }else{
            for(int i = lid*sz; i < (lid+1)*sz; i++){
                if(change[lid])v[i] = combine(v[i], bucket[lid]);
                if(l <= i)v[i] = combine(v[i], x);
            }
            change[lid] = false;
            bucket[lid] = init;
            for(int i = lid+1; i < rid; i++){
                change[i] = true;
                bucket[i] = combine(bucket[i], x);
            }
            for(int i = rid*sz; i < min((rid+1)*sz,n); i++){
                if(change[rid])v[i] = combine(v[i], bucket[rid]);
                if(i < r)v[i] = combine(v[i], x);
            }
            if(rid < num){
                change[rid] = false;
                bucket[rid] = init;
            }
        }
    }
    /*
    void add(int ind, int x){
        //v[ind]にxを足す
        v[ind] += x;
        recalc(idx(ind));
    }
    int query_min(int l, int r){
        //[l,r)の最小値を求める
        int ret = init;
        int lid = idx(l);
        int rid = idx(r);
        if(lid == rid){
            for(int i = l; i < r; i++){
                ret = min(ret, v[i]);
            }
            return ret;
        }
        for(int i = l; i < (lid+1)*sz; i++){
            ret = min(ret, v[i]);
        }
        for(int i = lid+1; i < rid; i++){
            ret = min(ret, bucket[i]);
        }
        for(int i = rid*sz; i < r; i++){
            ret = min(ret, v[i]);
        }
        return ret;
    }*/
    int query_get(int ind){
        //v[ind]を求める
        int id = idx(ind);
        if(change[id]){
            return combine(v[ind], bucket[id]);
        }
        return v[ind];
    }
    void show(){
        cout << endl;
        cout << "n = " << n;
        cout << ", sz = " << sz;
        cout << ", num = " << num;
        cout << endl;
        cout << "v:";
        for(int i = 0; i < n; i++)cout << " " << v[i];cout << endl;
        cout << "bucket:";
        for(int i = 0; i < num; i++)cout << " " << bucket[i];cout << endl;
        cout << "change:";
        for(int i = 0; i < num; i++)cout << " " << change[i];cout << endl;
        cout << endl;
    }
};


//http://judge.u-aizu.ac.jp/onlinejudge/review.jsp?rid=4398822#1
//Range Minimum Query
void dsl2a(){
    int n,q;
    cin >> n >> q;
    long init = (1LL<<31)-1;
    vector<int> in(n,init);
    SqrtDecompositionGetSegment sd(in,init);
    while(q--){
        int com,x,y;
        cin >> com >> x >> y;
        if(com == 0){//a_xをyに変更する
            sd.update(x,y);
        }else{//a_x ~ a_yの最小値を出力する
            //sd.show();
            cout << sd.query_min(x,y+1) << endl;
        }
    }
}
//http://judge.u-aizu.ac.jp/onlinejudge/review.jsp?rid=4398962#1
//Range Sum Query
void dsl2b(){
    int n,q;
    cin >> n >> q;
    long init = 0;
    vector<int> in(n,init);
    SqrtDecompositionGetSegment sd(in,init);
    while(q--){
        int com,x,y;
        cin >> com >> x >> y;
        if(com == 0){//a_xにyを加える
            x--;
            sd.add(x,y);
        }else{//a_x ~ a_yの総和を出力する
            //sd.show();
            x--,y--;
            cout << sd.query_sum(x,y+1) << endl;
        }
    }
}
//Range Update Query
//http://judge.u-aizu.ac.jp/onlinejudge/review.jsp?rid=4400323#1
void dsl2d(){
    int n,q;
    cin >> n >> q;
    long init = (1LL<<31)-1;
    vector<int> in(n,init);
    SqrtDecompositionUpdateSegment sd(in,init);
    while(q--){
        int com;
        cin >> com;
        if(com == 0){//a_s ~ a_tをxに変更する
            int s,t,x;
            cin >> s >> t >> x;
            sd.update_range(s,t+1,x);
            //sd.show();
        }else{//a_iの値を出力する
            //sd.show();
            int i;
            cin >> i;
            cout << sd.query_get(i) << endl;
        }
    }
}
//Range Add Query
//http://judge.u-aizu.ac.jp/onlinejudge/review.jsp?rid=4401022#1
void dsl2e(){
    int n,q;
    cin >> n >> q;
    long init = 0;
    vector<int> in(n,init);
    SqrtDecompositionUpdateSegment sd(in,init);
    while(q--){
        int com;
        cin >> com;
        if(com == 0){//a_s ~ a_tにxを足す
            int s,t,x;
            cin >> s >> t >> x;
            s--,t--;
            sd.update_range(s,t+1,x);
            //sd.show();
        }else{//a_iの値を出力する
            //sd.show();
            int i;
            cin >> i;
            i--;
            cout << sd.query_get(i) << endl;
        }
    }
}

signed main(){
    dsl2e();
}
