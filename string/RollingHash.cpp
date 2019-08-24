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
    /*
    int M = 1e9+7;
    int M2 = 999999937;
    int base2 = 1123;
    int base = 1213;
    string str;
    int n;
    vector<int> pow,sum;
    vector<int> pow2,sum2;

    void build(){
        n = str.size();
        sum = pow = vector<int> (n+1);
        sum2 = pow2 = vector<int> (n+1);
        sum[0] = sum2[0] = 0;
        pow[0] = pow2[0] = 1;
        for(int i = 0; i < n; i++){
            sum[i+1] = (str[i] + sum[i] * base) % M;
            pow[i+1] = pow[i] * base % M;
            sum2[i+1] = (str[i] + sum2[i] * base2) % M2;
            pow2[i+1] = pow2[i] * base2 % M2;
        }
    }
    */


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
    /*
    pii calc(int l, int r){//[l,r)のハッシュ値を計算
        int len = r - l;
        int ret = sum[r] + M;
        ret -= sum[l] * pow[len] % M;
        int ret2 = sum2[r] + M2;
        ret2 -= sum2[l] * pow2[len] % M2;
        return pii(ret % M, ret2 % M2);
    }
    */

};
