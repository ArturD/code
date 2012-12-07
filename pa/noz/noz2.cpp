#include<cstdio>
#include<set>
#include<vector>
#include<algorithm>
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

    //if( X[next(i,n)]<X[i] ) S.erase(next(i,n));
    //if( X[prev(i,n)]<X[i] ) S.erase(prev(i,n));
    SET::iterator iter = S.lower_bound(i);
    if( iter!=S.end() && *iter==i ) {
      SET::iterator iter2 = iter++;
      S.erase(iter2);
    }
    fprintf(stderr, " -- test %d %d \n", i, *iter);
    if( iter!=S.end() && X[*iter]==X[i] && !adj(i,*iter,n) ) {
      NEXT[i].push_back(*iter);
      NEXT[*iter].push_back(i);
      fprintf(stderr, " - \n");
    }
    if( S.size()>0 && iter!=S.begin() ) {
      iter--;
      fprintf(stderr, "test %d %d \n", i, *iter);
      if( iter!=S.end() && X[*iter]==X[i] && !adj(i,*iter,n) ) {
        NEXT[i].push_back(*iter);
        NEXT[*iter].push_back(i);
        fprintf(stderr, " + \n");
      }
    }
    if( X[next(i,n)]>X[i] ) S.insert(next(i,n));
    if( X[prev(i,n)]>X[i] ) S.insert(prev(i,n));
  }
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
  search(X, Y, n2);
  search(Y, X, n2);
  for(int i=0; i<n2; i++) {
    for(int j=0; j<NEXT[i].size(); j++) {
      fprintf(stderr, "[%d %d][%d %d]\n", X[i],Y[i], X[NEXT[i][j]],Y[NEXT[i][j]]);
    }
  }
  return 0;
}
