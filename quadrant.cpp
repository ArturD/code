#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

class Tree {
  int *A,*B,*C,*D;
  int *X,*Y;
  int start;

public:
  Tree(int n) {
    start = 1;
    while( start<n ) start *= 2;
    
    int ** arrays[6] = {&A,&B,&C,&D,&X,&Y};
    for(int i=0; i<6; i++) { 
      *(arrays[i]) = new int[start*2];
      memset(*(arrays[i]),0,start*2*sizeof(int));
    }
    for(int i=0; i<n; i++) {
      int x = start+i;
      for(int x=start+i; x>0 ;x/=2) {
        A[x]++;
      }
    }
  }

  void change_count(int pos, int a, int b, int c, int d, bool swp=false) {
    if( pos==0 ) return;
    if(swp) {
      if( X[pos]%2 ) { std::swap(a,d); std::swap(c,b); }
      if( Y[pos]%2 ) { std::swap(a,b); std::swap(c,d); }
    }
    A[pos] += a;
    B[pos] += b;
    C[pos] += c;
    D[pos] += d;
    change_count(pos/2,a,b,c,d, true);
  }

  void print(int* tab) {
    for(int s=start; s>0; s/=2) {
      for(int i=s; i<s*2; i++) {
        fprintf(stderr, "%d ", tab[i]);
      }
      fprintf(stderr, "\n");
    }
  }

  void swap(char axis, int a, int b) {
    a+=start; b+=start;
    int mult = 1;
    while( a<=b ) {
      if( a%2==1 ) {
        if(axis == 'X') {
          X[a]++;
          change_count(a, D[a]-A[a], C[a]-B[a], B[a]-C[a], A[a]-D[a]);
          //change_count(a, A[a]-D[a], B[a]-C[a], C[a]-B[a], D[a]-A[a]);
        }
        if(axis == 'Y') {
          Y[a]++;
          change_count(a, B[a]-A[a], A[a]-B[a], D[a]-C[a], C[a]-D[a]);
          //change_count(a, A[a]-B[a], B[a]-A[a], C[a]-D[a], D[a]-C[a]);
        }
        a++;
      }
      if( b%2==0 ) {
        if(axis == 'X') {
          X[b]++;
          change_count(b, D[b]-A[b], C[b]-B[b], B[b]-C[b], A[b]-D[b]);
          //change_count(b, A[b]-D[b], B[b]-C[b], C[b]-B[b], D[b]-A[b]);
        }
        if(axis == 'Y') {
          Y[b]++;
          change_count(b, B[b]-A[b], A[b]-B[b], D[b]-C[b], C[b]-D[b]);
          //change_count(b, A[b]-B[b], B[b]-A[b], C[b]-D[b], D[b]-C[b]);
        }
        b--;
      }
      a/=2;
      b/=2;
      mult *= 2;
    }
    /*
    fprintf(stderr, " --- \n");
    print(A);
    print(B);
    print(C);
    print(D);
    fprintf(stderr, " --- \n");
    */
  }

  inline int xtab(int tab) {
    return (~tab)&3;
  }
  inline int ytab(int tab) {
    return tab^1;
  }

  int read_one(int tab, int pos) {
    int* tabs[4] = {A,B,C,D};
    //fprintf(stderr," - read_one(%d,%d) = %d\n",tab, pos, tabs[tab][pos]);
    int x=0, y=0;
    int p = pos/2;
    for(int p=pos/2; p>0 ;p/=2) {
      x+=X[p];
      y+=Y[p];
    }
    if(x%2) tab = xtab(tab);
    if(y%2) tab = ytab(tab);
    //fprintf(stderr," + read_one(%d,%d) = %d\n",tab, pos, tabs[tab][pos]);
    return tabs[tab][pos];
  }

  int read(int tab, int a, int b) {
    a+=start; b+=start;
    int mult = 1;
    int result = 0;
    while( a<=b ) {
      if( a%2==1 ) {
        result += read_one(tab, a);
        a++;
      }
      if( b%2==0 ) {
        result += read_one(tab, b);
        b--;
      }
      a/=2;
      b/=2;
      mult *= 2;
    }
    return result;
  }
};

int main() {
  int n;
  scanf("%d", &n);
  Tree T(n);
  for(int i=0; i<n; i++) {
    int x,y;
    scanf("%d %d",&x,&y);
    if(x<0) T.swap('Y',i,i);
    if(y<0) T.swap('X',i,i);
  }
  int q;
  scanf("%d", &q);
  //fprintf(stderr,"q=%d\n", q);
  for(int i=0; i<q; i++) {
    char op;
    int a,b;
    while((op=getchar()) != EOF) if(op=='Y'||op=='X'||op=='C') break;
    scanf("%d %d", &a, &b);
    if( op=='X' ) T.swap('X',a-1,b-1);
    else if( op=='Y' ) T.swap('Y',a-1,b-1);
    else if( op=='C' ) {
      for(int i=0; i<4; i++) printf("%d ", T.read(i,a-1,b-1));
      printf("\n");
    } else {
      fprintf(stderr, "wrong op: %c (%d)\n", op, op);
    }
  }
  return 0;
}
