class RollingHash{
private:
    int M = 1e9+7;
    int base = 1213;
    string str;
    int n;
    vector<int> pow,sum;

    void build(){
        n = str.size();
        sum = pow = vector<int> (n+1);
        sum[0] = 0;
        pow[0] = 1;
        for(int i = 0; i < n; i++){
            sum[i+1] = (str[i] + sum[i] * base) % M;
            pow[i+1] = pow[i] * base % M;
        }
    }


public:
    RollingHash(){}
    RollingHash(string in){
        str = in;
        build();
    }
    RollingHash(string in, int p, int mod){
        M = mod;
        base = p;
        str = in;
        build();
    }

    int calc(int l, int r){//[l,r)のハッシュ値を計算
        int len = r - l;
        int ret = sum[r] + M;
        ret -= sum[l] * pow[len] % M;
        return ret % M;
    }

};
