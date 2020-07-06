#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
//有向グラフのサイクルを1つ見つけてくる
class FindCycle{
private:
	int n;
	vector<vector<int> > g;
	vector<int> v,ans;
	vector<bool> used, end;
	void dfs(int now, int par){
		v.push_back(now);
		if(used[now] == true){
			if(end[now] == false){//サイクル検出完了
				ans.push_back(v.back());
				for(int i = v.size()-2; i >= 0; i--){
					ans.push_back(v[i]);
					if(v[i] == v.back())break;
				}
			}
			return;
		}else{
			used[now] = true;
			for(auto x: g[now])if(x != par){
				dfs(x,now);
				if(ans.size())return;
			}
		}
		v.pop_back();
		end[now] = true;
	}
public:
	FindCycle(int sz){
		n = sz;
		g.resize(n);
	}
	void add_edge(int a, int b){
		g[a].push_back(b);
	}
	vector<int> calc(){
		v.resize(0);
		used = end = vector<bool>(n,false);
		ans.resize(0);
		for(int i = 0; i < n; i++)if(!used[i]){
			dfs(i,-1);
			if(ans.size())break;
		}
		reverse(ans.begin(),ans.end());
		return ans;
	}
};

//http://judge.u-aizu.ac.jp/onlinejudge/review.jsp?rid=4647542#1
#include<set>
void AOJ2891(){
	int n;
	cin >> n;
	FindCycle f(n);
	for(int i = 0; i < n; i++){
		int a,b;
		cin >> a >> b;
		a--,b--;
		f.add_edge(a,b);
		f.add_edge(b,a);
	}
	vector<int> v = f.calc();
	set<int> st;
	for(auto x:v)st.insert(x);
	int q;
	cin >> q;
	while(q--){
		int a,b;
		cin >> a >> b;
		a--,b--;
		if(st.count(a) && st.count(b)){
			cout << 2 << endl;
		}else{
			cout << 1 << endl;
		}
	}
}
int main(){
	AOJ2891();
}
