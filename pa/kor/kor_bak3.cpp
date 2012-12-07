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
  for(int j=0; j<n; j++) {
    for(int i=j-1; i>-1; i--) {
      DP[i][j] =  A[i]   - DP[i+1][j];
      if( DP[i][j] < A[j]-DP[i][j-1] ) {
        DP[i][j] = A[j] - DP[i][j-1];
      }
      if(DP[i][j] < A[i] + A[j] - DP[i+1][j-1]) {
        DP[i][j] = A[i] + A[j] - DP[i+1][j-1];
      }
    }
  }
  return DP[0][n-1];
}

int main() {
  scanf("%d", &n);
  ll sum = 0;
  for(int i=0; i<n; i++) {
    scanf("%lld", A+i);
    sum+=A[i];
  }
  ll sol = solve();
  ll a = (sum+sol)/2;
  ll b = sum-a;
  printf("%lld %lld\n",a,b);
  return 0;
}
