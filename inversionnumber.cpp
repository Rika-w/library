
//転倒数をO(NlogN)で求める

class InversionNumber{
private:
    vector<int> a;
    int n;

    int merge(int l, int mid, int r){
        int n1 = mid - l;
        int n2 = r - mid;
        int ret = 0;
        vector<int> left(n1+1), right(n2+1);
        rep(i,n1)left[i] = a[l+i];
        rep(i,n2)right[i] = a[mid+i];
        left[n1] = right[n2] = INF;//long long を使うときは LINF にする!!!!
        int i = 0, j = 0;
        for(int k = l; k < r; k++){
            if(left[i] <= right[j]){
                a[k] = left[i];
                i++;
            }else{
                a[k] = right[j];
                j++;
                ret += n1-i;
            }
        }
        return ret;
    }

    int mergesort(int l, int r){//[l,r)
        if(l + 1 < r){
            int mid = (l + r)/2;
            int v1 = mergesort(l, mid);
            int v2 = mergesort(mid, r);
            int v3 = merge(l, mid, r);
            return v1 + v2 + v3;
        }
        return 0;
    }

public:
    InversionNumber(){}
    InversionNumber(vector<int> &in){
        a = in;
        n = in.size();
    }
    int calc(){//転倒数を求める
        return mergesort(0,n);
    }

};
