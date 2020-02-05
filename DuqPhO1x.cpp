#include <bits/stdc++.h>
using namespace std;
const int N = 2e3 + 10;
int n, m, e;
vector<int> G[N]; //使用邻接表来储存边
int match[N], vis[N];
bool dfs(int u)
{
    int len = G[u].size();
    for (int i = 0; i < len; i++)
    { //遍历每一条边
        int v = G[u][i];
        if (vis[v])
            continue;
        vis[v] = 1;
        if (!match[v] ||
            dfs(match[v]))
        { //如果v没有匹配，或者v的匹配找到了新的匹配
            match[v] = u;
            match[u] = v; //更新匹配信息
            return 1;
        }
    }
    return 0;
}
int main()
{
    scanf("%d %d %d", &n, &m, &e);
    for (int i = 1; i <= e; i++)
    {
        int a, b;
        scanf("%d %d", &a, &b);
        if (a > n || b > m)
            continue;
        G[a].push_back(n + b);
        G[n + b].push_back(a);
    }
    int ans = 0;
    for (int i = 1; i <= n; i++)
    { //对每一个点尝试匹配
        for (int j = 1; j <= n + m; j++)
            vis[j] = 0;
        if (dfs(i))
            ans++;
    }
    printf("%d", ans);
    return 0;
}