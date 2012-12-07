#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>

using namespace std;

class Tree {
  int _start;
  int *_S, *_MAX;
public:
  Tree(int n) {
    _start = 1;
    while( _start<n ) _start *= 2;
    _S   = new int[_start*2];
    _MAX = new int[_start*2];
    memset(  _S, 0, 2*_start*sizeof(int));
    memset(_MAX, 0, 2*_start*sizeof(int));
  }
  void _update( int a ) {
    if( a==0 ) return;
    if( a>=_start ) {
      _MAX[a] = _S[a];
    } else {
      _MAX[a] = max( _MAX[2*a], _MAX[2*a+1] ) + _S[a];
    }
    _update(a/2);
  }

  void add(int a, int b, int v) {
    a+=_start;
    b+=_start;
    while(a<=b) {
      if( a%2==1 ) {
        _S[a] += v;
        _update( a++ );
      }
      if( b%2==0 ) {
        _S[b] += v;
        _update( b-- );
      }
      a/=2;
      b/=2;
    }
  }
  int _get(int a) {
    if(a==0) return 0;
    return _S[a] + _get(a/2);
  }
  int get(int a) {
    return _get( a+_start );
  }
  int get_max() {
    return _MAX[1];
  }

};

#define assert( EXPR ) if( !(EXPR) ) fprintf(stderr, " ASSERT ERROR %s\n", #EXPR)

void test() {
 for(int i=0; i<500; i++) {
  Tree t(8+i);
  t.add(1+i,1+i,1);
  assert( t.get(0+i)==0 );
  assert( t.get(1+i)==1 );
  assert( t.get(2+i)==0 );
  
  assert( t.get_max()==1 );
  
  t.add(2+i,2+i,1);
  assert( t.get(0+i)==0 );
  assert( t.get(1+i)==1 );
  assert( t.get(2+i)==1 );
  assert( t.get(3+i)==0 );
  
  assert( t.get_max()==1 );
  
  t.add(0+i,3+i,-1);
  assert( t.get(0+i)==-1 );
  assert( t.get(1+i)==0 );
  assert( t.get(2+i)==0 );
  assert( t.get(3+i)==-1 );
  
  assert( t.get_max()==0 );
  
  t.add(0+i,7+i,2);
  assert( t.get(0+i)==1 );
  assert( t.get(1+i)==2 );
  assert( t.get(2+i)==2 );
  assert( t.get(3+i)==1 );
  assert( t.get(7+i)==2 );
  
  assert( t.get_max()==2 );
  
  t.add(1+i,1+i,-1);
  assert( t.get_max()==2 );
  t.add(2+i,2+i,-1);
  assert( t.get_max()==2 );
  t.add(4+i,7+i,-1);
  assert( t.get_max()==1 );
 }
}
typedef pair<int,int> PII;

int main() {
  test();
  vector<PII> P;
  int n;
  scanf("%d", &n);
  for(int i=0; i<n; i++) {
    int a,b;
    scanf("%d %d", &a, &b);
    if( a==b ) continue;
    P.push_back( PII(a,b) );
    P.push_back( PII(b,a) );
  }
  n = P.size();

  if( P.size()==0 ) {
    printf("0\n");
  } else {
    for(int rep=0; rep<2; rep++) {
      if(rep) for(int i=0; i<P.size(); i++) swap( P[i].first, P[i].second );
      sort(P.begin(), P.end());
      int prev = -1, akt = -1;
      for(int i=0; i<P.size(); i++) {
        if( P[i].first==prev ) P[i].first = akt;
        else { prev = P[i].first; P[i].first = ++akt; }
      }
    }
    Tree T(n);
    int count = 0;
    int best = 0;
    for(int i=0; i<P.size(); i++) {
      //fprintf(stderr, " %d -- %d\n", P[i].first, P[i].second);
      if( P[i].first<P[i].second ) {
        count++;
        T.add( P[i].first, P[i].second-1, -1 );
      } else {
        count--;
        T.add( P[i].second, P[i].first-1, +1 );
      }
      if( i==n-1 || P[i].first!=P[i+1].first ) {
        best = max( best, T.get_max()+count );
        //fprintf(stderr, "          %d -> %d+%d\n", P[i].first, T.get_max(),count);
        T.add( P[i].first, P[i].first, count );
      }
    }
    printf("%d\n", best);
  }
  
  return 0;
}
