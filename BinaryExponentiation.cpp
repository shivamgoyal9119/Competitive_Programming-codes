#include<bits/stdc++.h>
using namespace std;

int f(int a, int b){
    if(b == 0) return 1;

    int res = f(a, b/2);
    res *= res;
    if((b & 1) == 1) res *= a;

    return res;
}

int main(){

    // Binary Exponentiation or Fast Exponentiation
    // T.C -> O(log b) : a ^ b

    int a, b;
    cin>>a>>b;

    cout<<f(a, b)<<endl;

    return 0;
}