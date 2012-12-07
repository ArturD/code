#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
#include<cmath>
#include<cstring>
using namespace std;

bool test(vector<int>& Q) {
  int n = Q.size();
  for(int d=1; d<=n/2; d++) {
    for(int i=0; i<n-2*d; i++) {
      if(Q[i+d] - Q[i] == Q[i+2*d] - Q[i+d]) return false;
    }
  }
  vector<int> Q2(Q);
  sort(Q2.begin(), Q2.end());
  for(int i=0; i<Q.size() ;i++) if(Q2[i] != i) return false; 
  return true;
}
void print(vector<int>& Q) {
  cout << "puts \"" << Q.size() <<"\"" << endl;
  cout << "puts \"";
  for(int i=0; i<Q.size(); i++) cout << Q[i] << " ";
  cout <<"\"";
  cout << endl;
}
int gcd(int a, int b)
{
    while( 1 )
    {
        a = a % b;
                if( a == 0 )
                        return b;
                b = b % a;

        if( b == 0 )
                        return a;
    }
}

template<class T>
bool random_permutation(T b, T e) {
  int s = e - b;
  for(int i=0; i<s-1; i++) {
    int o = rand() % (s-i-1) + i+1;
    swap(*(b+i),*(b+o));
  }
  return true;
}

const int maxf = 1100;
int DP[maxf*2], DN[maxf*2];
int DX[maxf*2], DY[maxf*2];
vector<int> Q;
int best = 0;

int n;
int COUNT[maxf][maxf];
int MASK [maxf][maxf];
bool add(int x, int y) {
  int dp = DP[y-x+n];
  int dn = DN[y+x];
  if(dp || dn || MASK[x][y]) {  
    return false;
  }
  ++DP[y-x+n];
  ++DN[y+x];
  for(int i=0; i<x; i++) {
    int dx = x-i;
    int dy = y-Q[i];
    int dd = gcd(abs(dx),abs(dy));
    dx /= dd;
    dy /= dd;
    int xx = x+dx;
    int yy = y+dy;
    while(xx >= 0 && yy >= 0 && xx < n && yy < n) {
      MASK[xx][yy]++;
      xx += dx;
      yy += dy;
    }
  }
  COUNT[x][y] ++;
  return true;
}

void remove(int x, int y) {
  COUNT[x][y] --;
  int dp = --DP[y-x+n];
  int dn = --DN[y+x];
 
  for(int i=0; i<x; i++) {
    int dx = x-i;
    int dy = y-Q[i];
    int dd = gcd(abs(dx),abs(dy));
    dx /= dd;
    dy /= dd;
    int xx = x+dx;
    int yy = y+dy;
    while(xx >= 0 && yy >= 0 && xx < n && yy < n) {
      MASK[xx][yy]--;
      xx += dx;
      yy += dy;
    }
  }
}


void printM(vector<int>& Q) {
  for(int i=0; i<n ;i++) {
    for(int j=0; j<n ;j++) {
      cerr << ((Q[i] == j) ? 1 : 0) << " ";
    }
    cerr << endl;
  }
  cerr << endl;
}
void print() {
  for(int i=0; i<n ;i++) {
    for(int j=0; j<n ;j++) {
      cerr << COUNT[i][j] << " ";
    }
    cerr << endl;
  }
  cerr << endl;
}
#define rep(i,n) for(int i=0; i<(n) ;i++)

bool check () {
  rep(i,n)
    rep(j,n)
      rep(k,n) {
        if(i<j && j<k) {
          int dx1 = j-i;
          int dy1 = Q[j]-Q[i];
          int dx2 = k-i;
          int dy2 = Q[k]-Q[i];
          int g1 = gcd(abs(dx1),abs(dy1));
          int g2 = gcd(abs(dx2),abs(dy2));

          if(dx1/g1 == dx2/g2 && dy1/g1 == dy2/g2) {
            cerr << "ZONK" << endl;
            cerr << " " << i << " : " << Q[i] << endl;
            cerr << " " << j << " : " << Q[j] << endl;
            cerr << " " << k << " : " << Q[k] << endl;
            return false;
          }
        }
      }
      return true;
}

int timeout = 50000;
vector<int> Q2;
void search(int x, int randomize = 15) {
   if(--timeout <= 0) {
     //if(timeout == 0) print();
     return;
   }
   if(x > best) {
    best = x;
     Q2.clear();
     for(int i=0; i<Q.size(); i++) {
       Q2.push_back(Q[i]);
     }
    //cout << x << endl;
   }
  if(x == n) {
    print();
    //cout << n << endl;
    if(check()) {
      print(Q);
      _exit(0);
    }
  }
  int rr1 = x, rr2 = x;
  if(randomize && ((rand() % randomize) < 10)) {
	  int nn = min(n, x+10);
	  rr1 = x + rand()%(nn-x);
	  rr2 = x + rand()%(nn-x);
	  swap(Q[rr1],Q[rr2]);
  }
  for (int i=x; i<n; i++) {
      //for(int xx=0;xx<x;xx++)cerr<<" ";cerr << " add " << x << " : " << Q[i] << endl;
    if(add(x, Q[i])) {
      //cerr << " ok " << endl;
      swap(Q[x],Q[i]);
      search(x+1, randomize);
      swap(Q[x],Q[i]);
      remove(x,Q[i]);
    }
  }
  if(randomize) {
  	swap(Q[rr1],Q[rr2]);
  }
}

