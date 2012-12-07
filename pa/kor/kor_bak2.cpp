#include<cstdio>
#include<algorithm>
using namespace std;

typedef long long ll;
const int maxn = 1000;
ll inf = 1000000000000000ll;
ll A[maxn];
ll DP[maxn][maxn];
int n;
ll solve() {
  for(int i=0; i<n; i++) { 
    for(int j=0; j<n; j++) {
      if( j==i ) DP[i][j] = A[i];
      else DP[i][j] = 0;
    }
  }
  for(int d=1; d<n; d++) {
    for(int i=0; i+d<n; i++) {
      DP[i][i+d] =  A[i]   - DP[i+1][i+d];
      if( DP[i][i+d] < A[i+d]-DP[i][i+d-1] ) {
        DP[i][i+d] = A[i+d] - DP[i][i+d-1];
      }
      if(DP[i][i+d] < A[i] + A[i+d] - DP[i+1][i+d-1]) {
        DP[i][i+d] = A[i] + A[i+d] - DP[i+1][i+d-1];
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
  printf("%lld\n", solve());
  return 0;
}
