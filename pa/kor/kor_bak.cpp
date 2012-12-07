#include<cstdio>
#include<algorithm>
using namespace std;

typedef long long ll;
const int maxn = 1000;
ll inf = 1000000000000000ll;
ll A[maxn];
ll A2[maxn];
ll DP[maxn][maxn];
ll DP2[maxn][maxn];
int n;
ll solve(int start) {
  for(int i=0; i<n; i++) { 
    for(int j=0; j<n; j++) {
      if( j==i ) DP[i][j] = A[i];
      //else if( i==j ) DP[i][j] = -inf;
      else DP[i][j] = 0;
      if( i==start) DP[i][j] = 0;
    }
  }
  for(int d=1; d<n; d++) {
    for(int i=0; i+d<n; i++) {
      //fprintf(stderr, " %d %d\n", i, i+d);
      DP[i][i+d] =  A[i]   - DP[i+1][i+d];
      DP2[i][i+d] = 1;
      if( DP[i][i+d] < A[i+d]-DP[i][i+d-1] ) {
        DP[i][i+d] = A[i+d] - DP[i][i+d-1];
        DP2[i][i+d] =2;
      }
      if(DP[i][i+d] < A[i] + A[i+d] - DP[i+1][i+d-1]) {
        DP[i][i+d] = A[i] + A[i+d] - DP[i+1][i+d-1];
        DP2[i][i+d] = 3;
      }
    }
  }
  /*
  for(int i=0; i<n; i++) {
    for(int j=0; j<n; j++) {
      if( DP[i][j]!=-inf ) fprintf(stderr, " %4lld", DP[i][j]);
      else fprintf(stderr, " -");
    }
    fprintf(stderr, " \n");
  }
  int a=0,b=n-1;
  int color = 1;
  while( b-a > 0) {
    DP2[a][b] += 128; 
    if( DP2[a][b]&1 ) A2[a++] = color;
    if( DP2[a][b]&2 ) A2[b--] = color;
    color ^= 3;
  }
  for(int i=0; i<n; i++) {
    for(int j=0; j<n; j++) {
      if( DP2[i][j]!=-inf ) fprintf(stderr, " %3lld", DP2[i][j]/128);
      else fprintf(stderr, " -");
    }
    fprintf(stderr, " \n");
  }
  for(int i=0; i<n; i++) {
    fprintf(stderr, " %lld", A2[i]);
  }
    fprintf(stderr, " \n");
  */
  return DP[0][n-1];
}

int main() {
  scanf("%d", &n);
  for(int i=0; i<n; i++) {
    scanf("%lld", A+i);
  }
  printf("%lld\n", solve());
  return 0;
}
