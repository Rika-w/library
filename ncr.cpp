//abc034C

#include<iostream>
#include<cstdio>
using namespace std;
#define rep(i,n) for(i=0;i<n;i++)
#define MOD 1000000007LL
/*
long long factorical(int n)
{
  long long ans=1,i;
  for(i=n;i>1;i--)
    ans=(ans*i)%MOD;
  return ans;
}

long long beki(long long a,int n)
{
  long long s=1LL;
  while(n){
    if(n%2)s=(s*a)%MOD;
    a=(a*a)%MOD;
    n/=2;
  }
  return s;
}

long long ncr(int n,int r)
{
  long long a=factorical(n);
  long long b=(factorical(r)*factorical(n-r))%MOD;
  return (a*beki(b,MOD-2))%MOD;
}
*/


int ncr[1005][1005];

void calc(){
  rep(i,1005){
    ncr[i][0] = 1;
    ncr[i][i] = 1;
  }
  loop(i,1,1005)loop(j,1,i){
    ncr[i][j] = ncr[i-1][j-1] + ncr[i-1][j];
  }
}


int main()
{
  int h,w;
  cin>>w>>h;
  h--;
  w--;
  cout<<ncr(h+w,h)<<endl;
}

