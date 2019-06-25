class BIT2D{
private:
    vector<vector<int> > b2;
    int n,m;
public:
    BIT2D(){}
    BIT2D(int h, int w){
        n = h, m = w;
        b2 = vector<vector<int> >(n+1, vector<int>(m+1,0));
    }
    //0-indexedで v[h][w] に +a する
    void add(int h, int w, int a){
        h++,w++;
        for(int i = h; i <= n; i += i&-i){
            for(int j = w; j <= m; j+= j&-j){
                b2[i][j] += a;
            }
        }
    }
    //0-indexedで半開
    int sum(int h, int w){
        int ret = 0;
        for(int i = h; i; i -= i&-i){
            for(int j = w; j; j -= j&-j){
                ret += b2[i][j];
            }
        }
        return ret;
    }
    //左上(x1,y1)右下(x2,y2)（0-indexedで半開）の値を求める
    //sum(0,0,h,w) == sum(h,w)
    int sum(int x1, int y1, int x2, int y2){
        return sum(x2,y2) + sum(x1,y1) - sum(x2,y1) - sum(x1,y2);
    }
    int get(int h, int w){
        return sum(h, w, h+1, w+1);
    }

};


//AOJ 2842
//http://judge.u-aizu.ac.jp/onlinejudge/review.jsp?rid=3687412#1

typedef pair<int,pii> pip;

signed main(void) {
    int h,w,tim,q;
    cin >> h >> w >> tim >> q;
    BIT2D yet(h,w), done(h,w);
    deque<pip> d;
    while(q--){
        int t,c,h1,w1;
        cin >> t >> c >> h1 >> w1;
        h1--,w1--;
        while(d.size() && d[0].first <= t-tim){
            int x = d[0].second.first;
            int y = d[0].second.second;
            yet.add(x,y,-1);
            done.add(x,y,1);
            d.pop_front();
        }
        if(c == 0){
            yet.add(h1,w1,1);
            d.push_back(pip(t,pii(h1,w1)));
        }else if(c == 1){
            if(done.get(h1,w1)){
                done.add(h1,w1,-1);
            }
        }else{
            int h2,w2;
            cin >> h2 >> w2;
            cout << done.sum(h1,w1,h2,w2) << " " << yet.sum(h1,w1,h2,w2) << endl;
        }
    }
}
