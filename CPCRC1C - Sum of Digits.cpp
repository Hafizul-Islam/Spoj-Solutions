/*
    Accepted 
    Digit Dp problem
    Md Hafizul Islam
*/
#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define f first
#define s second
const int mx=1e5+9;
typedef long long ll;
typedef pair <int,int > ii;
typedef vector<int> vi;
typedef vector <ii> vii;
ll n,dp[18][140][2];
vi digitA,digitB;
void getDigit(ll x,vi &digit){
    while(x){
        digit.pb(x%10);
        x/=10;
    }
}
ll Digit_sum(int idx,ll sum,int restrict,vi &digit)
{
    if(idx==-1) return sum;
    if(dp[idx][sum][restrict]!=-1 && restrict !=1)
        return dp[idx][sum][restrict];
    ll ret=0;
    int k=(restrict)?digit[idx]: 9;
    for(int i=0;i<=k;i++){
        int New_restrict = (digit[idx]==i)?restrict: 0;
        ret+=Digit_sum(idx-1,sum+i,New_restrict,digit);
    }
    if(!restrict)
        dp[idx][sum][restrict]=ret;
    return ret;
}
int main()
{
    int t;
    memset(dp,-1,sizeof dp);
    while(1){
        ll a,b;
        cin>>a>>b;
        if(a==-1 && b==-1) return 0;
        getDigit(a-1,digitA);
        getDigit(b,digitB);
        ll ans1=Digit_sum(digitA.size()-1,0,1,digitA);
        ll ans2=Digit_sum(digitB.size()-1,0,1,digitB);
        cout<<(ans2-ans1)<<endl;
        digitA.clear();
        digitB.clear();
    }
    return 0;
}

