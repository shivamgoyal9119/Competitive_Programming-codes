#include<iostream>
using namespace std;

class SGTree{
    vector<int> seg, lazy;
    public:
    SGTree(int n){
        seg.resize(4*n);
        lazy.resize(4*n, 0);
    }

    void build(int ind, int low, int high, int arr[]){
        if(low == high){
            seg[ind] = arr[low];
            return;
        }

        int mid = (low + high) >> 1;
        build((2*ind)+1, low, mid, arr);
        build((2*ind)+2, mid+1, high, arr);

        seg[ind] = seg[(2*ind)+1] + seg[(2*ind)+2];
    }

    void update(int ind, int low, int high, int l, int r, int val){
        // update the previous remaining updates
        // and propogate downwards

        if(lazy[ind] != 0){
            seg[ind] += (high - low + 1) * lazy[ind];
            // propogate the lazy update downwards
            // for the remaining nodes to get updated
            if(low != high){
                lazy[(2*ind)+1] += lazy[ind];
                lazy[(2*ind)+2] += lazy[ind];
            }

            lazy[ind] = 0;
        }

        // no overlap   
        // we don't do anything and return 
        // low high l r or l r low high
        if(high < l || r < low){
            return;
        }

        // complete overlap
        // l low high r
        if(low >= l && r >= high){
            seg[ind] += (high - low + 1) * val;
            if(low != high){
                lazy[(2*ind)+1] += val;
                lazy[(2*ind)+2] += val;
            }
            return;
        }

        // last case has to be partial overlap 
        int mid = (low + high) >> 1;
        update((2*ind)+1, low, mid, l, r, val);
        update((2*ind)+2, mid+1, high, l, r, val);

        seg[ind] = seg[(2*ind)+1] + seg[(2*ind)+2];
    } 

    int query(int ind, int low, int high, int l, int r){
        // update if any updates are remaining
        // as the node will stay fresh and updated
        if(lazy[ind] != 0){
            seg[ind] += (high - low + 1) * lazy[ind];

            if(low != high){
                lazy[(2*ind)+1] += lazy[ind];
                lazy[(2*ind)+2] += lazy[ind];
            }

            lazy[ind] = 0;
        }

        // no overlap return 0;
        if(low > r || high < l) return 0;

        // complete overlap
        if(low >= l && high <= r) return seg[ind];

        // partial overlap
        int mid = (low + high) >> 1;
        int left = query((2*ind)+1, low, mid, l, r);
        int right = query((2*ind)+2, mid+1, high, l, r);

        return left + right;
    }
};

int main(){

    // Segment Tree (Lazy Propogation)

    int n;
    cin>>n;

    int arr[n];
    for(int i = 0; i<n; i++) cin>>arr[i];

    SGTree seg(n);
    seg.build(0, 0, n-1, arr);

    int q;
    cin>>q;
    while(q--){
        int type;
        cin>>type;

        if(type == 1){
            int l, r;
            cin>>l>>r;
            cout<<seg.query(0, 0, n-1, l, r)<<endl;
        }else{
            int l, r, val;
            cin>>l>>r>>val;
            seg.update(0, 0, n-1, l, r, val);
        }
    }


    return 0;
}
