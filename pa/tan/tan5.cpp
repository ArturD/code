#include <cstdio>
#include <vector>
#include <algorithm>
#include <set>
#include <cstdlib>
using namespace std;
#define ASSERT( EXPR ) { if( !(EXPR) ) { fprintf(stderr, " ASSERT FAILED %s %s %d %s\n", #EXPR, __FILE__, __LINE__, __FUNCTION__); exit(1); } }
const int maxn = 1000005;

long long N[maxn];
// int L[maxn],R[maxn];
//bool EON[maxn];
int n,k;
int sign(long long a) { return a<0?-1:( (a>0)?1:0 ); }
set<int> SN;

int snprev(int a) {
  set<int>::iterator iter = SN.find(a);
  ASSERT( iter!=SN.end() )
  if( iter==SN.begin() || iter==SN.end() ) return -1;
  return *(--iter);
}

int snnext(int a) {
  set<int>::iterator iter = SN.find(a);
  ASSERT( iter!=SN.end() )
  iter++;
  if( iter==SN.end() ) return -1;
  return *(iter);
}

struct ecmp {
  bool operator()(int a, int b) const {
    if( N[a]!=N[b] ) return N[a]>N[b];
    return a<b;
  }
};
typedef set<int, ecmp> ESET;

ESET UP, DOWN;
long long down_sum = 0;

long long etotal(int no) {
  ASSERT( N[no]<0 )
  ASSERT( no%2==1 )
  return N[snnext(no)]+N[snprev(no)]+N[no];
}
long long etotal1(int no) {
  ASSERT( N[no]<0 )
  ASSERT( no%2==1 )
  return N[snprev(no)]+N[no];
}
long long etotal2(int no) {
  ASSERT( N[no]<0 )
  ASSERT( no%2==1 )
  return N[snnext(no)]+N[no];
}
void fixup(int no);

void padd(int no) {
  //fprintf(stderr, "padd N[%d]=%lld\n", no,N[no]);
  ASSERT( N[no]>=0 )
  ASSERT( no%2==0 )
  if( UP.empty() || N[*(UP.begin())]>N[no] ) {
    DOWN.insert(no);
    down_sum += N[no];
    //fprintf(stderr, " padd<DOWN>(%d)\n", no);
  } else {
    UP.insert(no);
    fixup(no);
    //fprintf(stderr, " padd<UP>(%d)\n", no);
  }
  //fprintf(stderr, " down_sum<padd> = %lld\n", down_sum);
}

void prm(int no) {
  ASSERT( N[no]>=0 )
  ASSERT( no%2==0 )
  if( no<0 || no>=n ) return;
  ESET::iterator iter = DOWN.find(no);
  if( iter!=DOWN.end() ) { DOWN.erase(iter); down_sum -= N[no]; }
  iter = UP.find(no);
  if( iter!=UP.end() ) { UP.erase(iter); }
  //fprintf(stderr, " down_sum<prm> = %lld\n", down_sum);
}

long long peval() {
  while( DOWN.size()<(unsigned int)k && UP.size()>0 ) {
    ESET::iterator iter = UP.begin();
    DOWN.insert(*iter);
    down_sum += N[*iter];
    UP.erase(iter);
  }
  while( DOWN.size()>(unsigned int)k ) {
    ESET::iterator iter = DOWN.end();
    iter--;
    int akt = *iter;
    UP.insert(akt);
    down_sum -= N[akt];
    DOWN.erase(iter);
    fixup(akt);
  }
  //fprintf(stderr, " down_sum<peval> = %lld  (DOWN.size()==%d)\n", down_sum, DOWN.size());
  return down_sum;
}
  

ESET eset;
void erm(int no) {
  if( no<0 || no>=n ) return;
  ASSERT( N[no]<0 )
  ASSERT( no%2==1 )
  ESET::iterator iter = eset.find(no);
  if( iter!=eset.end() ) {
    eset.erase(iter);
  }
}

void eadd(int no) {
  if( no<0 || no>=n ) return;
  ASSERT( N[no]<0 )
  ASSERT( no%2==1 )
  fprintf(stderr, "try eadd %d\n", no);
  if( etotal1(no) >= 0 && etotal2(no) >= 0) {
    fprintf(stderr, "   eadd %d\n", no);
    eset.insert(no);
  }
}

