#include<iostream>
#include<cstring>

using namespace std;

int DP[1<<15];
int PERM[15];
int n;

bool solve(int mask) {
  int prev = -1;
  int end = true;
  if(DP[mask]) return DP[mask] > 0;
  for(int i=0; i<n; i++) {
    if((1<<i) & mask) {
      if(PERM[i] < prev) {
        end = false;
        break;
      }
      prev = PERM[i];
    }
  }
  bool win = false;
  if(!end) {
    for(int i=0; i<n; i++) {
      if((1<<i) & mask) {
        bool win2 = solve(mask - (1<<i));
        if(!win2) {
          win = true;
          break;
        }
      }
    }
    
  }
  //cerr << mask << "  -> " << win << endl; 
  DP[mask] = win ? 1 : -1;
  return win;
}

int main() {
  int t;
  cin >> t;
  while(t--) {
    memset(DP, 0, (1<<15) * sizeof(int));
    cin >> n;
    for(int i=0; i<n ;i++) {
      cin >> PERM[i];
    }
    bool win = solve((1<<(n)) - 1);
    if(win) cout << "Alice" << endl;
    else cout << "Bob" << endl;
  } 
}
