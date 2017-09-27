
#define MAX_N 100000

int parent[MAX_N];
int ran[MAX_N];

void init(int n)
{
  int i;
  rep(i,n){
    parent[i]=i;
    ran[i]=0;
  }
}

int find(int x)
{
  if(parent[x]==x)
    return x;
  else
    return parent[x]=find(parent[x]);
}

void unite(int x,int y)
{
  x=find(x);
  y=find(y);
  if(x==y)return;

  if(ran[x]<ran[y])
    parent[x]=y;
  else{
    parent[y]=x;
    if(ran[x]==ran[y])ran[x]++;
  }
}
