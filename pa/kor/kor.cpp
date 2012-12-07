#include<cstdio>
#include<algorithm>
using namespace std;

typedef long long ll;
const int maxn = 1000000;
ll inf = 1000000000000000ll;
ll A[maxn];
ll DP[2][maxn];
int n;
ll solve() {
  DP[0][0] = A[0];
  for(int j=1; j<n; j++) {
    DP[j%2][j] = A[j];
    for(int i=j-1; i>-1; i--) {
      DP[j%2][i] =  A[i]   - DP[j%2][i+1];
      if( DP[j%2][i] < A[j]-DP[(j-1)%2][i] ) {
        DP[j%2][i] = A[j] - DP[(j-1)%2][i];
      }
      if(DP[j%2][i] < A[i] + A[j] - DP[(j-1)%2][i+1]) {
        DP[j%2][i] = A[i] + A[j] - DP[(j-1)%2][i+1];
      }
    }
  }
  return DP[(n-1)%2][0];
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
