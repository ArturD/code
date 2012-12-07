#include <iostream>
using namespace std;

int A[40];
int n,k;

void rek(int f, int wpr) {
  if(wpr == k) {
    for(int i=0;i<k; i++) cout << A[i] << " ";
    cout << endl;
  } else {
    for(int i=f; i<=n-(k-wpr)+1; i++)
    {
      A[wpr] = i;
      rek(i+1, wpr+1);
    }
  }
}

int main()
{
int t;
cin >> t;
for(int i=0; i<t; i++){
        cin >> n >> k;
        
          rek(1, 0); 
        }       
cout << endl;
}


