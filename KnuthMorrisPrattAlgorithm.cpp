#include<iostream>
using namespace std;

void getUpdtLPS(string &s, vector<int> &LPS){
    int len = 0, n = s.size(), i = 1;
    while(i < n){
        if(s[i] == s[len]) LPS[i++] = ++len;
        else{
            if(len == 0) LPS[i++] = 0;
            else len = LPS[len-1];
        }
    }
}

int main(){

    string s = "abcbabcaababaaab";
    int n = s.size();
    vector<int> LPS(n, 0);
    getUpdtLPS(s, LPS);

    for(int i = 0; i<n; i++) cout<<LPS[i]<<" ";
    cout<<endl;

    string pattern = "ab";
    int ans = 0, i = 0, j = 0;
    while(i < n){
        if(s[i] == pattern[j]){
            i++, j++;
            if(j >= pattern.size()){
                ans += 1;
                // cout<<i-j<<endl;
                j = LPS[j-1];
            }
        }else{
            if(j == 0) i++;
            else j = LPS[j-1];
        }
    }

    cout<<ans<<endl;

    return 0;
}
