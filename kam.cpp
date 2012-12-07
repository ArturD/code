#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
int main() {
  int u;
  cin >> u;
  // u zestawów wejściowych
  while(u--) {
    int n;
    cin >> n;
    vector<int> kupki;
    while(n--) {
      int k;
      cin >> k;
      kupki.push_back(k);
    }

    //transformacja do innej wersji problemu
    // teraz gra polega na przesówaniu x kamyków z kupki
    // o jeden w prawo
    vector<int> k2;
    k2.push_back(kupki[0]);
    for(int i=1;i<kupki.size();i++) {
      k2.push_back(kupki[i]-kupki[i-1]);
    }
    // ten problem rozwiązujemy jak nim licząc tylko parzyste od końca
    reverse(k2.begin(), k2.end());
    int wyn =0;
    for(int i=0;i<k2.size();i++) {
      if(i%2==0) wyn ^= k2[i];
    }
    if(wyn == 0) cout << "NIE\n";
    else cout << "TAK\n";
  }
}
