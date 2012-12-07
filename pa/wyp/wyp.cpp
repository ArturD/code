#include<cstdio>
using namespace std;
typedef long long ll;

template<typename T>
class Rational {
  T nwd(T a, T b) { return b==0 ? a : nwd(b, a % b); }
public:
  T a,b;
  Rational():Rational(0,1) { }
  Rational(T aa, T bb) {
    //if( bb==0 ) bb=1;
    a = aa;
    b = bb;
  }

  Rational<T> operator^(const Rational<T>& o) {
    return Rational(a+o.a, b+o.b);
  }

  Rational<T> operator+(const Rational<T>& o) {
    return Rational(a*o.b+o.a*b,b*o.b);
  }
  
  bool zero() const {
    return b==0;
  }

  bool operator<(const Rational<T>& o) const {
    if(zero()||o.zero()) {
      if(zero()&&!o.zero()) return true;
      else return false;
    }
    T x = a*o.b;
    T y = b*o.a;
    return x<y;
  }
  bool operator>(const Rational<T>& o) const {
    if(zero()||o.zero()) {
      if(!zero()&&o.zero()) return true;
      else return false;
    }
    T x = a*o.b;
    T y = b*o.a;
    return x>y;
  }

  void out(FILE* out, bool fix=false) {
    T g = fix ? nwd(a,b) : 1;
    fprintf(out, "%lld/%lld\n",a/g,b/g);
  }
};
typedef Rational< long long > NUMBER;
NUMBER max(const NUMBER& a, const NUMBER& b) {
  return a<b ? b:a;
}
class Tree {
  ll *A;
  int *BESTLEN;
  ll  *BESTSUM;
  int start;
public:
  Tree(int n) {
    start = 1;
    while( start<n ) start*=2;

    int count = start*2;
    A = new ll[count];
    for(int i=0; i<count ;i++) A[i] = 0;
    BESTSUM = new ll[count];
    for(int i=0; i<count ;i++) BESTSUM[i] = 0;

    BESTLEN = new int[count]; 
    for(int i=0; i<count; i++) BESTLEN[i] = 1;
  }
  
  void set(int a, ll val) {
    int pos = a + start;
    BESTSUM[pos] = A[pos] = val;
    pos/=2;
    int len = 1;
    while ( pos>0 ) {
      A[pos] = A[pos*2]+A[pos*2+1];
      ll a1 = BESTSUM[pos*2]
        ,a2 = BESTLEN[pos*2];
      ll b1 = A[pos*2]+BESTSUM[pos*2+1]
        ,b2 = len+BESTLEN[pos*2+1];
      if( a1*b2>b1*a2 ) {
        BESTSUM[pos] = a1;
        BESTLEN[pos] = a2;
      } else {
        BESTSUM[pos] = b1;
        BESTLEN[pos] = b2;
      }
      pos /= 2;
      len *= 2;
    }
  }
  
  NUMBER walk(int a) {
    //fprintf(stderr, "---\n");
    NUMBER x = walk_up( start+a,1,NUMBER(0,0) );
    return x;
    /*
    if( a%2==1 ) return walk_up( (a+start)/2+1, NUMBER(A[a+start],1) );
    else return max( 
        NUMBER(A[a+start],1)
      , walk_up( (a+start)/2+1, NUMBER(A[ (a+start)/2]),2 ) 
    );
    */
  }

  NUMBER walk_up(int a,int mult, NUMBER oc) {
    /*
    fprintf(stderr, " walk_up %d %d ",a,mult);
    oc.out(stderr);
    */
    NUMBER c = oc;
    //if( mult > 1 ) 
    c = max( c, walk_down(a,mult,oc) );
    c = max( c, oc^NUMBER(A[a],mult) ); 
    c = max( c, oc^NUMBER(BESTSUM[a],BESTLEN[a]) );
    // c = max( c,oc^NUMBER(A[a],mult) ); ??
    if( a%2==0 ) {
       c = max( c,walk_up( a+1, mult, oc^NUMBER(A[a],mult) ) );
    } else {
      int a2 = a/2;
      if( ((a2+1)^a2)<a2 ) 
        c = max( c,walk_up( a2+1,mult*2, oc^NUMBER(A[a],mult) ) );
    }
    return c;
  }
  NUMBER walk_down(int pos,int mult, NUMBER oc) {
    /*
    fprintf(stderr, " walk_down %d %d ",pos,mult);
    oc.out(stderr);
    */ 
    
    NUMBER c = oc;
    c = max( c,oc^NUMBER(A[pos],mult) ); 
    c = max( c,oc^NUMBER(BESTSUM[pos],BESTLEN[pos]) ); 
    if( mult==1 ) {
      return max( c, oc^NUMBER(A[pos],1) );
    }
    ll a1 = BESTSUM[pos*2]
      ,a2 = BESTLEN[pos*2];
    ll b1 = A[pos*2]+BESTSUM[pos*2+1]
      ,b2 = mult+BESTLEN[pos*2+1];
    NUMBER c1 = oc^NUMBER(a1,a2);
    NUMBER c2 = oc^NUMBER(b1,b2);
    if( (c1<c2) ) {
      c = max( c,c2 );
      c = max( c, walk_down(pos*2+1,mult/2,c1) );
    } else {
      c = max( c,c1 );
      c = max( c, walk_down(pos*2  ,mult/2,oc) );
    }
    return c;
  }
};
int n,z;
int main() {
  scanf("%d%d",&n,&z);
  Tree T(n+100);
  for(int i=0; i<n; i++) {
    int a;
    scanf("%d", &a);
    T.set(i+1,a);
  }
  /*
  for(int i=0; i<n; i++) {
    NUMBER x = T.walk(i);
    x.out(stderr);
  }
  */
  for(int i=0; i<z; i++) {
    int a,b;
    char c = 'u';
    while( c!='Z' && c!='P' ) {
      scanf("%c", &c);
    }
    if( c=='Z' ) {
      scanf("%d",&a);
      //a--;
      NUMBER x = T.walk(a);
      x.out(stdout, true);
    } else if( c=='P' ) {
      scanf("%d%d",&a,&b);
      //a--;
      T.set(a,b);
      //fprintf(stderr,"P %d %d\n",a,b);
    }
  }
  return 0;
}

