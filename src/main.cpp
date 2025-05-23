// Online C++ compiler to run C++ program online
#include <bits/stdc++.h>
using namespace std;
int main() {
    
    string A = "bannnz",
    B = "annamoxz";
    
    int dp[7][10];
    memset(dp,0,sizeof(dp));
    
    for(int i = 5;i>=0;i--){
        for(int j= 8;j>=0;j--){
            if(A[i]==B[j])
            dp[i][j] = 1+dp[i+1][j+1];
            else{
                dp[i][j] = max(dp[i+1][j],dp[i][j+1]);
            }
        }
    }

    cout<<dp[0][0]<<endl;
    
    string ans="";
    int i=0,j=0;
    while(i<6 && j<9){
        if(A[i]==B[j]){
            ans+=A[i];
            i++;j++;
        }else{
            if(dp[i+1][j]>dp[i][j+1]){
                i++;
            }else{
                j++;
            }
        }
    }
    
    cout<<ans<<endl;
    return 0;
}