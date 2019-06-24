class SegTree{

private:

    int n;
    int init = 0; //初期化の値（単位元）
    int combine(int a, int b){
        return max(a,b);
    }

public:
    vector<int> seg;

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
    int get(int x){
        return seg[n-1+x];
    }
};


class SegTree2D{
    vector<SegTree> vseg;
    int n;
    int init = 0;//初期化の値（単位元） SegTreeのinitと一致させる！！！
    int combine(int a,int b){//SegTreeのcombineと一致させる！！！
        return max(a+b);
    }

    SegTree2D (){}

    SegTree2D(int h, int w){
        n = 1;
        while(n < h) n <<= 1;
        vseg = vector<SegTree>(2*n,SegTree(w));
    }

    SegTree2D(const vector<vector<int> > &in){
        n = 1;
        while(n < in.size()) n <<= 1;
        vseg = vector<SegTree>(2*n,SegTree(in[0].size()));
        for(int i = n-1+in.size()-1; i >= 0; i--){
            if(i-(n-1) < 0){
                for(int j = 0; j < vseg[i].seg.size()){
                    vseg[i].seg[j] = combine(vseg[i*2+1].seg[j], vseg[i*2+2].seg[j]);
                }
            }else{
                vseg[i] = SegTree(in[i-(n-1)]);
            }
        }
    }

    //val[x][y]の値をaにする
    void update(int x, int y, int a){
        x += n-1;
        vseg[x].update(y,a);
        while(x > 0){
            x = (x-1)/2;
            vseg[x].update(y,a);
        }
    }
    //右上(x1,y1)左下(x2,y2)（半開区間）の値を求める
    int query(int x1, int y1, int x2, int y2, int k = 0, int l = 0, int r = -1){
        if(r == -1) r = n;
        if(r <= x1 || x2 <= l) return init;
        if(x1 <= l && r <= x2) return vseg[k].query(y1,y2);
        else return combine(query(x1,y1,x2,y2,k*2+1,l,(l+r)/2),query(x1,y1,x2,y2,k*2+2,(l+r)/2),r);
    }
    int get(int x, int y){
        return vseg[n-1+x].get(y);
    }
};
