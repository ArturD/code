#include<algorithm>
#include<cstdio>

using namespace std;

const int maxn = 101;
int P[maxn], IN[maxn];

void print(int *A, int n) {
  for(int i=0; i<n; i++) printf("%d ", A[i]);
  printf("\n");
}

double eval(int* A, int* P, int n) {
  int sum = 0;
  //printf("--");
  //print(A,n);
  //print(P,n);
  for(int i=0; i<n; i++) {
    int x = 1;
    for(int j=1; i-j>=0; j++) {
      if(A[P[i]] <= A[P[i-j]]) break;
      x++;
    }
    //printf("%d ", x);
    sum += x;
  }
  //printf("\n");
  return sum;
}

//      podz wyk   pozy
int  TAB[maxn][maxn][maxn];
int TAB2[maxn][maxn];
int main() {
  int t;
  scanf("%d", &t);
  while(t--) {
    int n;
    scanf("%d", &n);
    for(int i=0; i<n; i++) scanf("%d", IN+i);
    for(int i=0; i<n; i++) P[i] = i;
    sort(IN, IN+n);
    int prev = -1;
    for(int i=1; i<=n; i++) {
      for(int wyk=0; wyk<=i; wyk++) {
        for(int poz=0; poz<=wyk; poz++) {
          if(IN[i] != prev) {
            TAB[i][wyk][poz] = TAB2[i-1][poz] + TAB2[i-1][i-poz-1] + poz+1;
          } else {
            TAB[i][wyk][poz] = 0;
            for(int p2=0; p2<poz; p2++) {
              TAB
            }
          }
        }
        TAB2[i][wyk] = 0;
        for(int poz=0; poz<=wyk; poz++) {
          TAB2[i][wyk] += TAB[i][wyk][poz];
        }
      }
      prev = IN[i];
    }
    printf("%.2lf\n", total/nn);
  }
  return 0;
}
