#include <iostream>
#include <cstdio>
#include <vector>
#include <map>
#include <queue>
#include <cstring>
using namespace std;

typedef pair<int,int> PII;
typedef pair<int,PII> PIII;

const int maxn = 20005;
const int maxm = 200005;
const int maxk = 22;

int n,m,k;
int sp[maxk][maxk];
int spend[maxk];
unsigned char odw[maxn];
int bc[maxn];
vector<int> next[maxn];
vector<int> cost[maxn];


void dijkstra(int start) {
  priority_queue<PII> q;
//  q.reserve(1000000);
  q.push(PII(0, start));
  memset(odw, 0, sizeof(char)*n);
  memset(bc, -1, sizeof(int)*n);
  while(!q.empty()) {
    PII akt = q.top();
    q.pop();
    int aktcost = -akt.first;
    int aktv = akt.second;
    if(odw[aktv]) continue;
    odw[aktv] = 1;
    if(aktv < 21) sp[start][aktv] = aktcost;
    if(aktv == n-1) {
      spend[start] = aktcost;
    }
    for(int i=0; i<next[aktv].size(); i++) {
      int nn = next[aktv][i];
      if(odw[nn] || nn == aktv) continue;
      if(bc[nn] == -1 || bc[nn] > aktcost + cost[aktv][i]) {
        bc[nn] = aktcost + cost[aktv][i];
        q.push(PII(-aktcost - cost[aktv][i], nn));
      }
    }
  }
}


char odw2[(1<<20)][maxk];
//int best2[(1<<20)][maxk];
int require[maxk+5];
//int cangoc[1<<20];
int can_go(int v) {
//  if(cangoc[v]) return cangoc[v]-1;
  int ret =  0;
  for(int i=0; i<k; i++) {
    int v2 = v | (1<<i);
    if(v2 == v) continue;
    if((require[i+1] & v) == require[i+1]) {
      ret |= (1<<i);
    }
  }
  //cangoc[v] = ret+1;
  //if(v == 31) cerr << v<< " : " << ret;
  //cerr << "can go " << v << " : " << ret << endl;
  return ret;
}

int newton[21][21];
int _newton(int n, int k) {
  long long x = 1;
  if(k < n-k) return _newton(n,n-k);
  for(int i=k+1; i<=n; i++) x*=i;
  for(int i=1; i<=n-k; i++) x/=i;
  return (int) x;
}

int bits(int mask) {
  int ret = 0;
  for(;mask; mask = mask & (mask-1)) ret++;
  return ret;
}

int _index[1<<20];
int Index(int mask) {
  return _index[mask];
}

int _Index(int mask) {
  int ret = 0;
  int b = bits(mask);
  for(int i=21; i>=0; i--) {
    if(mask >> i == 0) continue;
    mask -= 1<< i;
    if(i<b) break;
    ret += newton[i][b];
    b--;
  }
  return ret;
}


const int max_subset = 185000;
int _s1[max_subset*20], _s2[max_subset*20];
//char was1[max_subset*20], was2[max_subset*20];

int Index(int mask, int last) {
  return max_subset*last + Index(mask);
}

bool can_go2(int mask, int v) {
  v++;
  //cerr << "    mask  "<< hex << mask<< ":"<< require[v]  << " : "<< dec << v << endl;
  if((require[v] & mask) == require[v]) return true;
  return false;
}

long long SP() {
  if(k == 0) return spend[0];
  int* prev=_s1, *akt=_s2;
  for(int i=0;i<k;i++) {
    int v = 1<<i;
    if(can_go(0) & v) {
      prev[Index(v,i)] = sp[0][i+1];
    } else prev[Index(v,i)] =2000000000;
  }

  for(int i=0; i<k-1; i++) {
    for(int m=0; m<(1<<k); m++){
      if(bits(m) != i+2) continue;
      for(int j=0; j<k; j++) {
        if((m & (1<<j))== 0) continue;
        int best = 2000000000;
        // (m, j)
        for(int ii=0; ii<k; ii++) {
          if(ii == j) continue;
          if(((m-(1<<j)) & (1<<ii))== 0) continue;
          if(!can_go2(m-(1<<j),j)) continue;
          int cc = prev[Index(m-(1<<j),ii)]+sp[ii+1][j+1];
          //cerr << "  prev " << hex << (m-(1<<j)) << " : "<< dec << ii <<" = " << cc<< endl;
          best = min(cc,best);
        }
        akt[Index(m, j)] = (int) best;

        //cerr << "akt " << hex << m << " : "<< dec << j <<" = " << best<< endl;
      }
    }
    swap(prev,akt);
  }

  int best2 = 2000000000;
  for(int i=0; i<k; i++) {
    best2 = min(best2, prev[Index((1<<(k))-1, i)]+spend[i+1]);
  }
  return best2;
}

long long dijkstra2() {
  priority_queue<PIII> q;
  for(int i=0;i<k;i++) {
    int v = 1<<i;
    if(can_go(0) & v) 
      q.push(PIII(-sp[0][i+1],PII(v, i+1)));
  }
  if(k==0) return spend[0];
  long long best = 1000000000000000ll;
  while(!q.empty()) {
    PIII akt = q.top();
    q.pop();
    long long aktcost = -akt.first;
    int aktm = akt.second.first;
    int aktv = akt.second.second;
    //cerr << aktv << " : " << aktm <<  "    :  " << aktcost << endl;
    if(aktm == (1<<(k))-1) { 
      best = min( aktcost + spend[aktv], best ) ; 
      //cerr << aktm << " :: " << aktv << " = "<< best << endl; 
    }

    if(odw2[aktm][aktv]) continue;
    odw2[aktm][aktv] = 1;

    for(int i=1; i<k+1; i++) {
      if( i== aktv) continue;
      int nn = aktm | (1<<(i-1));
      int cc = aktcost+sp[aktv][i];
      if(!odw2[nn][i] && /*(best2[nn][i] == 0 || best2[nn][i] > cc) &&*/ ((can_go(aktm) & nn) !=0)) {
        q.push(PIII(-cc,PII(nn, i)));
        //best2[nn][i] =cc;
      }
    }
  }
  return best;
}

int main() {
  for(int i=1; i<21;i++)
    for(int j=0; j<=i; j++) newton[i][j] = _newton(i,j);
  for(int i=0; i<(1<<20); i++) _index[i] = _Index(i);

  scanf("%d%d%d", &n,&m,&k);
  for(int i=0; i<m; i++) {
    int a,b,c;
    scanf("%d%d%d", &a,&b,&c);
    a--;
    b--;
    next[a].push_back(b);
    cost[a].push_back(c);
    
    next[b].push_back(a);
    cost[b].push_back(c);
  }

  for(int i =0; i<k+2; i++) {
    dijkstra(i);
  }
  for(int i=0; i<n; i++) {
    next[i].clear();
    cost[i].clear();
  }
  /*
  for(int i=0; i<k+1; i++) {
    cerr << i << " : ";
    for(int j=0; j<k+1; j++) {
      cerr << sp[i][j] <<" ";
    }
    cerr << endl;
  }
  */
  int o;
  scanf("%d", &o);
  for(int i=0; i<o; i++) {
    int a,b;
    scanf("%d%d", &a,&b); a--; b--;
    require[b] |= 1<<(a-1);
  }
  for(int i=0; i<n;i++) {
    next[i].clear();
    cost[i].clear();
  }
  long long out = SP();
  printf("%lld\n", out);
  return 0;
}
