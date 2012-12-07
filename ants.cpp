#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int _mod(int x, int mod) {
  return (x+mod) % mod;
}

int main() {
  ios_base::sync_with_stdio(false); 

  int n;
  vector<int> ants;

  cin >> n;
  for(int i=0; i<n ;i++) {
    int ant;
    cin >> ant;
    ants.push_back(ant);
  }
  sort(ants.begin(), ants.end());
  long long result = (n/2) * ((n+1)/2) * 400000LL;
  int cur = n;
  while( _mod(ants[_mod(cur  ,n)]    ,1000) ==
         _mod(ants[_mod(cur-1,n)] +1 ,1000) ) cur--;
  int first = cur;
  // cerr << " -- "<< first <<" " << ants[_mod(first, n)] << endl;
  do {
    int jump = cur;
    while( _mod(ants[_mod(jump  ,n)]    ,1000) ==
           _mod(ants[_mod(jump+1,n)] -1 ,1000) ) jump++;
    result += (jump-cur+1)/2;
    cur = jump + 1;
  } while(_mod(cur,n)!=_mod(first,n));
  cout << result << endl;
  return 0;
}
