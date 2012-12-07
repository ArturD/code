#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
const int maxn = 1000005;

int N[maxn];
int L[maxn],R[maxn];

int sign(int a) { return a<0?-1:( (a>0)?1:0 ); }

template<typename T, CMP>
struct Queue {
  long long VAL[maxn];
  bool ON[maxn];
  priority_queue<int, vector<T>, CMP> _q;
  int _size;
  long long _sum;

  Queue(int id) {
    _sum = _size = 0;
  }

  void push(int pos, long long val) { // push or update
    if( ON[pos] ) {
      if( VAL[pos]==val ) return;
      _sum += val - VAL[pos];
      VAL[pos] = 
    }

  }
  
  T pop() {
  }
};

Queue< PLI, greater<PLI> > UP;
Queue< PLI,    less<PLI> > DOWN;

#define ASSERT( EXPR ) if( !(EXPR) ) fprintf(stderr, " ASSERT FAILED %s", #EXPR)

void upate(int a) {
  ASSERT( N[a]<0 );
  
}

long long solve(int n) {
  for(int i=0; i<n; i++) {
    L[i] = R[i] = i;
  }
  for(int i=0; i<n; i++) {
    if( i%2==1 ) update(i);
  }
}

int main() {
  int n,n2=0,k;
  scanf("%d", &n);
  for(int i=0; i<n; i++) {
    int a;
    scanf("%d", &a);
    if( a<0 && n2==0 ) continue;
    if( n2>0 && ( sign(a)!=sign(N[n2-1]) || sign(a)*sign(N[n2-1])==0 ) ) {
      N[n2-1] += a;
    } else {
      N[n2++] = a;
    }
  }
  if( n2>0 && N[n2-1]<0 ) n2--;
  n=n2;

  for(int i=1; i<n; i++) { if( N[i]*N[i-1]==0 || sign(N[i])==sign(N[i-1]) ) fprintf(stderr,"!\n"); }
  
  long long result = 0;
  if( n>0 ) result = solve(n);
  printf("%lld", result);
  return 0;  
}
