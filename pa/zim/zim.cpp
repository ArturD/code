#include<cstdio>
#include<vector>
#include<stack>

using namespace std;

const int maxn = 500005;
vector<int> NEXT[maxn], P[maxn];
int PREV[maxn], RES[maxn], BUFF[maxn], VIS[maxn];
int n;

long long solve(int a) {
  stack<int> S;
  S.push(a);
  int best = 0;
  while( !S.empty() ) {
    int cur = S.top(); S.pop();
    //fprintf(stderr," -- %d -- \n", cur);
    if( cur>0 ) {
      if( VIS[cur] ) continue;
      VIS[cur] = 1;
      //fprintf(stderr," VIS[%d]=1\n", cur);
      S.push( -cur );
      for(int i=0; i<NEXT[cur].size(); i++) {
        if( !VIS[NEXT[cur][i]] ) {
          //PREV[NEXT[cur][i]] = cur;
          S.push( NEXT[cur][i] );
        }
      }
    } else {
      cur = -cur;
      if( VIS[cur]!=1 ) { fprintf(stderr, "!\n"); }
      VIS[cur] = 2;
      //fprintf(stderr," VIS[%d]=2 (%d)\n", cur, VIS[cur]);
      int cost = 0;
      int b1, b2;
      b1 = b2 = 0;
      for(int i=0; i<NEXT[cur].size(); i++) {
        int next = NEXT[cur][i];
        int   np = P   [cur][i];
        if( VIS[next]==2 ) {
          int co = RES[next] + ((np%2)?1:-1);
          //fprintf(stderr, "  %d->%d  RES[next]=%d", cur, next,RES[next]);
          //fprintf(stderr, "  co=%d  np=%d\n", co,np);
          if( b1<co ) { b2=b1; b1=co; }
          else if ( b2<co ) { b2=co; }
        }
      }
      //fprintf(stderr, " %d %d %d\n", cur, b1, b2);
      best = max(best, b1+b2);
      RES[cur] = b1;
    }
  }
  long long res = 0;
  for(int i=1; i<=n; i++) {
    for(int j=0; j<NEXT[i].size(); j++) {
      res += (P[i][j]+1)/2*2;
    }
  }
  //fprintf(stderr,"%lld %d\n",res,best);
  return res/2-best;
}

int main() {
  scanf("%d", &n);
  
  for(int i=0; i<n-1; i++) {
    int a,b,p;
    scanf("%d%d%d", &a,&b,&p);
    
    NEXT[a].push_back(b);
    P   [a].push_back(p);

    NEXT[b].push_back(a);
    P   [b].push_back(p);
  }
  printf("%lld\n",solve(1));
  return 0;
}
