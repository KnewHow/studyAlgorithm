#include <stdio.h>
#include <string.h>
int vis[14], e[14][14], link[14], op, tp;
void DFS(int x, int n);//深度优先搜索
void BFS(int x, int n);//广度优先搜索
int main()
{
    int n, m, u, v, i;
    while(scanf("%d %d", &n, &m) != EOF)
    {
        memset(vis, 0, sizeof(vis));//vis数组初始化（vis数组标记当前结点是否被访问过）
        memset(e, 0, sizeof(e));//e数组初始化（e数组记录结点之间是否存在路径）
        for(i = 0; i < m; i++)
        {
            scanf("%d %d", &u, &v);
            e[u][v] = e[v][u] = 1;
        }
        for(i = 0; i < n; i++)
        {
            if(vis[i] == 0)
            {
                printf("{");
                DFS(i, n);//深度优先搜索
                printf(" }\n");
            }
        }
        op = tp = 0;//队列标记变量初始化
        memset(vis, 0, sizeof(vis));//vis数组初始化（vis数组标记当前结点是否被访问过）
        for(i = 0; i< n; i++)
        {
            if(vis[i] == 0)
            {
                printf("{");
                BFS(i, n);//广度优先搜索
                printf(" }\n");
            }
        }
    }
    return 0;
}
void DFS(int x, int n)//深度优先搜索
{
    int i;
    printf(" %d", x);
    vis[x] = 1;
    for(i = 0; i < n; i++)
    {
        if(vis[i] == 0 && e[x][i] == 1)
        {
            DFS(i, n);//深度优先搜索（递归思想）
        }
    }
}
void BFS(int x, int n)//广度优先搜索(队列思想)
{
    int i, f1;
    link[tp++] = x;//当前结点入队
    vis[x] = 1;
    while(op < tp)
    {
        f1 = link[op++];//头结点出队
        printf(" %d", f1);
        for(i = 0; i < n; i++)
        {
            if(vis[i] == 0 && e[f1][i] == 1)
            {
                vis[i] = 1;
                link[tp++] = i;//当前结点入队
            }
        }
    }
}