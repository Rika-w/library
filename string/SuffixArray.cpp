
class SuffixArray{
private:

    class SegTree{
    private:
        int n;
        vector<int> seg;
        int init = INF; //初期化の値（単位元）
        int combine(int a, int b){
            return min(a,b);
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

    string s;
    int n,k;
    vi rank,tmp,sa,lcp;
    SegTree st;
    /*
    bool compare(int i, int j){
        if(rank[i] != rank[j])return rank[i] < rank[j];
        int ri = i + k <= n ? rank[i+k] : -1;
        int rj = j + k <= n ? rank[j+k] : -1;
        return ri < rj;
    }
    */
    void bulid(){ // O(N log^2 N)
        rank = tmp = sa = lcp = vi(n+1, 0);
        for(int i = 0; i <= n; i++){
            sa[i] = i;
            rank[i] = i < n ? s[i] : -1;
        }
        auto compare = [&](int i, int j) {
            if(rank[i] != rank[j])return rank[i] < rank[j];
            int ri = i + k <= n ? rank[i+k] : -1;
            int rj = j + k <= n ? rank[j+k] : -1;
            return ri < rj;
        };
        for(k = 1; k <= n; k *= 2){
            sort(all(sa), compare);
            tmp[sa[0]] = 0;
            for(int i = 1; i <= n; i++){
                tmp[sa[i]] = tmp[sa[i-1]] + (compare(sa[i-1],sa[i]) ? 1 : 0);
            }
            for(int i = 0; i <= n; i++)rank[i] = tmp[i];
        }

        rank = vi(n+1, 0);
        for(int i = 0; i <= n; i++)rank[sa[i]] = i;
        int h = 0;
        lcp[0] = 0;
        for(int i = 0; i < n; i++){
            int j = sa[rank[i]-1];

            if(h > 0)h--;
            for(; j+h < n && i+h < n; h++){
                if(s[j+h] != s[i+h])break;
            }
            lcp[rank[i]-1] = h;
        }
        st = SegTree(lcp);
    }

public:
    SuffixArray(){}
    SuffixArray(string in){
        s = in;
        n = s.size();
        bulid();
    }
    bool contain(string t){ // O(|t| log |s|)
        int a = 0, b = n;
        int m = t.size();
        while(b - a > 1){
            int c = (a + b)/2;
            if(s.compare(sa[c], m, t) < 0) a = c;
            else b = c;
        }
        return s.compare(sa[b], m, t) == 0;
    }

    int get_lcp(int i,int j){
        if(rank[i] > rank[j])swap(i,j);
        return st.query(rank[i],rank[j]);
    }
};
