#include <iostream>
using namespace std;

typedef unsigned long long ull;

ull liczba[100000];


ull nww(ull a, ull b)
{
     ull _a =a;
     ull _b =b;
     while(b)
     {
     ull akt=b;
     b=a%b;
     a=akt;
    
     }
     a=(_a/a)*_b;
     return a;
}

int main()
{
ios_base::sync_with_stdio(false);
int t;
cin >> t;
for(int i=0; i<t; i++)
        {
        ull a;
        cin >> a;
        for(int j=0; j<a; j++)
                {
                cin >> liczba[j];
                }
                ull aa=liczba[0];
        for(int j=1; j<a;j++)
                {
                ull b=liczba[j];
                aa=nww(aa,b);
                
                
                }
        cout << aa << endl;
        }    
}
