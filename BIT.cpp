//ant book P161
//O(logN)

//1-indexedであることに注意
class BIT{
private:
    //[1,n]
    vector<int> bit,
    int n;

public:
    BIT(){}
    BIT(int size){
        n = size;
        bit = vector<int>(n+1);
    }
    //0からiまでの総和
    int sum(int i){
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
        for(int i = 1; i <= n; i++){
            cout << " " << bit[i];
        }
        cout << endl;
    }
}
