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

vector<vector<ll>> matExpo(vector<vector<ll>> base, ll exp) {  // use when recursion stack space matter.
    int size = base.size();
    vector<vector<ll>> result(size, vector<ll>(size, 0));

    // Identity matrix
    for (int i = 0; i < size; ++i)
        result[i][i] = 1;

    while (exp > 0) {
        if (exp % 2 == 1)
            result = matmul(result, base, size);
        base = matmul(base, base, size);
        exp /= 2;
    }

    return result;
}

int main(){

    // For using purpose we only need the matrix and power(n)
    // ans = matExpo(matrix, power);






    
    
    // ********** Fully Tested Via (Codeforces & Leetcode) **********
    return 0;
}
