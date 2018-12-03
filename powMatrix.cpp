//AOJ1327
typedef vector<vi> vvi;

void printMatrix(vvi a){
    rep(i,a.size()){
        rep(j,a[0].size())cout << a[i][j] << " " ;
        cout << endl;
    }
}

vvi product(vvi a, vvi b, int mod){//ret = a * b % mod
    vvi ret(a.size(), vi(b[0].size(),0));
    rep(i,a.size())rep(j,b[0].size()){
        rep(k,a[0].size()) (ret[i][j] += a[i][k]*b[k][j]) %= mod;
    }
    return ret;
}


vvi powMatrix(vvi a, int t, int mod){// A^t % mod
    int n = a.size();

    vvi ret(n, vi(n,0));
    rep(i,n)ret[i][i] = 1; // 単位行列

    while(t > 0){ //繰り返し自乗法
        if(t&1) ret = product(ret, a, mod);
        a = product(a,a, mod);
        t = t >> 1;
    }
    return ret;
}


int main(void) {
    int i,j;
    int n,m,a,b,c,t;

    while(cin >> n >> m >> a >> b >> c >> t, n){
        vvi s(n,vi(1));
        rep(i,n) cin >> s[i][0];

        vvi A(n, vi(n,0));
        rep(i,n)rep(j,n){
            if(i == j+1) A[i][j] = a;
            if(i == j) A[i][j] = b;
            if(i+1 == j) A[i][j] = c;
        }
        //printMatrix(A);
        A = powMatrix(A,t,m);
        vvi ans = product(A, s, m);

        rep(i,n){
            cout << ans[i][0];
            if(i<n-1)cout << " " ;
            else cout << endl;
        }

    }
}
