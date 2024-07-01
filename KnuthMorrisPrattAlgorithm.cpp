#include<iostream>
using namespace std;

void getFillLPS(string &p, vector<int> &LPS, int n){
    int len = 0, i = 1;
    while(i < n){
        if(p[len] == p[i]) LPS[i++] = ++len;
        else{
            if(len == 0) LPS[i++] = 0;
            else len = LPS[len-1];
        }
    }
}

void getAns(string &s, string &p, vector<int> &v){
    int ans = 0, i = 0, j = 0, n = s.size(), m = p.size();
    vector<int> LPS(m, 0);
    getFillLPS(p, LPS, m);
    while(i < n){
        if(s[i] == p[j]){
            i++, j++;
            if(j >= m){
                v.push_back(i-m);
                j = LPS[j-1];
            }
        }else{
            if(j == 0) i++;
            else j = LPS[j-1];
        }
    }
}

int main(){

    string s = "ababababazzabababb", p = "aba";
    vector<int> ans;
    getAns(s, p, ans);
    for(int i = 0; i<ans.size(); i++){
        cout<<ans[i]<<" ";
    }cout<<endl;


    return 0;
}
