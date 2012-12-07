#include<cstdio>
#include<cstdlib>
using namespace std;

#define ASSERT( EXPR ) { if( !(EXPR) ) { fprintf(stderr, " ASSERT FAILED %s %s %d %s\n", #EXPR, __FILE__, __LINE__, __FUNCTION__); exit(1); } }

const int maxd = 7000000;
int POS[maxd];
int TYPE[maxd];
int lastdir = 7;
int level = 0;

int DR3[7] = {-1,-1,0,0,0,1,0};
int DL3[7] = {-1,0,1,1,1,0,-1};
int NEWPOS3 [7] = {-1,-1,1,2,3,-1,-1};
int LASTDIR3[7] = {-1, -1, 6,7,7,-1,-1};
int DFIELD3[7] = {0, 0, 0, 0, 0, 0, -1};

int DR4[7] = {0,-1,0,0,0,0,1};
int DL4[7] = {-1,0,1,1,1,1,0};
int NEWPOS4[7] = {-1,-1,1,2,3,4,-1};
int LASTDIR4[7] = {-1, -1, 6,7,7,7,-1};
int DFIELD4[7] = {-1,0,0,0,0,0,0};
int field = 0;

int getType(int level) {
  if( TYPE[level] == 7 ) return 4;
  if( TYPE[level] == 4 ) {
    ASSERT( POS[level]<=3 )
    ASSERT( POS[level]>=1 )
    if( POS[level]==2 || POS[level]==3 ) return 4;
    return 3;
  }
  if( TYPE[level] == 3 ) {
    ASSERT( POS[level]<=2 )
    ASSERT( POS[level]>=1 )
    if( POS[level]==2  ) return 4;
    return 3;
  }
  ASSERT( false )
}

void outPos() {
  for(int i=0; i<=level; i++) {
    fprintf(stderr, " [%d/%d]",POS[i],TYPE[i]);
  }
  fprintf(stderr, " t = %d", getType(level));
  fprintf(stderr, " f = %d", field);
  fprintf(stderr, " dir = %d", lastdir);
  fprintf(stderr,"\n");
}


void fixPos(int level) {
  //fprintf(stderr, "fix level %d\n", level);
  if( level<0 ) return;
  if( level==0 ) {
    POS[level] = (POS[level]+7)%7;
    return;
  }
  while( POS[level] < 1 ) {
    POS[level-1] --;
    //if( level < ::level )
    field--;
    fixPos(level-1);
    POS[level] += getType(level-1)-1;
    TYPE[level] = getType(level-1);
  }
  while( POS[level] >= TYPE[level] ) {
    int oldType = TYPE[level];
    POS[level-1] ++;
    //if( level < ::level )
    field++;
    fixPos(level-1);
    POS[level] -= oldType-1;
    TYPE[level] = getType(level-1);
  }
}

void go(int dir) {
  int newDir = (lastdir+dir) % 7;
  
  int type    = getType(level);
  int dright  = type==3 ? DR3[newDir] : DR4[newDir];
  int dlevel  = type==3 ? DL3[newDir] : DL4[newDir];
  int newPos  = type==3 ? NEWPOS3[newDir] : NEWPOS4[newDir];
  int newlDir = type==3 ? LASTDIR3[newDir] : LASTDIR4[newDir];
  int dfield  = type==3 ? DFIELD3[newDir] : DFIELD4[newDir];
  if( dlevel==1 ) {
    POS[++level] = newPos;
    TYPE[level] = type;
    lastdir = newlDir;
    //field += dfield;
    //fprintf(stderr, " newlDir %d\n", newlDir);
    fixPos(level);
  } else if( dlevel==-1 ) {
    lastdir = POS[level]+1;
    level--;
    if( level<0 )return;
    if( type==3 && newDir==6 ) lastdir=2;
    //if( type==3 && newDir==6 ) field--;
    //if( type==3 && newDir==1 ) POS[level]--;
    if( type==3 && newDir==0 ) POS[level]--;
    field += dfield;
    //if( dright!=1 ) field--;
    fixPos(level);
    if( type==3 && newDir==0 ) { 
      if( getType(level)==3 ) lastdir=4;
      if( getType(level)==4 ) lastdir=5;
    }
  } else {
    POS[level] += dright;
    //field += dright;
    fixPos(level);
    if( dright==1 ) lastdir = 1;
    else {
      if( getType(level) == 4 ) lastdir = 6;
      else lastdir = 5;
    }
  }
}

int main() {
  int n =0;
  scanf("%d", &n);
  TYPE[0] = 7;
  outPos();  
  for(int i=0; i<n-1; i++) {
    int dir;
    scanf("%d", &dir);
    fprintf(stderr, " go %d\n", dir);
    go(dir);
    if( level==-1 ) break; // just in case
    outPos();  
  }
  printf("%d\n", abs(field));
  return 0;
}
