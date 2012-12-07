#include<cstdio>
#include<algorithm>
#include<functional>
using namespace std;

const int maxn = 500005;
const int inf  = 2000000000;
int X1[maxn], Y1[maxn], X2[maxn], Y2[maxn];
int n;
int XY[maxn],YX[maxn],XY2[maxn],YX2[maxn];

template< class TCMP=less<int> >
struct cmp {
  int *A, *B;
  TCMP _cmp;
  cmp(int* a, int* b, TCMP cmp=TCMP()):A(a),B(b),_cmp(cmp) {}
  inline bool operator()(int a, int b) const {
    if(A[a] != A[b]) return _cmp(A[a],A[b]);
    return _cmp(B[a],B[b]);
  }
};

long long field(int x, int y, int x2, int y2) {
  if( x<x2 && y<y2 ) {
    long long ret = (long long)(x2-x)*(y2-y);
    //fprintf(stderr, "  field: %d %d %d %d %lld\n",x,y,x2,y2, ret);
    return ret;
  }
  return 0;
}
long long score(int* A, int n) {
  int x1=0, x2=inf, y1=0, y2=inf;
  for(int i=0; i<n; i++) {
    x1 = max(x1,X1[A[i]]);
    y1 = max(y1,Y1[A[i]]);
    x2 = min(x2,X2[A[i]]);
    y2 = min(y2,Y2[A[i]]);
  }
  return field(x1,y1,x2,y2);
}
long long solve(int* A, int n) {
  long long sum = 0;
  long long all = score(A, n);
  for(int i=0; i<n; i++) {
    swap(A[i],A[n-1]);
    sum += score(A, n-1) - all;
    swap(A[i],A[n-1]);
  }
  return sum + all;
}

int main() {
  scanf("%d", &n);
  for(int i=0; i<n; i++) {
    scanf("%d%d%d%d", X1+i, Y1+i, X2+i, Y2+i);
  }
  const int _t = 400;
  int t = min(n,_t);
  int * ARR[4] = {XY,YX,XY2,YX2};
  for(int a=0; a<4; a++) 
    for(int i=0; i<n; i++) ARR[a][i] = i;
  nth_element( XY, XY+t-1, XY+n, cmp< greater<int> >(X1,Y1));
  nth_element( YX, XY+t-1, YX+n, cmp< greater<int> >(Y1,X1));
  nth_element(XY2,XY2+t-1,XY2+n, cmp<    less<int> >(X2,Y2));
  nth_element(YX2,XY2+t-1,YX2+n, cmp<    less<int> >(Y2,X2));
  int ii = 0;
  int A[_t*4];
  for(int a=0; a<4; a++)
    for(int b=0; b<t; b++) A[ii++] = ARR[a][b];
  sort(A,A+ii);
  ii = unique(A,A+ii) - A;
  for(int i=0; i<ii; i++) fprintf(stderr," %d", A[i]); fprintf(stderr,"\n");
  printf("%lld\n", solve(A,ii));
  return 0;
}

