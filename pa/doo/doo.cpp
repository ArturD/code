#include<cstdio>
#include<vector>
#include<queue>

using namespace std;

struct Visitor {
  int vertex;
  int cost;
  int dir;
  Visitor(int v,int c,int d):vertex(v),cost(c),dir(d){}
  bool operator<(const Visitor& o) const {
    return cost > o.cost;
  }
};

const int maxn = 100005;
vector<int> NEXT[maxn];
vector<int> COST[maxn];
vector<int> DK  [maxn];
int W[maxn];
int VIS[maxn];
int LAST[maxn];
int m,n;

int dijkstra(int a) {
  priority_queue<Visitor> Q;
  Q.push( Visitor(a,0,0) );
  while( !Q.empty() ) {
    Visitor v = Q.top(); Q.pop();
    //fprintf(stderr, "  Q %d %d %d\n", v.vertex, v.cost, v.dir);
    if( v.vertex==a && v.dir!=0 ) return v.cost;
    if( VIS[v.vertex]==2 || (VIS[v.vertex]==1&&LAST[v.vertex]==v.dir) ) continue;
    VIS[v.vertex] ++;
    LAST[v.vertex] = v.dir;
    for(int i=0; i<NEXT[v.vertex].size(); i++) {
      int v2 = NEXT[v.vertex][i], cost2 = v.cost+COST[v.vertex][i], k2 = DK[v.vertex][i]+v.dir;
      if(VIS[v2]<2) Q.push( Visitor(v2,cost2,k2) );
    }
  }
  return -1;
}

int main() {
  scanf("%d %d", &n, &m);
  for(int i=0; i<n; i++) {
    int w;
    scanf("%d", &w);
    W[i+1] = w;
  }
  for(int i=0; i<m; i++) {
    int a,b,x,k;
    scanf("%d %d %d %d", &a,&b,&x,&k);
    
    int dk = 0;
    if( k>0 && W[a]>W[b] ) dk=1;
    if( k<0 && W[a]<W[b] ) dk=-1;
    //fprintf(stderr, "  %d %d %d\n",a,b,dk)

    NEXT[a].push_back(b);
    COST[a].push_back(x);
    DK  [a].push_back(dk);
    
    NEXT[b].push_back(a);
    COST[b].push_back(x);
    DK  [b].push_back(-dk);

    
    /*
    for(int r=0; r<rep; r++) {
      int aa = a + r*n;
      int bb = b + r*n;
      if( k>0 && W[aa]>W[bb] ) bb+=n;
      if( k<0 && W[aa]<W[bb] ) bb-=n;
      if( bb<n*rep && bb>=0 ) {
        NEXT[aa].push_back(bb);
        COST[aa].push_back(x);
        
        NEXT[bb].push_back(aa);
        COST[bb].push_back(x);
        //fprintf(stderr,"%d %d %d\n", aa, bb, x);
      }
    }
    */
  }
  printf("%d\n", dijkstra(1));
}
