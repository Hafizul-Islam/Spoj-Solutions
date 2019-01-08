/*
    Author:Md Hafizul Islam
    Category: Centroid Decomposition && Lca
    Complexity: nlogn
*/
#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define ff first
#define ss second
typedef long long ll;
typedef pair <int,int > ii;
typedef vector<int> vi;
typedef vector <ii> vii;
const int mx=1e5+3;
const int INF=1e5+7;
set<int> g[mx];
int dp[mx][20],lv[mx],sub[mx],n,par[mx],ans;
bool white[mx];
struct path{
    int to,distt;
    inline bool operator <(const path &other) const
    { return distt>other.distt ; }
};
void dfs0(int u,int p){
    for(auto it=g[u].begin();it!=g[u].end();it++){
        if(*it!=p){
            dp[*it][0]=u;
            lv[*it]=lv[u]+1;
            dfs0(*it,u);
        }
    }
}
void preprocess(){
    lv[1]=0;
    memset(dp,-1,sizeof dp);
    dfs0(1,-1);
    for(int j=1;(1<<j)<n;j++){
        for(int i=1;i<=n;i++){
            if(dp[i][j-1]!=-1) dp[i][j]=dp[ dp[i][j-1 ]][j-1];
        }
    }
}
int lca(int p,int q){
    if(lv[p]<lv[q]) swap(p,q);
    int log=1;
    while(1){
        int next=log+1;
        if( (1<<next)>lv[p]) break;
        log++;
    }
    for(int i=log;i>=0;i--) if(lv[p]-(1<<i)>=lv[q]) p=dp[p][i];
    if(p==q) return p;
    for(int i=log;i>=0;i--){
        if(dp[p][i]!=-1&&dp[p][i]!=dp[q][i])
            p=dp[p][i],q=dp[q][i];
    }
    return dp[p][0];
}
int dist(int u,int v){ return lv[u]+lv[v]-2*lv[lca(u,v)];
    }
/*Decompose part*/
int nn=0;
void dfs1(int u,int p){
    sub[u]=1;
    nn++;
    for(auto it=g[u].begin();it!=g[u].end();it++){
        if(*it!=p){
            dfs1(*it,u);
            sub[u]+=sub[*it];
        }
    }
}
int dfs2(int u,int p){
    for(auto it=g[u].begin();it!=g[u].end();it++){
        if(*it!=p&& sub[*it]>nn/2){
            return dfs2(*it,u);
        }
    }
    return u;
}
void decompose(int r,int p){
    nn=0;dfs1(r,r);
    int centroid=dfs2(r,r);
    if(p==-1) p=centroid;
    par[centroid]=p;
    for(auto it=g[centroid].begin();it!=g[centroid].end();it++){
        g[*it].erase(centroid);
        decompose(*it,centroid);
    }
    g[centroid].clear();
}
priority_queue<path> que[mx];
int dist_white(int x)
{
    priority_queue<path> &q=que[x];
    while(!q.empty()){
        path cur=q.top();
        if( !white[cur.to]) q.pop();
        else return cur.distt;
    }
    return INF;
}

int main()
{   int u,v,x,root,q;
    cin>>n;
    for(int i=1;i<n;i++){
        cin>>u>>v;
        g[u].insert(v);
        g[v].insert(u);
    }
    preprocess();
    decompose(1,-1);
  //  for(int i=1;i<=n;i++) cout<<par[i]<<" ";
    cin>>q;
    while(q--){
        cin>>u>>x;
        if(u==0){
            white[x]=!white[x];
            if(white[x]){
                int root=x;
                while(1){
                    que[root].push(path{x,dist(x,root)});
                 //   cout<<x<<" "<<dist(x,root)<<endl;
                    if(par[root]==root) break;
                    root=par[root];
                }
            }
        }
        else{
            root=x,ans=INF;
            while(1){
                ans=min(ans,dist(x,root)+dist_white(root));
                //cout<<dist(x,root)<<" "<<dist_white(root)<<endl;
                if(par[root]==root) break;
                root=par[root];
            }
            printf("%d\n",(ans==INF)?-1:ans);

        }
    }
    return 0;
}
