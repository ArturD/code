#include <cstdio>

using namespace std;
const int maxn = 3001;
int T[maxn][maxn];
int removed[maxn];
int main() {
  int n,m;
  scanf("%d%d", &n, &m);
  for(int i=0;i<m;i++) {
    int a,b;
    scanf("%d%d",&a,&b);
    a--; b--;
    T[a][b] = 1;
  }
  for(int i=0; i<n;i++) {
    for(int j=i+1; j<n;j++) {
      if (T[i][j] == 0 && !removed[i] && !removed[j] ) {
        removed[i] = 1;
        removed[j] = 1;
//        fprintf(stderr, "remove  %d, %d\n", i, j);
      }
    }
  }
  int w = 0;
  for(int i=0; i<n; i++) {
    if(removed[i] == 0) {
      printf("%d ", i+1);
      w++;
      if(w == n/3) break;
    }
  }
  printf("\n");
  return 0;
}
