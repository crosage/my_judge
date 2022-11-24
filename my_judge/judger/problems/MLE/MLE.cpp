#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll read(){
	ll ret=0;
	char c=getchar();
	while(c<'0'||c>'9')c=getchar();
	while(c>='0'&&c<='9'){
		ret*=10;
		ret+=c-'0';
		c=getchar();
	}
	return ret;
}
ll n,k;
ll ans,tmp;
namespace subtask1{
	void work(){
		ans=0;
		for(int i=1;i<=n;i++){
			tmp=read();
			ans^=tmp;
		}
		printf("%lld",ans);
		return ;
	}
}
namespace subtask2{
	set<int>s;
	set<int>::iterator it;
	void work(){
		while(n--){
			tmp=read();
			it=s.find(tmp);
			if(it!=s.end()){
				s.erase(it);
			}else{
				s.insert(tmp);
			}
		}
		for(it=s.begin();it!=s.end();it++){
			printf("%d ",*it);
		}
	} 
}
int main(){
	// freopen("sort.in","r",stdin);
	// freopen("sort.out","w",stdout);
	n=read();
	k=read();
	if(k==1){
		subtask1::work();
	}else{
		subtask2::work();
	}
	return 0;
}