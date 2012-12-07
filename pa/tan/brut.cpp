#include<iostream>

using namespace std;

typedef long long ll;
int n,k;
const int maxn = 1000005;
int DAYS[maxn];


ll solve(int* A, int n, int k) {
  if( k==0 ) return 0;
  if( n==0 ) return 0;
  ll result = 0;
  for(int i=0; i<n; i++) {
    ll sum = 0;
    for(int j=i; j<n; j++) {
      sum += A[j];
      result = max(result, 
        sum + solve(A+j+1, n-j-1,k-1));
    }
  }
  return result;
}

int main() {
  cin >> n >> k;
  for(int i=0; i<n; i++) {
    cin >> DAYS[i];
  }

  cout << solve(DAYS, n, k) << endl;
}
