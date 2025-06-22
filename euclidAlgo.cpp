#include<bits/stdc++.h> 
#include <algorithm>
using namespace std;

int getGCD(int a, int b){
    if(a == 0) return b;
    return getGCD(b%a, a);
}

int main(){

    // use to find gcd;
    // imp. relation => (a * b) / gcd(a, b) = lcm(a, b);

    int a, b;
    cin>>a>>b;
    cout<<getGCD(a, b)<<endl;
    // cout<<__gcd(a, b);
    // TC => O(logn)


    return 0;
} 