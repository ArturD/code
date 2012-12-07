#include<cstdio>
#include<algorithm>

using namespace std;

const int maxn = 40005;
bool A[maxn];
int B[2][maxn*2];
int N[2];

int main() {
  int n,m;
  scanf("%d %d", &n, &m);
  for(int j=0; j<n; j++) {
    B[0][j] = j+1;
  }
  B[0][n] = -1;
  N[0] = n;
  for(int i=0; i<m; i++) {
    for(int j=0; j<n; j++) {
      int x;
      scanf("%d", &x);
      if(j<n/2) A[x] = 1;
      else A[x] = 0;
    }
    int countdown = n;
    N[(i+1)%2] = 0;
    for(int j=0; j<N[i%2]; j++) {
      if(B[i%2][j] == -1) fprintf(stderr, "!");
      bool any = false;
      //fprintf(stderr,"|");
      for(int k=j; B[i%2][k]!=-1; k++) {
        if(A[B[i%2][k]]) {
          //fprintf(stderr,"%d ", B[i%2][k]);
          any = true;
          B[(i+1)%2][N[(i+1)%2]++] = B[i%2][k];
        }
      }
      //fprintf(stderr,"|");
      if(any) B[(i+1)%2][N[(i+1)%2]++] = -1;
      any = false;
      for(int k=j; B[i%2][k]!=-1; k++) {
        if(!A[B[i%2][k]]) {
          //fprintf(stderr,"%d ", B[i%2][k]);
          any = true;
          B[(i+1)%2][N[(i+1)%2]++] = B[i%2][k];
        }
      }
      if(any) B[(i+1)%2][N[(i+1)%2]++] = -1;
      for(; B[i%2][j]!=-1; j++) {}
    }
      //fprintf(stderr,"\n");
  }
  bool tak = true;
  int count = 0;
  for(int j=0; j<N[m%2]; j++) {
    //fprintf(stderr,"%d ", B[m%2][j]);
    if ( B[m%2][j]==-1 ) count = 0;
    else count++;
    if(count > 1) tak = false;
  }
  printf("%s\n", tak?"TAK":"NIE");
  return 0;
}
