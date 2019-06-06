vector<pair<int,int> > get_segment(const vector<int> &v, int t){
    int n = v.size();
    deque<int> a,b;
    if(v[0] == t)a.push_back(0);
    rep(i,n-1)if(v[i] != t && v[i+1] == t)a.push_back(i+1);
    if(v.back() == t)b.push_front(n);
    rep(i,n-1)if(v[n-i-1] != t && v[n-i-2] == t)b.push_front(n-i-1);
    vector<pair<int,int> > ret;
    //rep(i,a.size())cout << " " << a[i];cout << endl;
    //rep(i,b.size())cout << " " << b[i];cout << endl;
    rep(i,a.size())ret.push_back(pii(a[i],b[i]));
    return ret;
}
