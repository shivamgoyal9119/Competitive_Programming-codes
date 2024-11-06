#include<iostream>
using namespace std;

void get_update_f_v(vector<int> &f_v, int idx, int val, int n){
    if(idx >= n) return;
    f_v[idx] += val;
    idx = idx + (idx & (-idx));
    get_update_f_v(f_v, idx, val, n);
}

int get_sum(vector<int> &f_v, int idx){
    if(idx <= 0) return 0;
    int ans = f_v[idx];
    idx = idx - (idx & (-idx));
    ans += get_sum(f_v, idx);
    return ans;
}

int main(){

    // Fenwick Tree (Binary Indexed Tree)

    int n;
    cin>>n;
    vector<int> v(n), f_v(n+1, 0);
    for(int i = 0; i<n; i++) cin>>v[i];

    for(int i = 0; i<n; i++)
        get_update_f_v(f_v, i+1, v[i], n+1); // Pre-Processing has time complexity O(n*log2(n))
    

    int val = get_sum(f_v, n), val2 = get_sum(f_v, 2);
    cout<<val-val2<<endl;


    


    return 0;
}