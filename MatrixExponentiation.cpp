#include<bits/stdc++.h>
using namespace std;

static const int MOD = 1e9 + 7;

vector<vector<int> > matmul(vector<vector<int> > &m1, vector<vector<int> > &m2, int n){
    vector<vector<int> > ans(n, vector<int> (n, 0));
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            long long cnt = 0;
            for(int k = 0; k < n; k++)
                cnt = (cnt + 1LL * m1[i][k] * m2[k][j]) % MOD;
            
            ans[i][j] = cnt;
        }
    }
    return ans;
}

vector<vector<int> > matExpo(vector<vector<int> > &mat, int n){
    if(n == 1) return mat;
    vector<vector<int> > ans = matExpo(mat, n/2);
    ans = matmul(ans, ans, ans.size());
    if((n & 1) == 1) ans = matmul(ans, mat, ans.size());
    return ans;
}

int main(){

    // For using purpose we only need the matrix and power(n)
    // ans = matExpo(matrix, power);
    

    return 0;
}
