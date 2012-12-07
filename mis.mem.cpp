#include<iostream>

using namespace std;

#define REP(i,n) for(int i=0; i<(n); i++)

const int maxn = 39;
int A[maxn][maxn][maxn][maxn][4][4];

bool check(int a, int b, int c) {
  int A = 0, B=0, X1=0, X2=0;
  
  if(a%2 == 0) X1++;
  else X2++;
  if(a/2 == 0) A++;
  else B++;

  if(b%2 == 0) X1++;
  else X2++;
  if(b/2 == 0) A++;
  else B++;

  if(c%2 == 0) X1++;
  else X2++;
  if(c/2 == 0) A++;
  else B++;

  if(A == 3 || B == 3 || X1 == 3 || X2 == 3) return false;
  return true;
}

int main() {
  int a,b,c,d;
  cin >> a >> b >> c >> d;

  int sum = a+b+c+d;
  if(sum == 0) cout << "1" << endl;
  else if(sum == 1) cout << "1" << endl;
  else if(sum == 2) {
    if(a == 2 || b == 2 || c == 2 || d == 2) cout << "2" << endl;
    else cout << "1" << endl;
  } else {
    REP(x, 4) REP(y,4) {
          int ii=0, jj=0, kk=0, ll=0;
          if(x == 0) ii++;
          if(y == 0) ii++;
          
          if(x == 1) jj++;
          if(y == 1) jj++;
          
          if(x == 2) kk++;
          if(y == 2) kk++;
          
          if(x == 3) ll++;
          if(y == 3) ll++;
          if(ii<=a && jj<=b && kk<=c && ll<=d) {
            A[ii][jj][kk][ll][x][y] += 1;
          }
    }

    REP(i, a+1) {
    REP(j, b+1) {
    REP(k, c+1) {
    REP(l, d+1) {
      int sum2 = i+j+k+l;
      if(sum2 < 2) continue;
      REP(x, 4) REP(y,4) {
        A[i][j][k][l][x][y] %= 1000000;
        //cerr<< i <<","<<j<<","<<k<<","<<l<<";"<<x<<","<<y<<" = " << A[i][j][k][l][x][y]<<endl;
        if(i+1 <= a && check(x,y,0)) A[i+1][j][k][l][y][0] += A[i][j][k][l][x][y];
        if(j+1 <= b && check(x,y,1)) A[i][j+1][k][l][y][1] += A[i][j][k][l][x][y];
        if(k+1 <= c && check(x,y,2)) A[i][j][k+1][l][y][2] += A[i][j][k][l][x][y];
        if(l+1 <= d && check(x,y,3)) A[i][j][k][l+1][y][3] += A[i][j][k][l][x][y];
      }
    }
    }
    }
    }
    int result = 0;
    REP(x, 4) REP(y,4) {
      result += A[a][b][c][d][x][y];
    }
    cout << (result % 1000000) << endl;
  }

  return 0;
}
