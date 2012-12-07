#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 105;
char STR[maxn];
int DP[maxn][maxn][3][3];
int other(int a, int b) {
  if(a!=0 && b!=0) return 0;
  if(a!=1 && b!=1) return 1;
  return 2;
}
int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    scanf("%s", STR);
    int n = strlen(STR);
    for(int i=0; i<n ;i++) STR[i] -= 'a';
    for(int s=1; s<n+1 ;s++) {
      for(int i=0; i<n-s+1 ;i++) {
        if(s==1) {
          for(int a=0; a<3; a++)
            for(int b=0; b<3; b++)
              DP[i][i][a][b] = (a==b && b==STR[i]) ? 1 : maxn;
        } else {
          for(int a=0; a<3 ;a++)
            for(int b=0; b<3 ;b++) {
              int best = maxn;
              for(int split=1; split<s ;split++) {
                for(int c=0; c<3 ;c++) 
                  for(int d=0; d<3 ;d++) { 
                    best = min(best, DP[i][i+split-1][a][c] + DP[i+split][i+s-1][d][b]);
                    if(c!=d) {
                      if(DP[i+split][i+s-1][d][d]                 != 1)
                        if(c!=a && d!=a && DP[i][i+split-1][c][c] == 1)
                          best = min(best, DP[i][i+split-1][c][c] + DP[i+split][i+s-1][d][b]-1);
                      if(c!=b && d!=b && DP[i+split][i+s-1][d][d] == 1)
                        if(DP[i+split][i+s-1][d][d]               != 1)
                          best = min(best, DP[i][i+split-1][a][c] + DP[i+split][i+s-1][d][d]-1);
                      if(c!=a && d!=a && DP[i][i+split-1][c][c] == 1)
                        if(c!=b && d!=b && DP[i+split][i+s-1][d][d] == 1)
                          best = min(best, 1);

                      if(DP[i][i+split-1][a][c]   != 1 && 
                         DP[i+split][i+s-1][d][b] != 1 )
                        best = min(best, DP[i][i+split-1][a][c] + DP[i+split][i+s-1][d][b]-1);
                    }
                  }
              }
              if(best != maxn) {
              //cerr << i << " " << s << " " << a << " : " << b<< endl;
              //cerr << "  " << best << endl;
              }
              DP[i][i+s-1][a][b] = best;
            }
        }
      }
    }
    int result = maxn;
    for(int a=0; a<3 ;a++)
      for(int b=0; b<3 ;b++) {
        result = min(result, DP[0][n-1][a][b]);
      }

    printf("%d\n",result);
  }
  return 0;
}
