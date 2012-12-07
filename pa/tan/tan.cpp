#include <cstdio>
#include <vector>
#include <algorithm>
#include <queue>
#include <cstdlib>
using namespace std;
const int maxn = 1000005;
const long long inf = 1000000000000000000ll;
long long N[maxn];
int n,k;
int sign(long long a) { return a<0?-1:( (a>0)?1:0 ); }

template<typename NUMBER, typename CMP>
class Tree {
  NUMBER *A;
  int *IND;
  CMP cmp;
  int start;
public:
  Tree(int n, NUMBER initial = 0) {
    start = 1;
    while( start<n ) start*=2;

    int count = start*2;
    A = new NUMBER[count];
    for(int i=0; i<count ;i++) A[i] = initial;
    IND = new int[count]; // fill ?
    for(int i=0; i<start; i++) {
      int pos = i+start;
      while( pos>0 ) {
        IND[pos] = i;
        pos/=2;
      }
    }
  }
  
  void set(int a, NUMBER val) {
    int pos = a + start;
    while ( pos>0 ) {
      if( cmp(A[pos], val) ) { 
        A[pos] = val;
        IND[pos] = a;
      }
      pos/=2;
    }
  }

  NUMBER get(int a) { return A[a+start]; }
  
  NUMBER get(int a, int b) {
    int ind = getind(a,b);
    return get(ind);
  }

  int getind(int a, int b) {
    //fprintf(stderr, " getind \n");
    int ind = a;
    a += start;
    b += start;
    NUMBER res = A[a];
    while( a<=b ) {
      if ( a%2==1 ) {
        if( cmp(res,A[a]) ) {
          res = A[a];
          ind = IND[a];
          //fprintf(stderr, " a=%d, IND[a]=%d, A[a]=%lld\n", a,IND[a],A[a]);
        }
        a++;
      }
      if ( b%2==0 ) {
        if( cmp(res,A[b]) ) {
          res = A[b];
          ind = IND[b];
          //fprintf(stderr, " b=%d, IND[b]=%d, A[b]=%lld\n", b,IND[b],A[b]);
        }
        b--;
      }
      a/=2;
      b/=2;
    }
    return ind;
  }
};
class SequenceIndex {
  long long *SUM, *N;
  int *LOW,*HIGH;
  Tree< long long, greater<long long> > *MIN;
  Tree< long long,    less<long long> > *MAX;
  
  int n;

  void precompute() {
    SUM[0] = LOW[0] = HIGH[0] = 0;
    for(int i=1; i<n; i++) {
      SUM[i] = SUM[i-1] + N[i];
      MIN->set( i, SUM[i] );
    }
    for(int i=1; i<n; i++) {
      HIGH[i] = i-1;
      LOW[i]  = i;
      while( HIGH[i]>0 && SUM[HIGH[i]]<SUM[i] ) {
        if( SUM[LOW[HIGH[i]]-1] < SUM[LOW[i]-1] ) 
          LOW[i] = LOW[HIGH[i]];
        HIGH[i] = HIGH[HIGH[i]];
      }
      MAX->set( i, SUM[i]-SUM[LOW[i]-1] );
    }
    /*
    for(int i=1; i<n; i++) { fprintf(stderr, " %d",   LOW[i]); }
    fprintf(stderr,"\n");
    for(int i=1; i<n; i++) { fprintf(stderr, " %d",   HIGH[i]); }
    fprintf(stderr,"\n");
    for(int i=1; i<n; i++) { fprintf(stderr, " %lld", MAX->get(i)); }
    fprintf(stderr,"\n---\n");
    */
  }
public:
  SequenceIndex(long long *N, int n) {
    this->n = n;
    this->N = new long long[n];
    for(int i=0; i<n; i++) this->N[i] = N[i];
    SUM = new long long[n];
    HIGH = new int[n];
    LOW  = new int[n];
    MIN = new Tree< long long, greater<long long> >(n,inf);
    MAX = new Tree< long long,    less<long long> >(n,-inf);
    
    precompute();
  }

