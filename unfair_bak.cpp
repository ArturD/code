#include<cstdio>
#include<vector>
#include<cstring>
#include<iostream>

using namespace std;
const int maxn = 15;
typedef long long ll;
ll COST[2][2][1<<maxn];
int XOR[2][2][1<<maxn];
int N[maxn];
int n;
ll top;

inline void relax(int sh, int m, int xo, ll cost) {
    int good = (xo & (1<<sh)) ? 0 : 1;
    int v = COST[sh&1][good][m];
    if(v == -1 || v > cost) {
      COST[sh&1][good][m] = cost;
      XOR[sh&1][good][m] = xo;
      if(good && m) {
        top = min(top, cost + xo);
      }
    }
}

inline int BOOL(int a) {
  return a ? 1 : 0;
}

ll solve() {
  top = 1ll << 50;
  int n1 = n-1;
  int cur = 0;
  for(int i=0; i<n ;i++) cur ^= N[i];
  if(cur == 0) return 0;
  int sh = 31;
  while(true) {
    // cerr << (1<<n) << endl;
    bool br = false;
    for(int i=0; i<n ;i++) if(N[i] & (1<<sh)) br = true;
    if(br) break;
    sh --;
  }
  sh++;
  /*
  for(int m=0; m<=(m<<n1) ;m++) {
    int l = cur;
    ll cost = 0;
    for(int i=0; i<n ;i++) if(m&(1<<i)) l ^= N[i];
    for(int i=0; i<n ;i++) if(m&(1<<i)) cost += (1<<sh) - N[i];
    relax(sh, m, l, cost, BOOL(l & (1<<sh)));
  }
  */
  memset(COST[(sh+1)%2][0], -1, sizeof(ll) * (1<<n));
  memset(COST[(sh+1)%2][1], -1, sizeof(ll) * (1<<n));
  COST[(sh+1)%2][1][0] = 0;
  XOR [(sh+1)%2][1][0] = cur;

  for(; sh>=0 ;sh--) {
    int pow = (1<<sh);
    memset(COST[sh%2][0], -1, sizeof(ll) * (1<<n));
    memset(COST[sh%2][1], -1, sizeof(ll) * (1<<n));
    //cerr << " -- " << (1<<n) << " - -";
    //for(int i=0; i<(1<<n);i++)cerr << COST[sh%2][0][i] << " ";
    //cerr << endl;
    for(int m=0; m<(1<<n) ;m++) {
      if(COST[(sh+1)%2][1][m] != -1) 
        relax(sh, m, XOR[(sh+1)%2][1][m], COST[(sh+1)%2][1][m]);
      
      //int tmpxor0 = XOR[sh%2][0][m];
      
      if(COST[sh%2][0][m] != -1 && m!=0) 
        relax(sh, m, XOR[sh%2][0][m] ^ pow, COST[sh%2][0][m] + pow);
      if(COST[sh%2][1][m] != -1 && m!=0) 
        relax(sh, m, XOR[sh%2][1][m] ^ pow, COST[sh%2][1][m] + pow);
      
      int tmpxor0 = XOR[sh&1][0][m];
      int tmpxor1 = XOR[sh&1][1][m];
      ll tmpcost0 = COST[sh&1][0][m];
      ll tmpcost1 = COST[sh&1][1][m];
      
      for(int i=0; i<n ;i++) if((m&(1<<i)) == 0) if((N[i] & pow) == 0) {
        //cerr << " add " << i << endl;
        int nn = N[i] & ((1<<(sh+1))-1);
        //cerr << " nn = " << nn << endl;
        int dx = (1<<sh) ^ nn;
        int dc = (1<<sh) - nn;
        if(COST[sh%2][0][m] != -1) 
          relax(sh, m|(1<<i), tmpxor0 ^ dx, tmpcost0 + dc);
        if(COST[sh%2][1][m] != -1) 
          relax(sh, m|(1<<i), tmpxor1 ^ dx, tmpcost1 + dc);
      }
    }
  }
  return top;
}

int main() {
  int t;
  scanf("%d",&t);
  while(t--) {
    scanf("%d",&n);
    for(int i=0; i<n ; i++) {
      scanf("%d", N+i);
    }
    ll sol =  solve() ; 
    printf("%lld\n", sol);
  }
  return 0;
}