class E {
  vector<int> Q;
  int _eval;
public:
  E(vector<int>& q):Q(q) {
    _eval = -1;
  }

  void fix() {
    int *X = new int[Q.size()];
    int *U = new int[Q.size()];
    memset(X, 0, Q.size()*sizeof(int));
    for(int i=0; i<Q.size() ;i++) {
      X[Q[i]] ++;
    }
    for(int i=0; i<Q.size() ;i++) {
      if(X[i]) U[i] = rand() % X[i];
    }
    vector<int> touse, unused;
    for(int i=0; i<Q.size() ;i++) {
      if(X[i] == 0) {
        unused.push_back(i);
      } if(X[i] > 1) {
        if(--U[i]) {
          touse.push_back(Q[i]);
        }
      }
    }
    delete X;
    delete U;
    random_permutation(touse.begin(), touse.end());
    for(int i=0; i<unused.size(); i++) {
      Q[unused[i]] = touse[i];
    }
  }

  int eval() {
    if(_eval == -1) return _eval = do_eval();
  }
  int do_eval() {
    int *DP = new int[Q.size()*2],
        *DN = new int[Q.size()*2];

    //printM(Q);

    memset(DP, 0, Q.size()*2*sizeof(int));
    memset(DN, 0, Q.size()*2*sizeof(int));
    int ev = 0;
    for(int i=0; i<Q.size(); i++) {
      if(DN[i+Q[i]]++) ev+=1;
      if(DP[Q.size()-i+Q[i]]++) ev+=1;
      for(int j=i+1; j<Q.size(); j++) {
        int di = j-i;
        int dy = Q[j] - Q[i];
        int g = gcd(abs(dy),abs(di));
        di /= g;
        dy /= g;
        for(int k=1; k*di+j <Q.size(); k++) {
          int kk = k*di+j;
          if(Q[kk] == Q[j]+dy*k) ev+=1;
        }
      }
    }
    delete DN;
    delete DP;
    return ev;
  }

  void pmx(E* e, vector<E*>& out) {
    vector<int> a(Q),b(e->Q);
    int q = rand() % 4 + 2;
    vector<int> pivs;
    for(int i=0; i<q; i++) pivs.push_back(rand()%Q.size());
    sort(pivs.begin(), pivs.end());
    int j = 0;
    bool sw = false;
    for(int i=0; i<q; i++) {
      while(j<pivs.size() && pivs[j] == i) { j++; sw = !sw; }
      if(sw) {
        swap(a[i],b[i]);
      }
    }
    E *ea = new E(a),
      *eb = new E(b);
    ea->fix();
    ea->fix();
    cerr << " " << e->eval() << " : " << this->eval();
    cerr << " " << ea->eval() << " : " << eb->eval() << endl;
    out.push_back(ea);
    out.push_back(eb);
  }
};
struct ECMP {
  bool operator()(E* a, E* b) const {
    return a->eval() < b->eval();
  }
};

int main(int argc, char **argv) {
  if(argc > 1) {
    int seed= atoi(argv[1]);
    srand(seed);
  }
  if(argc > 2) {
    timeout = atoi(argv[2]);
  }
  cin >> n;
  for(int i=0; i<n; i++) {
    Q.push_back(i);
  }
  random_permutation(Q.begin(), Q.end());
  
  vector<E*> pop;
  search(0,1);
  int ix = 0;
  while(true) {
    if(pop.size() == 10) break;
    E* e = new E(Q2);
    cerr << "E " << e->eval() << endl;
    cerr << " best " << best << endl;
    pop.push_back(e);
    if(ix++ % 3) {
      for(int i=0; i<best/2; i++) {
        swap(Q2[i],Q2[best-i-1]);
      }
    } else {
      for(int i=0; i<best-1; i++) {
        swap(Q2[i],Q2[i+1]);
      }
    }
    for(int i=0; i<Q2.size(); i++) Q[i] = Q2[i];
    int b2 = best;
    best = 0;
    timeout = 50000;
    search(0,100);
  }
  
  int population = 1000;
  int iterations = 1000;
  while(iterations--) {
    int xx = population;
    for(int i=0; i<xx ;i++) {
      int a = rand() % pop.size();
      int b = a; 
      while(b==a) b = rand() % pop.size();
      pop[a]->pmx(pop[b], pop);
    }

    sort(pop.begin(), pop.end(), ECMP());
    
    int n = pop.size();
    long long r = rand() | ((long long)rand() << 16LL) % (n*n);
    r = min((int)sqrt(r), n-1);
    pop[r] = 0;
    int e = 0;
    for(int i=0; i<n; i++) {
      if(pop[i]) pop[e++] = pop[i];
    }

    pop.resize(e);

    cerr << "best" << pop[0]->eval() << endl; 
    cerr << "worst" << pop[pop.size()-1]->eval() << endl; 
  }
  return 0;
}
