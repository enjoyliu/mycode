#include <bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;++i)
#define pb push_back
typedef long double LD;
typedef unsigned long long ll;
const int N = 5e6 + 100;
using namespace std;
struct node {
    int x;
    ll t;
    node(){}
    node(int a,ll b) {x=a,t=b;}
    bool operator < (const node a) const {
        if(t==a.t) return  x<a.x;
        return t < a.t;
    }
};
bool cmp(node a,node b) {
    if(a.x==b.x) return a.t < b.t;
    return a.x < b.x;
}
bool cmp0(node a,node b) {
    if(a.t==b.t) return a.x > b.x;
    return a.t < b.t;
}
vector<node> v;
map<node,int> id;
node fid[N];
int cnt;

int nxt[N];
LD dp[N];
vector< pair<int,LD> > E[N];
void nwnode(node a) {
    if(id[a]!=0) return;
    ++cnt;
    fid[cnt] = a;
    id[a] = cnt;
}
void add(int a,int b,LD p){
    E[a].pb(make_pair(b,p));
}
int n,m;
ll k;

int main() {int f=0;
    ll MX=0,MN=1000000000000000002LL;
    scanf("%d%d%llu",&m,&n,&k);
    rep(i,1,m) {int a,b;ll s,t; double p;
        scanf("%d %d %llu %llu %lf",&a,&b,&s,&t,&p);
        if(t<=k){
            nwnode(node(a,s));
            nwnode(node(b,t));

            add(id[node(a,s)],id[node(b,t)],(LD)p);
            v.pb(node(a,s));
            v.pb(node(b,t));
            if(b == 1LL) {
                dp[id[node(b,t)]] = 1.0;
                MX = max(t,MX);
            }
            if(a==0){
                if(!f)MN=t;
                else MN=min(MN,t);
                f=1;
            }
        }
    }

    nwnode(node(1,MX));
    nwnode(node(1,k));
    nxt[id[node(1,MX)]] = id[node(1,k)];
    dp[id[node(1,k)]] = 1.0;
    v.pb(node(1,k));
    add(id[node(1,MX)],id[node(1,k)],1.0);

    nwnode(node(0,0));
    v.pb(node(0,0));
    nxt[id[node(0,0)]] = id[node(0,MN)];
    add(id[node(0,0)],id[node(0,MN)],1.0);

    sort(v.begin(),v.end(),cmp);
    for(int i=v.size()-2;i>=0;--i) {
        if(v[i].x==v[i+1].x){
            if(v[i].t == v[i+1].t) nxt[id[v[i]]] = nxt[id[v[i+1]]];
            else nxt[id[v[i]]] = id[v[i+1]];
        }
    }
    sort(v.begin(),v.end(),cmp0);

    for(int i=v.size()-1;i>=0;--i) if(dp[id[v[i]]]==0){
        LD mx = 0;int t = id[v[i]];
        for(int j=0;j<E[t].size();++j) {
            if(fid[nxt[E[t][j].first]].x == fid[E[t][j].first].x && fid[nxt[t]].x == fid[t].x && dp[nxt[t]]!=0 && dp[nxt[E[t][j].first]]!=0 )
                mx = max(mx, E[t][j].second*dp[nxt[E[t][j].first]] + (1.0-E[t][j].second)*dp[nxt[t]]);
            else if(fid[nxt[E[t][j].first]].x == fid[E[t][j].first].x && dp[nxt[E[t][j].first]]!=0)
                mx = max(mx, E[t][j].second*dp[nxt[E[t][j].first]]);
            else if(fid[nxt[t]].x == fid[t].x && dp[nxt[t]]!=0)
                mx = max(mx, (1.0-E[t][j].second)*dp[nxt[t]]);
        }
        if(fid[nxt[t]].x == fid[t].x)
            mx = max(mx, dp[nxt[t]]);
        dp[t] = mx;
    }
    printf("%.10f\n",(double)dp[id[node(0,0)]]);
    return 0;
}