#include<cstdio>
#include<queue>
#include<vector>
#include<algorithm>
#include<set>
#include<cstdlib>
using namespace std;

const int maxn = 100005;
int X[maxn], Y[maxn];
vector<int> NEXT[maxn];

bool line(int a, int b, int c) {
  if( X[a]==X[b] && X[a]==X[c] ) return true;
  if( Y[a]==Y[b] && Y[a]==Y[c] ) return true;
  return false;
}

struct cmp {
  int *X, *Y;
  cmp(int *x, int *y):X(x),Y(y) {}
  bool operator()(int a, int b) const {
    if( X[a]!=X[b] ) return X[a]<X[b];
    return Y[a]<Y[b];
  }
};

int I[maxn];

int next(int i,int n) { return (i+1)  %n; }
int prev(int i,int n) { return (i+n-1)%n; }
int adj(int a, int b, int n) { return a==next(b,n) || a==prev(b,n); }

void search(int* X, int* Y, int n) {
  cmp cmpx(X,Y), cmpy(Y,X);
  typedef set<int,cmp> SET;
  SET S(cmpy);
  for(int i=0; i<n; i++) I[i] = i;
  sort(I, I+n, cmpx);
  for(int _i=0; _i<n; _i++) {
    int i = I[_i];
    //fprintf(stderr, " [%d,%d]\n",X[i],Y[i]);
    
    SET::iterator iter = S.lower_bound(i);
    if( iter!=S.end() && *iter==i ) {
      //fprintf(stderr, " erase [%d,%d]\n",X[*iter],Y[*iter]);
      SET::iterator iter2 = iter++;
      S.erase(iter2);
    }
    
    if( _i+1<n && X[I[_i+1]]==X[i] && !adj(i,I[_i+1],n) ) {
      if( !(iter!=S.end() && Y[*iter]<Y[I[_i+1]]) ) {
        NEXT[I[_i+1]].push_back(i);
        NEXT[i].push_back(I[_i+1]);
      }
      //fprintf(stderr," [%d %d] [%d %d]\n", X[i],Y[i], X[I[_i+1]],Y[I[_i+1]]);
    }
    if( X[next(i,n)]>X[i] ) S.insert(next(i,n));
    if( X[prev(i,n)]>X[i] ) S.insert(prev(i,n));
  }
}
long long field(int n) {
  long long res = 0;
  for(int i=0; i<n; i++) {
    res += (long long)(X[i]-X[prev(i,n)]) * Y[i];
  }
  return res;
}

long long cross_product(int c,int a, int b) { 
  return ((long long) (X[a]-X[c])*(Y[b]-Y[c]))
    -((long long) (Y[a]-Y[c])*(X[b]-X[c])); 
}
bool left(int a, int b, int c) { return cross_product(a,b,c)<0; }
int VIS[maxn];
void print(int cur,int n) {
  fprintf(stderr, " [%d,%d]",X[prev(cur,n)],Y[prev(cur,n)]);
  fprintf(stderr, " [%d,%d]",X[cur],Y[cur]);
  fprintf(stderr, " [%d,%d]",X[next(cur,n)],Y[next(cur,n)]);
  fprintf(stderr, " \n");
}
int count(int n) {
  int cuts = 0;
  for(int i=0; i<n; i++) {
    if( !left(prev(i,n),i,next(i,n)) ) {
      if (VIS[i]) continue;
      int len = 0;
      queue<int> Q;
      Q.push(i);
      while(!Q.empty()) {
        int cur = Q.front(); Q.pop();
        if( VIS[cur] ) continue;
        VIS[cur] = 1;
        if( left(prev(cur,n),cur,next(cur,n)) ) {
          continue; // !!
        }
        len++;
        for(int j=0; j<NEXT[cur].size(); j++) {
           Q.push(NEXT[cur][j]);
        }
      }
      cuts += (len+1)/2;
    }
  }
  return cuts;
}

int main() {
  int n,n2=0;
  scanf("%d", &n);
  for(int i=0; i<n; i++) {
    scanf("%d%d",X+n2,Y+n2);
    if( n2<2 || !line(n2-1,n2-2,n2) )  n2++;
    else fprintf(stderr, " skip %d %d\n", X[n2],Y[n2]);
  }
  n=n2;
  if( field(n)<0 ) { reverse(X,X+n); reverse(Y,Y+n); }
  search(X, Y, n);
  search(Y, X, n);
  /*
  for(int i=0; i<n2; i++) {
    for(int j=0; j<NEXT[i].size(); j++) {
      fprintf(stderr, "[%d %d][%d %d]\n", X[i],Y[i], X[NEXT[i][j]],Y[NEXT[i][j]]);
    }
  }
  */
  printf("%d\n",count(n));
  return 0;
}