void ejoin(int no) {
  fprintf(stderr, "join %d %lld\n", no, N[no]);
  ASSERT( N[no]<0 )
  ASSERT( no%2==1 )
  erm(no);
  int next = snnext(no);
  int prev = snprev(no);
  ASSERT( next!=-1 )
  ASSERT( prev!=-1 )
  int nn = snnext(next);
  int pp = snprev(prev);
  erm(nn);
  erm(pp);
  prm(next);
  prm(prev);
 
  SN.erase(next);
  SN.erase(no);
  N[prev] = N[prev] + N[no] + N[next];
  if( N[prev] == 0 ) {
    SN.erase(prev);
    if( nn!=-1 && pp!=-1 ) {
      N[nn] += N[pp];
      SN.erase(pp);
      eadd(nn);
    } else {
      if( pp!=-1 ) SN.erase(pp);
      if( nn!=-1 ) SN.erase(nn);
    }
  } else {
    padd(prev);
    eadd(nn);
    eadd(pp);
  }
  
}

void fixup(int no) {
  int n = snnext(no);
  int p = snprev(no);
  if( N[p]+N[no]+N[n]>0 ) {
    return;
  }
  if( n>=0 && p>=0 ) {
    fprintf(stderr, "fixup(%d) %lld [N[%d]=%lld, N[%d]=%lld]\n", no,N[no],n,N[n],p,N[p]);
    if( N[p]+N[no]+N[n] < 0 ) {
      erm(p);
      erm(n);
      prm(no);
      SN.erase(n);
      SN.erase(no);
      N[p] += N[no]+N[n];
      eadd(p);
    }
  }
}


long long solve(int n) {
  long long res = 0;
  for(int i=0; i<n; i++) {
    SN.insert(i);
  }
  for(int i=0; i<n; i++) {
    if( i%2==1 ) eadd(i);
    else padd(i);
  }
  peval();
  fprintf(stderr, "eset.size()==%lu\n", eset.size());
  while( eset.size()>0 ) {
    int a = *eset.begin();
    long long ev = peval();

    int ppp = 0;
    for(set<int>::iterator iter = SN.begin(); iter!=SN.end(); iter++) {
      fprintf(stderr,"N[%d]==%lld ", *iter, N[*iter]);
      if ( ppp%2==0 ) { ASSERT( N[*iter]>=0 ) }
      if ( ppp%2==1 ) { ASSERT( N[*iter]<=0 ) }
      ppp++;
    }
    /*
    for(ESET::iterator iter = eset.begin(); iter!=eset.end(); iter++) {
      fprintf(stderr, " N[%d]=%lld ", *iter, N[*iter]);
    } fprintf(stderr, "\n");
    fprintf(stderr, " join %d (ev = %lld)\n", a, ev);
    */
    ejoin(a);
    res = max(res,ev);
  }
  long long ev = peval();
  res = max(res,ev);
  return res;
}

int main() {
  int n2=0;
  scanf("%d %d", &n, &k);
  for(int i=0; i<n; i++) {
    long long a;
    scanf("%lld", &a);
    if( a<=0 && n2==0 ) continue;
    if( n2>0 && ( sign(a)==sign(N[n2-1]) || sign(a)*sign(N[n2-1])==0 ) ) {
      N[n2-1] += a;
    } else {
      N[n2++] = a;
    }
    //fprintf(stderr, " N[%d]=%lld\n", n2-1, N[n2-1]);
  }
  if( n2>0 && N[n2-1]<0 ) n2--;
  n=n2;
  /*
  if( n2>1 ) {
    int n3 = 1;
    for(int i=0; i<n2; i++) fprintf(stderr, " go %d %lld\n", n2, N[i]);
    for( int i=2; i<n2-1; i+=2 ) {
      N[n3+1] = N[i];
      N[n3+2] = N[i+1];
      n3 += 2;
      while( n3 > 1 ) {
        if( N[n3-1]<=-N[n3-2] && N[n3-1]<=-N[n3] ) {
          N[n3-2] += N[n3-1] + N[n3];
          n3-=2;
          fprintf(stderr, " reduce %d\n", n3);
        } else break;
      }
    }
    n3++;
    N[n3++] = N[n2-1];
    n=n3;
  }
  */
  //for(int i=0; i<n; i++) fprintf(stderr, " go %d %lld\n", n, N[i]);
  for(int i=1; i<n; i++) { 
    //fprintf(stderr, "%d %lld %lld\n",i, N[i-1], N[i]);
    ASSERT( N[i]*N[i-1]!=0 )
    ASSERT( sign(N[i])!=sign(N[i-1]) ) 
  }
  long long result = 0;
  if( n>0 ) result = solve(n);
  printf("%lld\n", result);
  return 0;  
}
