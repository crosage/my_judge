#include <iostream>
#include <cstring>
using namespace std;
int n;
int map[7][10][7];
bool checkM[7][10];
int xx[7],yy[7],ww[7],xxx[7],yyy[7],www[7];
bool flag;
int ans=7;

int read()
{
	int s=0;
	char ch=getchar();
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch))
	{
		s=(s<<3)+(s<<1)+(ch^'0');
		ch=getchar();
	}
	return s;
}
void In()
{
	n=read();
	int k,GET;
	for(int i=1;i<=5;++i)
	{
		k=0;
		GET=read();
		while(GET)
		{
			map[i][++k][0]=GET;
			GET=read();
		}
	}
}
void check(int ste)
{
	bool b=0;
	memset(checkM,0,sizeof(checkM));
	flag=1;
	for(int i=1;i<=5;++i)
		for(int j=1;j<=7;++j)
		{
			int color=map[i][j][ste];
			if(color!=0)
			{
				flag=0;
				if(i<=3 && map[i+1][j][ste]==color && map[i+2][j][ste]==color)
					b=1,checkM[i][j]=checkM[i+1][j]=checkM[i+2][j]=1;
				if(j<=5 && map[i][j+1][ste]==color && map[i][j+2][ste]==color)
					b=1,checkM[i][j]=checkM[i][j+1]=checkM[i][j+2]=1;
			}
		}
	if(b)
	{
		for(int i=1;i<=5;++i)
			for(int j=1;j<=7;++j)
				if(checkM[i][j])
					map[i][j][ste]=0;
		bool bb=0;
		for(int i=1;i<=5;++i)
			for(int j=2;j<=7;++j)
			{
				int k=j-1;
				while(map[i][k][ste]==0 && k>=1)
				{
					bb=1;
					map[i][k][ste]=map[i][k+1][ste];
					map[i][k+1][ste]=0;
					--k;
				}
			}
		if(bb) check(ste);
	}
}
void swi(int x,int y,int way,int ste)
{
	for(int i=1;i<=5;++i)
		for(int j=1;j<=7;++j)
			map[i][j][ste+1]=map[i][j][ste];
	swap(map[x+way][y][ste+1],map[x][y][ste+1]);
	xxx[ste+1]=x,yyy[ste+1]=y,www[ste+1]=way;
}
void print()
{
	if(ans>n) cout<<-1;
	else for(int i=1;i<=ans;++i)
		cout<<xx[i]-1<<' '<<yy[i]-1<<' '<<ww[i]<<endl;
}
void dfs(int step)
{
	if(step>n || step>=ans) return;
	if(flag)
	{
		if(step<ans)
		{
			ans=step;
			for(int i=1;i<=ans;++i) xx[i]=xxx[i],yy[i]=yyy[i],ww[i]=www[i];
		}
		flag=0;
		return;
	}
	for(int i=1;i<=5;++i)
		for(int j=1;j<=7;++j)
			if(map[i][j][step])
			{
				if(i<=4 && map[i][j][step]!=map[i+1][j][step])
				{
					swi(i,j,1,step);
					check(step+1);
					dfs(step+1);
				}
				if(i>=2 && map[i-1][j][step]==0)
				{
					swi(i,j,-1,step);
					check(step+1);
					dfs(step+1);
				}
			}
}
int main()
{
    
	In();
    double start=clock(),end=0;
	dfs(0);
	print();
    end=clock();
    printf("%lf\n",(end-start)/1000);
	return 0;
}