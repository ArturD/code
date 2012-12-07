#include <cstdio>
#include <vector>
#include <algorithm>
#include <set>
#include <cstdlib>
using namespace std;
#define ASSERT( EXPR ) { if( !(EXPR) ) { fprintf(stderr, " ASSERT FAILED %s %s %d %s\n", #EXPR, __FILE__, __LINE__, __FUNCTION__); exit(1); } }
const int maxn = 1000005;

long long N[maxn];
int L[maxn],R[maxn];
bool EON[maxn];
int n,k;
int sign(long long a) { return a<0?-1:( (a>0)?1:0 ); }

struct ecmp {
  bool operator()(int a, int b) const {
    if( N[a]!=N[b] ) return N[a]>N[b];
    return a<b;
  }
};
typedef set<int, ecmp> ESET;

ESET UP, DOWN;
long long down_sum = 0;
void padd(int no) {
  fprintf(stderr, "padd %d\n", no);
  ASSERT( N[no]>=0 )
  ASSERT( no%2==0 )
  if( UP.empty() || N[*(UP.begin())]>N[no] ) {
    DOWN.insert(no);
    down_sum += N[no];
    fprintf(stderr, " padd<DOWN>(%d)\n", no);
  } else {
    UP.insert(no);
    fprintf(stderr, " padd<UP>(%d)\n", no);
  }
  fprintf(stderr, " down_sum<padd> = %lld\n", down_sum);
}

void prm(int no) {
  ASSERT( N[no]>=0 )
  ASSERT( no%2==0 )
  if( no<0 || no>=n ) return;
  ESET::iterator iter = DOWN.find(no);
  if( iter!=DOWN.end() ) { DOWN.erase(iter); down_sum -= N[no]; }
  iter = UP.find(no);
  if( iter!=UP.end() ) { UP.erase(iter); }
  //fprintf(stderr, " down_sum<prm> = %lld\n", down_sum);
}

long long peval() {
  while( DOWN.size()<(unsigned int)k && UP.size()>0 ) {
    ESET::iterator iter = UP.begin();
    DOWN.insert(*iter);
    down_sum += N[*iter];
    UP.erase(iter);
  }
  while( DOWN.size()>(unsigned int)k ) {
    ESET::iterator iter = DOWN.end();
    iter--;
    UP.insert(*iter);
    down_sum -= N[*iter];
    DOWN.erase(iter);
  }
  //fprintf(stderr, " down_sum<peval> = %lld  (DOWN.size()==%d)\n", down_sum, DOWN.size());
  return down_sum;
}
  
long long etotal(int no) {
  ASSERT( N[no]<0 )
  ASSERT( no%2==1 )
  return N[no-1]+N[no+1]+N[no];
}

ESET eset;
void erm(int no) {
  if( no<0 || no>n ) return;
  ESET::iterator iter = eset.find(no);
  if( iter!=eset.end() ) {
    EON[no] = false;
    eset.erase(iter);
  }
}

void eadd(int no) {
  if( no<0 || no>=n ) return;
  if( etotal(no) >= 0 ) {
    eset.insert(no);
  }
}

void ejoin(int no) {
  fprintf(stderr, "join %d %lld\n", no, N[no]);
  ASSERT( N[no]<0 )
  ASSERT( no%2==1 )
  erm(no);
  erm(L[no-1]-1);
  erm(R[no+1]+1);
  int l = L[no-1];
  int r = R[no+1];
  prm(l);
  prm(r);
  
  N[r] = N[l] = N[no]+N[no-1]+N[no+1];
  L[l] = l; R[l] = r;
  L[r] = l; R[l] = r;

  eadd(l-1);
  eadd(r+1);
  padd(l);
}


long long solve(int n) {
  long long res = 0;
  for(int i=0; i<n; i++) {
    L[i] = R[i] = i;
  }
  for(int i=0; i<n; i++) {
    if( i%2==1 ) eadd(i);
    else padd(i);
  }
  while( eset.size()>0 ) {
    //int a = *(--eset.end());
    int a = *eset.begin();
    long long ev = peval();
    /*
    for(ESET::iterator iter = eset.begin(); iter!=eset.end(); iter++) {
      fprintf(stderr, " N[%d]=%lld ", *iter, N[*iter]);
    } fprintf(stderr, "\n");
    fprintf(stderr, " join %d (ev = %lld)\n", a, ev);
    */
    ejoin(a);
    res = max(res,ev);
  }
  long long ev = peval();
  res = max(res,ev);
  return res;
}

int main() {
  int n2=0;
  scanf("%d %d", &n, &k);
  for(int i=0; i<n; i++) {
    long long a;
    scanf("%lld", &a);
    if( a<0 && n2==0 ) continue;
    if( n2>0 && ( sign(a)==sign(N[n2-1]) || sign(a)*sign(N[n2-1])==0 ) ) {
      N[n2-1] += a;
    } else {
      N[n2++] = a;
    }
    //fprintf(stderr, " N[%d]=%lld\n", n2-1, N[n2-1]);
  }
  if( n2>0 && N[n2-1]<0 ) n2--;
  n=n2;
  if( n2>1 ) {
    int n3 = 1;
    for(int i=0; i<n2; i++) fprintf(stderr, " go %d %lld\n", n2, N[i]);
    for( int i=2; i<n2-1; i+=2 ) {
      N[n3+1] = N[i];
      N[n3+2] = N[i+1];
      n3 += 2;
      while( n3 > 1 ) {
        if( N[n3-1]<=-N[n3-2] && N[n3-1]<=-N[n3] ) {
          N[n3-2] += N[n3-1] + N[n3];
          n3-=2;
          fprintf(stderr, " reduce %d\n", n3);
        } else break;
      }
    }
    n3++;
    N[n3++] = N[n2-1];
    n=n3;
  }
  for(int i=0; i<n; i++) fprintf(stderr, " go %d %lld\n", n, N[i]);
  for(int i=1; i<n; i++) { 
    //fprintf(stderr, "%d %lld %lld\n",i, N[i-1], N[i]);
    ASSERT( N[i]*N[i-1]!=0 )
    ASSERT( sign(N[i])!=sign(N[i-1]) ) 
  }
  long long result = 0;
  if( n>0 ) result = solve(n);
  printf("%lld\n", result);
  return 0;  
}
