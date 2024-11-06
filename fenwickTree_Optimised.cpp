#include<iostream>
using namespace std;

int main(){

    // Fenwick Tree Pre-processing In O(N)
    // Using Prefix_Sum For Getting Optimised Pre-Processing

    int n, p_sum = 0;
    cin>>n;

    vector<int> v(n), prefix_v(n+1, 0), f_array(n+1, 0);
    for(int i = 0; i<n; i++) cin>>v[i];
    for(int i = 0; i<n; i++)
        prefix_v[i+1] = p_sum += v[i];
    
    for(int i = 1; i<n+1; i++){ // Pre-Processing
        int i_ = i - (i&(-i));
        f_array[i] = prefix_v[i] - prefix_v[i_];
    }

    for(int i = 0; i<n+1; i++){
        cout<<f_array[i]<<" ";
    }cout<<endl;


    


    return 0;
}
