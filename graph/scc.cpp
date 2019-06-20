struct SCC{
  int n;
  vector<vector<int> > G,rG,T,C;
  vector<int> vs,used,belong;
  SCC(){}
  SCC(int sz):n(sz),G(sz),rG(sz),used(sz),belong(sz){}
  
  void add_edge(int from,int to){
    G[from].push_back(to);
    rG[to].push_back(from);
  }
  
  void input(int m,int offset=0){
    int a,b;
    for(int i=0;i<m;i++){
      cin>>a>>b;
      add_edge(a+offset,b+offset);
    }
  }
  
  void dfs(int v){
    used[v]=1;
    for(int i=0;i<(int)G[v].size();i++){
      if(!used[G[v][i]]) dfs(G[v][i]);
    }
    vs.push_back(v);
  }
  
  void rdfs(int v,int k){
    used[v]=1;
    belong[v]=k;
    C[k].push_back(v);
    for(int i=0;i<(int)rG[v].size();i++){
      if(!used[rG[v][i]]) rdfs(rG[v][i],k);
    }
  }
  
  int build(){
    fill(used.begin(),used.end(),0);
    vs.clear();
    for(int v=0;v<n;v++){
      if(!used[v]) dfs(v);
    }
    fill(used.begin(),used.end(),0);
    int k=0;
    for(int i=vs.size()-1;i>=0;i--){
      if(!used[vs[i]]){
	T.push_back(vector<int>());
	C.push_back(vector<int>());
	rdfs(vs[i],k++);
      }
    }
    for(int i=0;i<n;i++)
      for(int u:G[i])
	if(belong[i]!=belong[u])
	  T[belong[i]].push_back(belong[u]);
    for(int i=0;i<k;i++){
      sort(T[i].begin(),T[i].end());
      T[i].erase(unique(T[i].begin(),T[i].end()),T[i].end());
    }
    return k;
  }
};
 
