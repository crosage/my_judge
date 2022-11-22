#include <bits/stdc++.h>
using namespace std;

#define Int register int
#define MAXN 100005

// char buf[1<<21],*p1=buf,*p2=buf;
// #define getchar() (p1==p2 && (p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
template <typename T> inline void read(T &t) {
    t = 0;
    char c = getchar();
    int f = 1;

    while (c < '0' || c > '9') {
        if (c == '-')
            f = -f;

        c = getchar();
    }

    while (c >= '0' && c <= '9') {
        t = (t << 3) + (t << 1) + c - '0';
        c = getchar();
    }

    t *= f;
}
template <typename T, typename ... Args> inline void read(T &t, Args &... args) {
    read(t);
    read(args...);
}
template <typename T> inline void write(T x) {
    if (x < 0) {
        x = -x;
        putchar('-');
    }

    if (x > 9)
        write(x / 10);

    putchar(x % 10 + '0');
}
template <typename T> inline void chkmax(T &a, T b) {
    a = max(a, b);
}
template <typename T> inline void chkmin(T &a, T b) {
    a = min(a, b);
}

int n, q;
vector <int> g[MAXN];

int ind, dfn[MAXN], dep[MAXN], mxd[MAXN], les[MAXN], par[MAXN][21], st1[MAXN][21], st2[MAXN][21];

struct Node {
    priority_queue <int> q1, q2;
    void Push(int v) {
        q1.push(v);
    }
    void Dele(int v) {
        q2.push(v);
    }
    int Top() {
        while (!q1.empty() && !q2.empty() && q1.top() == q2.top())
            q1.pop(), q2.pop();

        if (!q1.empty())
            return q1.top();
        else
            return -1e9;
    }
} Seq[MAXN];

void dfs(int u, int fa) {
    par[u][0] = fa, dep[u] = dep[fa] + 1, dfn[u] = ++ ind;

    for (Int i = 1; i <= 20; ++ i)
        par[u][i] = par[par[u][i - 1]][i - 1];

    for (Int v : g[u])
        if (v ^ fa) {
            dfs(v, u);

            if (mxd[v] + 1 > mxd[u])
                les[u] = mxd[u], mxd[u] = mxd[v] + 1;
            else
                chkmax(les[u], mxd[v] + 1);
        }

    for (Int v : g[u])
        if (v ^ fa) {
            Seq[u].Push(mxd[v] + 1);

            if (mxd[v] + 1 == mxd[u])
                st1[v][0] = les[u] - dep[u], st2[v][0] = les[u] + dep[u];
            else
                st1[v][0] = mxd[u] - dep[u], st2[v][1] = mxd[u] + dep[u];
        }

    // cout << "rnm??? " << u << ": " << mxd[u] << " , " << les[u] << endl;
}

int getlca(int u, int v) {
    if (dep[u] < dep[v])
        swap(u, v);

    for (Int i = 20, dis = dep[u] - dep[v]; ~i; -- i)
        if (dis >> i & 1)
            u = par[u][i];

    if (u == v)
        return u;

    for (Int i = 20; ~i; -- i)
        if (par[u][i] ^ par[v][i])
            u = par[u][i], v = par[v][i];

    return par[u][0];
}
int climb(int u, int d) {
    for (Int i = 20; ~i; -- i)
        if (d >> i & 1)
            u = par[u][i];

    return u;
}

#define pii pair<int,int>
#define se second
#define fi first
pii getmid(int u, int v) {
    int lca = getlca(u, v), len = dep[u] + dep[v] - 2 * dep[lca];

    // cout << u << " , " << v << " , " << lca << ": " << dep[u] << " , " << dep[v] << " , " << dep[lca] << endl;
    if (len & 1) {
        if (dep[u] - dep[lca] < dep[v] - dep[lca]) {
            int p1 = climb(v, len >> 1), p2 = par[p1][0];
            return {p1, p2};
        } else {
            int p1 = climb(u, len >> 1), p2 = par[p1][0];
            return {p1, p2};
        }
    } else {
        if (dep[u] - dep[lca] < dep[v] - dep[lca]) {
            int p1 = climb(v, len >> 1);
            return {p1, p1};
        } else {
            int p1 = climb(u, len >> 1);
            return {p1, p1};
        }
    }
}

vector <int> sT;
namespace Subtask1 { //for situation:size>=B
bool imp[MAXN];
int f[MAXN], h[MAXN];
void dfs1(int u, int fa) {
    f[u] = 1e9;

    if (imp[u])
        f[u] = 0;

    for (Int v : g[u])
        if (v ^ fa)
            dfs1(v, u), chkmin(f[u], f[v] + 1);
}
void dfs2(int u, int fa) {
    h[u] = f[u];

    if (fa)
        chkmin(h[u], h[fa] + 1);

    for (Int v : g[u])
        if (v ^ fa)
            dfs2(v, u);
}
void Work() {
    for (Int x = 1; x <= n; ++ x)
        imp[x] = 0;

    for (Int x : sT)
        imp[x] = 1;

    dfs1(1, 0), h[0] = 1e9, dfs2(1, 0);
    int ans = 0;

    for (Int x = 1; x <= n; ++ x)
        chkmax(ans, h[x]);

    write(ans), putchar('\n');
}
}

