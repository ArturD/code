#include <cstdio>
#include <vector>
#include <algorithm>
#include <set>
#include <cstdlib>
using namespace std;
#define ASSERT( EXPR ) { if( !(EXPR) ) { fprintf(stderr, " ASSERT FAILED %s %s %d %s\n", #EXPR, __FILE__, __LINE__, __FUNCTION__); exit(1); } }
const int maxn = 10005;
int n,k;
long long N[maxn];
long long A[101][maxn]  // last used
        , B[101][maxn]; // last not used

int sign(long long a) { return a<0?-1:( (a>0)?1:0 ); }
long long solve() {
  long long res = 0;
  for(int ik = 1; ik<=k; ik++) {
    for(int in = 0; in<n; in++) {
      A[ik][in] = max(0ll,N[in]);
      if( in>0 ) {
        A[ik][in] = max(A[ik][in-1]+N[in], A[ik][in]);
        B[ik][in] = max(A[ik][in-1], B[ik][in-1]);
        A[ik][in] = max(B[ik-1][in-1]+N[in], A[ik][in]);
      }
      fprintf(stderr, "%d %d -> %lld %lld\n", ik, in, A[ik][in], B[ik][in]);
      res = max(res, A[ik][in]);
    }
  }
  return res;
}

int main() {
  int n2=0;
  scanf("%d %d", &n, &k);
  for(int i=0; i<n; i++) {
    long long a;
    scanf("%lld", &a);
    if( a<=0 && n2==0 ) continue;
    if( n2>0 && ( sign(a)==sign(N[n2-1]) || sign(a)*sign(N[n2-1])==0 ) ) {
      N[n2-1] += a;
    } else {
      N[n2++] = a;
    }
  }
  if( n2>0 && N[n2-1]<0 ) n2--;
  n=n2;
  
  for(int i=1; i<n; i++) { 
    ASSERT( N[i]*N[i-1]!=0 )
    ASSERT( sign(N[i])!=sign(N[i-1]) ) 
  }
  
  long long result = 0;
  if( n>0 ) result = solve();
  printf("%lld\n", result);
  return 0;  
}
