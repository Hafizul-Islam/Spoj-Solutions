/*
    https://www.spoj.com/problems/DQUERY/
    mos algorithm
    accepted
    Md Hafizul Islam
*/
#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define f first
#define s second
#define mx 550
#define N 311111
#define block 555
#define A 1111111
typedef long long ll;
typedef pair <int,int > ii;
typedef vector<int> vi;
typedef vector <ii> vii;

int cnt[A],a[N],ans[N],answer=0;
struct node{
    int l,r,index;
}q[N];
bool cmp(node a,node b){
    if(a.l/block != b.l/block) return a.l/block < b.l/block;
    return a.r < b.r;
}
void add(int pos){
    cnt[ a[pos] ]++;
    if(cnt[ a[pos] ]==1 ) answer++;
}
void remove(int pos){
    cnt[ a[pos] ]--;
    if(cnt[ a[pos] ]==0) answer--;
}
int main()
{
    int n,i,m;
    scanf("%d",&n);
    for(i=0;i<n;i++) scanf("%d",&a[i]);
    scanf("%d",&m);
    for(i=0;i<m;i++){
        scanf("%d%d",&q[i].l,&q[i].r);
        q[i].l--;
        q[i].r--;
        q[i].index=i;
    }
    sort(q,q+m,cmp);

    int currentL=0,currentR=0;
    for(i=0;i<m;i++){
        int L=q[i].l,R=q[i].r;
        while(currentL < L){
            remove(currentL);
            currentL++;
        }
        while(currentL > L){
            add(currentL-1);
            currentL--;
        }
        while(currentR<=R){
            add(currentR);
            currentR++;
        }
        while(currentR > R+1){
            remove(currentR-1);
            currentR--;
        }

        ans[ q[i].index ] = answer;
    }
    for(i=0;i<m;i++) printf("%d\n",ans[i]);
    return 0;
}
