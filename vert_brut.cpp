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

int main() {
  int t;
  scanf("%d", &t);
  while(t--) {
    int n;
    scanf("%d", &n);
    for(int i=0; i<n; i++) scanf("%d", IN+i);
    for(int i=0; i<n; i++) P[i] = i;
    double total = 0;
    int nn = 0;
    do {
      //print(P, n);
      double v = eval(IN, P, n);
      total += v;
      nn ++;
    } while(next_permutation(P, P+n));
    printf("%.2lf\n", total/nn);
  }
  return 0;
}
