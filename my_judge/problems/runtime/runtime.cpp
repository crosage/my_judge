#include <bits/stdc++.h>
#define N 500004
using namespace std;
typedef long long ll;

int n, m, rt; ll v[N];
int tI[N], tmr, tO[N]; ll bit[N];

struct es { int t, nxt; } e[N*2];
int hd[N], tot;

void add (int u, int v)
{
    e[++tot]=(es){ v, hd[u] };
    hd[u]=tot;
}

void add_bit (int x, int num)
{
    while (x<=n) {
        bit[x]+=num;
        x+=(x&(-x));
    }
}

ll qry (int l, int r)
{
    ll res=0;
    while (r) {
        res+=bit[r];
        r-=(r&(-r));
    }
    while (l) {
        res-=bit[l];
        l-=(l&(-l));
    }
    return res;
}

void dfs (int u, int fa)
{
    add_bit(++tmr, v[u]); tI[u]=tmr;

    for (int i=hd[u]; i; i=e[i].nxt) {
        int v=e[i].t;
        if (v==fa) { continue; }
        dfs(v, u);
    }

    tO[u]=tmr;
}

int main ()
{
    int a[5555];
    printf("%lld\n",a[64654]);

    return 0;
}