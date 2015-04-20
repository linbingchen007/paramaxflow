//
//  main.cpp
//  paramaxflow
//
//  Created by linbingchen on 15/4/20.
//  Copyright (c) 2015年 linbingchen. All rights reserved.
//

#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
const int maxn = 105;
int e[maxn];
int c[maxn][maxn],f[maxn][maxn];
int h[maxn];
int vis[maxn];
int mp[maxn][maxn];
int n,m;
int s,t;
vector<int> adj[maxn];
void addedge(int u,int v,int tc){
    c[u][v]=tc;
    mp[u][v]=1; //单向边 判断用
    adj[u].push_back(v);
    adj[v].push_back(u);
}

inline int cf(int u,int v){
    return c[u][v]-f[u][v];
}


int stk[maxn];
int tl;

void push(int u,int v){ //if d[u]==d[v]+1 and c[u][v]-f[u][v]>0
    int dtuv = min(e[u],cf(u,v));
    f[u][v]=f[u][v]+dtuv;
    f[v][u]=f[v][u]-dtuv;
    e[u]-=dtuv;
    e[v]+=dtuv;
    if(e[v]&&!vis[v]&&v!=s&&v!=t){
        stk[tl++]=v;
        vis[v]=1;
    }
}

void initialize_preflow(){ //init e h f
    memset(e,0,sizeof(e));
    memset(h,0,sizeof(h));
    memset(f,0,sizeof(f));
    h[s]=n;
    for (int i=0;i<adj[s].size();i++){
        int tv=adj[s][i];
        if(mp[s][tv]){
            f[s][tv]=c[s][tv];
            f[tv][s]=-f[s][tv];
            e[tv]=c[s][tv];
            e[s]=e[s]-c[s][tv];
            if (e[tv]>0&&!vis[tv]&&tv!=s&&tv!=t){
                stk[tl++]=tv;
                vis[tv]=1;
            }
        }
    }
}

void init(int ps,int pt,int pn,int pm){
    s=ps;
    t=pt;
    n=pn;
    m=pm;
    memset(c, 0, sizeof(c));  //init c mp adj
    memset(mp, 0, sizeof(mp));
    memset(vis, 0, sizeof(vis));
    for(int i =1;i<=n;i++) adj[i].clear();
    int tu,tv,tc; //make adj mp c
    //printf("输入m个边");
    for(int i = 1;i<=m;i++){
        cin>>tu>>tv>>tc;
        addedge(tu,tv,tc);
    }
    initialize_preflow(); //init e h f
}

void generic_push_relabel(int ps,int pt,int pn,int pm){
    //init(ps,pt,pn,pm);
    while(tl){
        int u = stk[--tl];
        vis[u]=0;
        int nhu=1<<30;
        int fg=1;
        for(int i=0;i<adj[u].size() && e[u]>0;i++){
            int v=adj[u][i];
            if (h[u]==h[v]+1 && c[u][v]-f[u][v]>0){
                fg=0;
                push(u,v);
            }else if(fg && h[u]<=h[v] && c[u][v]-f[u][v]>0){
                nhu=min(h[v],nhu);
            }
        }
        if (fg){
            h[u]=nhu+1;
        }
        if (e[u]>0){
            stk[tl++]=u;
            vis[u]=1;
        }
    }
    cout<<e[t]<<endl;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    int ts,tt,tn,tm;
    int np,nc,nm;
    while(cin>>tn){
        tn+=2;
        cin>>np>>nc>>nm;
        tm=nm+np+nc;
        s=1;
        t=tn;
        n=tn;
        m=tm;
        memset(c, 0, sizeof(c));  //init c mp adj
        memset(mp, 0, sizeof(mp));
        memset(vis, 0, sizeof(vis));
        for(int i =1;i<=n;i++) adj[i].clear();
        int tu,tv,tc;
        for(int i=1;i<=nm;i++){
            scanf(" (%d,%d)%d", &tu, &tv, &tc);
            addedge(tu+2,tv+2,tc);
        }
        for(int i=1;i<=np;i++){
            scanf(" (%d)%d", &tv, &tc);
            addedge(1,tv+2,tc);
        }
        for(int i=1;i<=nc;i++){
            scanf(" (%d)%d", &tu, &tc);
            addedge(tu+2, tn, tc);
        }
        initialize_preflow();
        generic_push_relabel(ts,tt,tn,tm);
    }
    
    return 0;
}
