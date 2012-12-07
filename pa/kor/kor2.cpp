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
      else DP[i][j] = 0;
    }
  }
  for(int d=1; d<n; d++) {
    for(int i=0; i+d<n; i++) {
      if( i>start || i+d<start ) continue;
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
  return DP[0][n-1];
}

int main() {
  scanf("%d", &n);
  for(int i=0; i<n; i++) {
    scanf("%lld", A+i);
  }
  for(int i=0; i<n; i++) {
    printf("%lld\n", solve(i));
  }
  return 0;
}
