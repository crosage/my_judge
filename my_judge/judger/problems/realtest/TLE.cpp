#include <bits/stdc++.h>

using namespace std;

int n;

int a[15][15];

struct node{
    int x, y, opt;
};

bool vis[15][15];

void init()
{
    for(int i = 0; i < 5; i++)
        for(int j = 0; j < 7; j++)
            vis[i][j] = false;
}

void drop()
{
    for(int i = 0; i < 5; i++)
    {
        for(int j = 0; j < 7; j++)
        {
            if(a[i][j] != 0)
            {
                int k = j;
                while(k > 0 && a[i][k-1] == 0)
                    swap(a[i][k], a[i][k-1]), k--;
            }
        }
    }
}

int merge()
{
    drop();
    init();
    for(int i = 0; i < 5; i++)
    {
        for(int j = 0; j < 7; j++)
        {
            if(a[i][j] == 0)break;
            if(a[i][j] == a[i+1][j] && a[i+1][j] == a[i+2][j])
                vis[i][j] = vis[i+1][j] = vis[i+2][j] = true;
            if(a[i][j] == a[i][j+1] && a[i][j+1] == a[i][j+2])
                vis[i][j] = vis[i][j+1] = vis[i][j+2] = true;
        }
    }
    int sum = 0;
    for(int i = 0; i < 5; i++)
        for(int j = 0; j < 7; j++)
            if(vis[i][j])a[i][j] = 0, sum++;
    return sum;
}

node st[10];

bool success;

void dfs(int left, int sum)
{
    int res = merge();
    while(res != 0)
        sum -= res, res = merge();
    if(left == 0 && sum != 0)return;
    if(left == 0 && sum == 0)
    {
        success = true;
        for(int i = n; i >= 1; i--)
            printf("%d %d %d\n", st[i].x, st[i].y, st[i].opt);
        return;
    }
    if(success)return;
    int b[15][15];
    memcpy(b, a, sizeof(a));
    for(int i = 0 ; i < 5; i++)
    {
        for(int j = 0; j < 7; j++)
        {
            if(success)return;
            if(a[i][j] == 0)break;
            if(i < 4)
            {
                if(st[left + 1].opt == 1)
                    if(st[left + 1].x == i && st[left + 1].y == j)
                        continue;
                if(st[left + 1].opt == -1)
                    if(st[left + 1].x == i + 1 && st[left + 1].y == j)
                        continue;
                swap(a[i][j], a[i+1][j]);
                st[left] = (node){i, j, 1};
                dfs(left-1, sum);
                memcpy(a, b, sizeof(b));
            }
            if(i > 0)
            {
                if(st[left + 1].opt == -1)
                    if(st[left + 1].x == i && st[left + 1].y == j)
                        continue;
                if(st[left + 1].opt == 1)
                    if(st[left + 1].x == i - 1 && st[left + 1].y == j)
                        continue;
                swap(a[i][j], a[i-1][j]);
                st[left] = (node){i, j, -1};
                dfs(left-1, sum);
                memcpy(a, b, sizeof(b));
            }
        }
    }
}

int main()
{
    scanf("%d", &n);
    int tot = 0;
    for(int i = 0; i < 5; i++)
    {
        int x, k = 0;
        while(scanf("%d", &x) && x != 0)
            a[i][k++] = x;
        tot += k;
    }
    dfs(n, tot);
    if(!success)printf("-1");
    return 0;
}