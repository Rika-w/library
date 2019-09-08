#include<iostream>
#include<vector>
#include<set>
using namespace std;
#define rep(i,n) for(int i = 0; i < (n); i++)

class SuperSet{
private:

    class BIT{
    private://[1,n]
        vector<int> bit;
        int n;
    public:
        BIT(){}
        BIT(int size){
            n = size;
            bit = vector<int>(n+1,0);
        }
        int sum(int i){//[0,i)のsum（内部実装は[1,i]）
            int s = 0;
            while(i > 0){
                s += bit[i];
                i -= i & -i;
            }
            return s;
        }
        void add(int i, int x){
            while(i <= n){
                bit[i] += x;
                i += i & -i;
            }
        }
        void show(){
            cout << "bit:";
            for(int i = 1; i <= n; i++){
                cout << " " << bit[i];
            }
            cout << endl;
        }
    };

    int n;
    BIT bit;
    set<int> st;

public:
    SuperSet(){}
    SuperSet(int size){
        n = size;
        bit = BIT(n);
    }
    void add(int x){//[0,n)
        st.insert(x);
        bit.add(x,1);
    }
    bool erase(int ind){//[0,st.size())
        if(ind > bit.sum(n))return false;
        int l = 0, r = n+1;
        while(r - l > 1){
            int mid = (l + r)/2;
            if(ind >= bit.sum(mid))l = mid;
            else r = mid;
        }
        bit.add(l,-1);
        st.erase(l);
        return true;
    }
    int size(){
        return st.size();
    }
    void show(){
        for(auto x: st){
            cout << " " << x;
        }
        cout << endl;
    }

    /*
    [1,N]の値を管理するset
    add(x)はsetにxを追加する
    erase(x)はsetに入っている値の小さい方からx番目を削除する(xは1以上要素数以下)
    */
    
};

int main(){
    int n = 5;
    SuperSet st(n);
    st.add(1);
    st.add(2);
    st.add(3);
    st.add(4);
    st.add(5);
    st.show();
    st.erase(1);
    st.show();
    st.erase(3);
    st.show();
}