  pair<int, int> query_fast(int a, int b) {
    int x = MAX->getind(a,b);
    //fprintf(stderr," q %d,%d x=%d \n", a,b,x);
    //fprintf(stderr,"  HIGH[x]=%d LOW[x]=%d \n", HIGH[x], LOW[x]);
    if ( LOW[x]<a ) {
      int y = MAX->getind( x+1,b );
      int z = MIN->getind( a-1,x-1 ) + 1;
      fprintf(stderr," q %d,%d y=%d z=%d\n", a,b,y,z);
      if ( SUM[x]-SUM[z-1]<MAX->get(y) ) {
        return make_pair( LOW[y],y );
      } else {
        return make_pair( z,x );
      }
    } else {
      return make_pair( LOW[x],x );
    }
  }
  long long eval(pair<int, int> interval) {
    return SUM[interval.second] - SUM[interval.first-1];
  }
  pair<int,int> query_slow(int a,int b) {
    pair<int,int> best;
    long long ev = -inf;
    for(int i=a; i<=b; i++) {
      for(int j=i; j<=b; j++) {
        pair<int,int> cur = make_pair(i,j);
        long long cure = eval(cur);
        if( cure>ev ) {
          ev = cure;
          best = cur;
        }
      }
    }
    return best;
  }
  
  pair<int,int> query(int a,int b) {
    /*
    pair<int,int> pii = query_slow(a,b);
    pair<int,int> pii2 = query_fast(a,b);
    if( eval(pii) != eval(pii2) ) {
      fprintf(stderr, " query %d %d\n", a,b);
      fprintf(stderr, " %d %d %d %d\n", pii.first, pii.second, pii2.first,pii2.second);
      fprintf(stderr, " %lld %lld\n", eval(pii), eval(pii2));
      exit(1);
    }
    */
    return query_fast(a,b);
  }
};

struct Interval {
  pair<int,int> inner,outer;
  long long split_cost;
  bool pos;
  Interval(pair<int,int> o, pair<int,int> i, long long cost, bool pn) {
    inner = i;
    outer = o;
    split_cost = cost;
    pos = pn;
  }
  bool operator<(const Interval& o) const {
    return split_cost < o.split_cost;
  }
};

long long solve() {
  for(int i=n; i>0; i--) N[i] = N[i-1];
  N[0] = 0;
  n++;

  SequenceIndex pos(N,n);
  for(int i=0; i<n; i++) N[i] = -N[i];
  SequenceIndex neg(N,n);
  
  priority_queue<Interval> Q;
  pair<int,int> start = pos.query(1,n-1);
  Interval first(make_pair(1,n-1), start, pos.eval(start), true);
  Q.push(first);
  long long res = 0;
  for(int i=0; i<k; i++) {
    Interval cur = Q.top(); Q.pop();
    SequenceIndex *index=&pos, *index2=&neg;
    if( cur.pos ) { index=&neg; index2=&pos; }
    if( cur.split_cost <= 0 ) break;
    res += cur.split_cost;
    //fprintf(stderr, " (%d,(%d,%d),%d)", cur.outer.first
     // ,cur.inner.first,cur.inner.second,cur.outer.second);
    //fprintf(stderr, " %d %lld\n", (int)cur.pos, cur.split_cost);
    
    pair<int,int> i = index->query(cur.inner.first, cur.inner.second);
    Interval mid( cur.inner, i, index->eval(i), !cur.pos );
    Q.push( mid );
    
    pair<int, int> left  = make_pair(cur.outer.first, cur.inner.first-1)
                  ,right = make_pair(cur.inner.second+1, cur.outer.second);
    if( left.first<=left.second ) {
      pair<int,int> i = index2->query(left.first, left.second);
      Interval l( left, i, index2->eval(i), cur.pos );
      Q.push( l );
    }
    
    if( right.first<=right.second ) {
      pair<int,int> i = index2->query(right.first, right.second);
      Interval r( right, i, index2->eval(i), cur.pos );
      Q.push( r );
    }
  }
  return res;
}

int main() {
  int n2=0;
  scanf("%d %d", &n, &k);
  for(int i=0; i<n; i++) {
    long long a;
    scanf("%lld", &a);
    N[i] = a;
    /*
    if( a<=0 && n2==0 ) continue;
    if( n2>0 && ( sign(a)==sign(N[n2-1]) || sign(a)*sign(N[n2-1])==0 ) ) {
      N[n2-1] += a;
    } else {
      N[n2++] = a;
    }
    */
    //fprintf(stderr, " N[%d]=%lld\n", n2-1, N[n2-1]);
  }
 /* 
  if( n2>0 && N[n2-1]<0 ) n2--;
  n=n2;
  */
  long long result = 0;
  if( n>0 ) result = solve();
  printf("%lld\n", result);
  return 0;  
}
