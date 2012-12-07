#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;

struct Point {
  int x,y;

  Point(int a, int b):x(a),y(b) {}
  
  bool operator<(const Point& o) const {
    if(x!=o.x)return x<o.x;
    return y<o.y;
  }
};

typedef pair<Point,Point> PP;
long long solve(const vector<PP>& SQ) {
  const int inf = 2000000000;
  long long f = 0;
  int n = SQ.size()/2;
  int prev_x = -1, dx = 0;
  int s0=0,s1=0,e0=inf,e1=inf,recs = 0;
  
  sort(SQ.begin(), SQ.end());
  for(int i=0; i<SQ.size(); i++) {
    if(SQ[i].first < SQ[i].second) { // add rectangle
      recs++;
      s0 = max(s0,SQ[i].first.y);
      e0 = min(e0,SQ[i].second.y);
    } else { // remove rectangle
      recs--;
    }
  }
}

int main() {
  int n;
  vector<PP> SQ;
  scanf("%d", &n);
  SQ.reserve(n);
  for(int i=0; i<n; i++) {
    int x1,y1,x2,y2;
    scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
    SQ.push_back(PP( Point(x1,y1),Point(x2,y2) ));
    SQ.push_back(PP( Point(x2,y2),Point(x1,y1) ));
  }
  printf("%lld", solve());
  return 0;
}

