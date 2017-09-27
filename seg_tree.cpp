//1-indexed

int n;//range
int s[4*100005];//n=1e5
int t;

int hyoka(int a,int b){//min
  if(a<b)return a;
  else return b;
}

//初期化
//INFの値に注意する

void sset(int n,vi d){
  int i;
  for(t=1;t<n;t*=2);
  for(i=0;i<n;i++)s[t+i]=d[i];
  for(;i<t;i++)s[t+i]=INF;
  for(i=t-1;i;i--)s[i]=hyoka(s[i*2],s[i*2+1]);
}

//update
//i番目の数値をnに変更
void sud(int i,int n){
  for(s[i+=t]=n;i/=2;)
    s[i]=hyoka(s[i*2],s[i*2+1]);
}

//クエリ処理
//[a,b)区間だとsout(a,b,1,0,t);
int sout(int a,int b,int i,int l,int r){
  if(r<=a || b<=l)return INF;
  if(a<=l && r<=b)return s[i];
  return hyoka(sout(a,b,i*2,l,(l+r)/2),sout(a,b,i*2+1,(l+r)/2,r));
}
