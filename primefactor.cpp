
vector<pii> primefactor(int n){
    vector<pii> ret;
    for(int i = 2; i*i <= n; i++)if(n % i == 0){
        int cnt = 0;
        while(n%i == 0)n /= i, cnt++;
        ret.push_back(pii(i,cnt));
    }
    if(n != 1)ret.push_back(pii(n,1));

    return ret;
}

signed main(void) {
    int n;
    cin >> n;
    vector<pii> v = primefactor(n);

}
