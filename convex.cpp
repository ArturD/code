#include <iostream>

#include <vector>
#include <algorithm>

using namespace std; 


struct point {
  int X,Y;
  point(int x, int y) {
    X = x;
    Y = y;
  }

  point operator-(point b) const {
    return point(X-b.X, Y-b.Y);
  }
  
  point operator-=(point b) {
    X -= b.X;
    Y -= b.Y;
    return *this;
  }

  long long operator*(point b) const {
    return (long long) X*b.Y - (long long) Y*b.X;
  }

  long long dl() const {
    return X*X + Y*Y;
  }

  int cz() const {
    if (X == 0 && Y == 0) return 0;
    if (X == 0 && Y > 0) return 1;
    if (X > 0) return 1;
    if (X == 0 && Y < 0) return 2;
    if (X < 0) return 2;
    cerr << "!";
  }
};

struct cmp {
  bool operator()(const point& a, const point& b) const {
    if(a.cz() != b.cz()) return a.cz() < b.cz();
    if(a*b == 0) return a.dl() < b.dl(); 
    return a*b < 0;
  }
};

void hull(vector<point>& P) {
  if(P.size() < 3) return;
  vector<point> S;
  S.push_back(P[0]);
  S.push_back(P[1]);
    cerr << "PUSH: " << P[0].X << ":" << P[0].Y << endl; 
    cerr << "PUSH: " << P[1].X << ":" << P[1].Y << endl; 
  
  for(int i=2; i<P.size(); i++) {
    while(true) {
      if(S.size() < 2) { cerr << "!!"; }
      point a = S[S.size()-1],
            b = S[S.size()-2];
      point c = P[i];
      if((c-a) * (b-a) < 0) break;
      cerr << "POP:  " << a.X << ":" << a.Y << endl; 
      S.pop_back();
    }
    cerr << "PUSH: " << P[i].X << ":" << P[i].Y << endl; 
    S.push_back(P[i]);
  }
  swap(P,S);
}

vector<point> P;

int main () {
  int n;
  cin >> n;
  for(int i=0; i<n; i++) {
    int a,b;
    cin >> a >> b;
    P.push_back(point(a,b));
  }

  point s = P[0];
  for(int i=0; i<n; i++) {
    if(s.X > P[i].X || (s.X == P[i].X && s.Y > P[i].Y)) {
      s = P[i];
    }
  }

  for(int i=0; i<n; i++) {
    P[i] -= s;
  }
  
  sort(P.begin(), P.end(), cmp());
  hull(P);

  for(int i=0; i<n; i++) {
    cout << P[i].X << " " << P[i].Y << endl;
  }

  return 0;
}