int getmxv1(int u, int d) {
    int mxv = -1e9;

    for (Int i = 20; ~i; -- i)
        if (d >> i & 1)
            chkmax(mxv, st1[u][i]), u = par[u][i];

    return mxv;
}
int getmxv2(int u, int d) {
    int mxv = -1e9;

    for (Int i = 20; ~i; -- i)
        if (d >> i & 1)
            chkmax(mxv, st2[u][i]), u = par[u][i];

    return mxv;
}

namespace Subtask2 { //for situation:size<B
vector <int> sG, T[MAXN];
int ans, top, sta[MAXN];
bool imp[MAXN];
void linkit(int u, int v) {
    // cout << u << " ---> " << v << endl,
    T[u].push_back(v);
}
void build() {
    sG = sT;

    // cout << getmid (927,1744).fi << endl;
    // return ;
    // for (Int x : sT) cout << x << " , ";cout << endl;
    for (Int i = 0; i < sT.size(); ++ i)
        for (Int j = i + 1; j < sT.size(); ++ j) {
            pii it = getmid(sT[i], sT[j]);
            sG.push_back(it.fi);

            // cout << sT[i] << " & " << sT[j] << ": " << it.fi << endl;
            if (it.se != it.fi)
                sG.push_back(it.se);
        }

    sG.push_back(1), sort(sG.begin(), sG.end(), [](int x, int y) {
        return dfn[x] < dfn[y];
    }), sG.erase(unique(sG.begin(), sG.end()), sG.end());
    sta[top = 1] = 1;

    for (Int x : sT)
        imp[x] = 1;

    for (Int x : sG) {
        if (x == 1)
            continue;

        // cout << "add it : " << x << endl;
        int lca = getlca(x, sta[top]);

        if (lca == sta[top])
            sta[++ top] = x;
        else {
            while (top > 1 && dep[sta[top - 1]] >= dep[lca])
                linkit(sta[top - 1], sta[top]), -- top;

            if (lca != sta[top])
                linkit(lca, sta[top]), sta[top] = lca;

            sta[++ top] = x;
        }
    }

    while (top > 1)
        linkit(sta[top - 1], sta[top]), -- top;
}
void clearit() {
    for (Int x : sT)
        imp[x] = 0;

    sG.clear(), sT.clear();
}
int f[MAXN], h[MAXN];
void dfs1(int u, int fa) {
    f[u] = 1e9;

    if (imp[u])
        f[u] = 0;

    for (Int v : T[u])
        dfs1(v, u), chkmin(f[u], f[v] + dep[v] - dep[u]);
}
void dfs2(int u, int fa) {
    h[u] = f[u];

    if (fa)
        chkmin(h[u], h[fa] + dep[u] - dep[fa]);

    // if (u == 2393) cout << u << ": " << Seq[u].Top() << endl;
    for (Int v : T[u]) {
        int p = climb(v, dep[v] - dep[u] - 1);
        // if (u == 2393) cout << u << " ----> " << p << endl;
        Seq[u].Dele(mxd[p] + 1);
    }

    int oth = max(0, Seq[u].Top());
    chkmax(ans, h[u] + oth);

    // if (u == 2393) cout << "fuck you!!! " << u << ": " << h[u] << " , " << oth << endl;
    for (Int v : T[u]) {
        int p = climb(v, dep[v] - dep[u] - 1);
        // if (u == 2393) cout << "add back: " << u << " ---> " << p << endl;
        Seq[u].Push(mxd[p] + 1);
    }

    if (dep[fa] + 1 != dep[u]) {
        if (h[u] + 1 <= h[fa] + dep[u] - dep[fa] - 1)
            chkmax(ans, getmxv1(u, dep[u] - dep[fa] - 1) + dep[u] + h[u]);
        else
            chkmax(ans, getmxv2(u, dep[u] - dep[fa] - 1) - dep[fa] + h[fa]);
    }

    for (Int v : T[u])
        dfs2(v, u);

    T[u].clear();
}
void Work() {
    build(), ans = 0, dfs1(1, 0), dfs2(1, 0), write(ans), putchar('\n'), clearit();
}
}

signed main() {
    // freopen ("do0.in","r",stdin);
    read(n, q);

    for (Int i = 2, u, v; i <= n; ++ i)
        read(u, v), g[u].push_back(v), g[v].push_back(u);

    dfs(1, 0);

    for (Int i = 1; i <= 20; ++ i)
        for (Int u = 1; u <= n; ++ u)
            st1[u][i] = max(st1[u][i - 1], st1[par[u][i - 1]][i - 1]),
                        st2[u][i] = max(st2[u][i - 1], st2[par[u][i - 1]][i - 1]);

    int B = 50;

    while (q -- > 0) {
        int Siz;
        read(Siz), sT.resize(Siz);

        for (Int i = 0; i < Siz; ++ i)
            read(sT[i]);

        // cout << q << ": ";
        if (Siz >= B)
            Subtask1::Work();
        else
            Subtask2::Work();
    }

    return 0;
}
/*
7 1
5 4
6 5
7 3
7 4
1 5
2 4
2
2 3

7 2
5 4
6 5
7 3
7 4
1 5
2 4
1
4
1
6
*/