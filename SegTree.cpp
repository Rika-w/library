
//0-indexed
class SegTree{

private:

    int n;
    vector<int> seg;
    int init = 0; //初期化の値（単位元）
    int combine(int a, int b){
        return max(a,b);
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
};

/*

 モノイドを変更する場合は
 - 単位元　init　
 - 評価関数　combine
 を変更すること！！

SegTree a(n); でn要素のセグ木を宣言
SegTree a(v); で配列vを初期化したセグ木を宣言

a.update(k,x); で配列のk番目(0-indexed)にxを代入+更新
a.query(a,b); で [a,b) の区間を調べる

*/

//https://beta.atcoder.jp/contests/abc095/submissions/2978868


/*

pair型の RMQ
firstに要素、secondにindexが入っている。
https://code-festival-2018-final-open.contest.atcoder.jp/submissions/3630832
*/
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




 class LazySegmentTree{
 private:
     int n;
     vector<long long> node, lazy;
     long long node_init = 0; // sum, max, update
     //long long node_init = LINF; // min
     //long long lazy_init = 0; // default
     long long lazy_init = LINF; // min, update (存在しない値)

     long long lazy_update(long long a,long long b){
         //return a+b; // sum query
         //return max(a,b); // max query
         //return min(a,b); // min query
         return b; // update query
     }

     long long node_update(long long a, long long b, int l, int r){ // lazy を node に反映
         //return a + b; // min query
         //return b; // update query
         return b * (r-l); // sum query
     }

     long long combine(long long a,long long b){
         return a+b; // sum query
         //return max(a,b); // max query
         //return min(a,b); // min query
     }

 public:
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
         if(r < 0)r = n;
         eval(k,l,r);
         if(b <= l || r <= a)return;
         if(a <= l && r <= b){
             lazy[k] = x;
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




signed main(void) {
    int i,j;
    int n, c;
    cin >> n >> c;
    vector<pii> x(n),y(n);
    rep(i,n){
        int t,v;
        cin >> t >> v;
        x[i] = pii(t,v);
        y[i] = pii(c-t,v);
    }
    sort(all(x));
    sort(all(y));
    rep(i,n-1){
        x[i+1].second += x[i].second;
        y[i+1].second += y[i].second;
    }
    vi a(n),aa(n),b(n),bb(n);
    rep(i,n){
        a[i] = x[i].second - x[i].first;
        aa[i] = x[i].second - 2*x[i].first;
        b[i] = y[i].second - y[i].first;
        bb[i] =  y[i].second - 2*y[i].first;
    }

    SegTree a1(a),a2(aa),b1(b),b2(bb);

    int ans = 0;
    rep(i,n+1){
        ans = max(ans, a1.query(0,i) + b2.query(0,n-i));
        ans = max(ans, a2.query(0,i) + b1.query(0,n-i));
    }
    cout << ans << endl;
}
