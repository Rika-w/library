//aoj2300

int main(void) {
  int i,j,k;
  int n,m;
  cin>>n>>m;
  vector<double> l(n),a(n),b(n);
  rep(i,n)cin>>l[i]>>a[i]>>b[i];
  double ans=0;
  rep(i,1<<n){
    vi t;
    rep(j,n)if(i&(1<<j))t.push_back(j);
    double tmp=0;
    if(t.size()!=m)continue;
    rep(j,t.size())loop(k,j+1,t.size()){
      tmp+=(l[t[j]]-l[t[k]])*(l[t[j]]-l[t[k]]);
      tmp+=(a[t[j]]-a[t[k]])*(a[t[j]]-a[t[k]]);
      tmp+=(b[t[j]]-b[t[k]])*(b[t[j]]-b[t[k]]);
    }
    ans=max(ans,tmp);
  }
  cout<<shosu(10)<<ans<<endl;
}
