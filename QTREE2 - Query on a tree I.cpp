/* lca problem
   accepted code
   Md Hafizul Islam
*/
#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define f first
#define s second
const int mx=1<<14;
typedef long long ll;
typedef pair <int,int > ii;
typedef vector<int> vi;
typedef vector <ii> vii;
vector <ii> g[mx];
int t[mx],p[mx][14],l[mx];
int sum[mx];
void dfs1(int p,int u,int d)
{
    l[u]=d;
    for(int i=0;i<g[u].size();i++){
        ii v=g[u][i];
        if(v.f!=p){
            t[v.f]=u;
            sum[v.f]=sum[u]+v.s;
            dfs1(u,v.f,d+1);
        }
    }
}
int lca_querry(int n,int p1,int q1)
{
    int tmp,log,i;
    if(l[p1]<l[q1]) tmp=p1,p1=q1,q1=tmp;
    log=1;
    while(1){
        int next = log+1;
        if( (1<<next)>l[p1]) break;
        log++;
    }
    for(i=log;i>=0;i--){
        if(l[p1]-(1<<i)>=l[q1])
            p1=p[p1][i];
    }
    if(p1==q1) return p1;
    for(i=log;i>=0;i--){
        if(p[p1][i]!=-1 && p[p1][i]!=p[q1][i])
            p1=p[p1][i],q1=p[q1][i];
    }
    return t[p1];
}
void bulidLca(int n)
{
    int i,j,k;
    memset(p,-1,sizeof p);
    for(i=1;i<=n;i++) p[i][0]=t[i];

    for(j=1;(1<<j)<n;j++){
        for(i=1;i<=n;i++)
            if(p[i][j-1]!=-1) p[i][j]=p[p[i][j-1]][j-1];
    }
}
int find1(int p1, int t) {
	int i, stp;
	for(stp = 1; 1<<stp <= l[p1]; stp++); stp--;
	for(i = stp; i >= 0; i--)
		if(l[p1] - (1<<i) >= t)
			p1 = p[p1][i];
	return p1;
}
int main()
{
    int u,v,c,j,k,n,m,te;
    char str[8];
    scanf("%d",&te);
    while(te--){
        scanf("%d",&n);
        for(int i=1;i<=n;i++){
            g[i].clear();
            sum[i]=0;
            t[i]=-1;
        }
        for(int i=1;i<n;i++){
            scanf("%d%d%d",&u,&v,&c);
            g[u].pb(ii(v,c));
            g[v].pb(ii(u,c));
        }
        dfs1(-1,1,0);
        bulidLca(n);
        while(scanf("%s",&str)==1){
            if(str[1]=='O') break;
            scanf("%d%d",&u,&v);
            k=lca_querry(n,u,v);
            if(str[1]=='I'){
                printf("%d\n",sum[u]+sum[v]-2*sum[k]);
            }
            else if (str[1]=='T'){
                scanf("%d",&c);
                if(l[u]-l[k]+1>=c) m=find1(u,l[u]-c+1);
                else{
                    m=find1(v,2*l[k]+c-l[u]-1);}
                printf("%d\n",m);
            }
        }
        printf("\n");
    }
    return 0;
}
