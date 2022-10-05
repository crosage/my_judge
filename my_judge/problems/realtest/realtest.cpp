#include<bits/stdc++.h>
#include<unistd.h>
using namespace std;
#define ll long long
ll mp[8][6],vis[10][10],sta[10],del[10][10];
ll top,tt;
const ll n=7,m=5;
struct node{
	ll x,y;
	node(){}
	node(const ll &a,const ll &b){x=a,y=b;}
};
struct an{
	ll x,y,g;
	an(){}
	an(const ll &a,const ll &b,const ll &c){x=a,y=b,g=c;}
}ans[7];
deque<node> q,p;
ll ok(ll x,ll y,ll opt){
	if(x>=1&&x<=n&&y>=1&&y<=m&&mp[x][y]==opt&&!vis[x][y]) return 1; 
	return 0;
}
void print(){
	puts("wwb");
	for(ll i=1;i<=n;i++,puts(""))
		for(ll j=1;j<=m;j++){
			printf("%lld ",mp[i][j]);
		}
}
void down(){
	for(ll i=1;i<=m;i++){
		top=0;
		for(ll j=1;j<=n;j++)
			if(mp[j][i])
				sta[++top]=mp[j][i];
		for(ll j=1;j<=n;j++)
			mp[j][i]=0;
		for(ll j=1;j<=top;j++)
			mp[j][i]=sta[j];
	}
}
void xiao(){
	ll ok=0;
	down();	
	memset(del,0,sizeof(del));
	for(ll i=1;i<=n;i++)
		for(ll j=1;j<=m;j++){
			if(mp[i][j]){
				if(i>1&&i<n){
					if(mp[i][j]==mp[i+1][j]&&mp[i][j]==mp[i-1][j]){
						del[i][j]=1,del[i+1][j]=1,del[i-1][j]=1;
						ok=1;
					}
				}
				if(j>1&&j<m){
					if(mp[i][j]==mp[i][j-1]&&mp[i][j]==mp[i][j+1]){
						del[i][j]=1,del[i][j-1]=1,del[i][j+1]=1;
						ok=1;
					}
				}
			}
		}
	if(!ok) return ;
	for(ll i=1;i<=n;i++)
		for(ll j=1;j<=m;j++)
			if(del[i][j])
				mp[i][j]=0;
	down();
	xiao();
	return ;
}
ll ttt;
ll check(){
	for(ll i=1;i<=m;i++)
		if(mp[1][i]) return 0;
	return 1;
}
void cpy(ll x[][6],ll y[][6]){
	for(ll i=1;i<=n;i++)
		for(ll j=1;j<=m;j++)
			x[i][j]=y[i][j];
}
void dfs(ll cnt){
//	printf("%lld\n",cnt);
	if(check()&&cnt==tt+1){
		for(ll i=1;i<=tt;i++)
			printf("%lld %lld %lld\n",ans[i].x,ans[i].y,ans[i].g);
		exit(0);
	}
	if(cnt>=tt+1) return ;
	ll mem[8][6];
	for(ll j=1;j<=m;j++)
		for(ll i=1;i<=n;i++){
			if(mp[i][j]){				
				if(j!=m&&mp[i][j]!=mp[i][j+1]){
					cpy(mem,mp);
					ans[++ttt]=an(j-1,i-1,1);
					swap(mp[i][j],mp[i][j+1]);
					xiao();
					dfs(cnt+1);ttt--;
					cpy(mp,mem);
				}
				if(j!=1&&!mp[i][j-1]){
					cpy(mem,mp);
					ans[++ttt]=an(j-1,i-1,-1);
					swap(mp[i][j],mp[i][j-1]);
					xiao();
					dfs(cnt+1);ttt--;
					cpy(mp,mem);
				}

			}
		}
}
ll cnt[7];
int main(){
	scanf("%lld",&tt);ll x;
	x=1;while(x!=0){scanf("%lld",&x);mp[++cnt[1]][1]=x;}
	x=1;while(x!=0){scanf("%lld",&x);mp[++cnt[2]][2]=x;}
	x=1;while(x!=0){scanf("%lld",&x);mp[++cnt[3]][3]=x;}
	x=1;while(x!=0){scanf("%lld",&x);mp[++cnt[4]][4]=x;}
	x=1;while(x!=0){scanf("%lld",&x);mp[++cnt[5]][5]=x;}
	xiao();
	dfs(1);
	while(1);
	puts("-1");
}