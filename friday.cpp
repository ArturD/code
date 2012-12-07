/*
ID: adambry1
PROG: friday
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;

int dzien[7];
int miesiac[12];
int main()
{
ifstream fin ("friday.in");
miesiac[0]=31;
miesiac[1]=28;
miesiac[2]=31;
miesiac[3]=30;
miesiac[4]=31;
miesiac[5]=30;
miesiac[6]=31;
miesiac[7]=31;
miesiac[8]=30;
miesiac[9]=31;
miesiac[10]=30;
miesiac[11]=31;
for(int i=0; i<7; i++)
        {
        dzien[i]=0;
        }
int n;

fin >> n;
int pocz=1;
for(int i=0; i<n; i++)
        {
             bool luty=false;
        int rok=1900+i;
        if(rok%4==0)
                    {
                    if(rok%100!=0){miesiac[1]++; luty=true;}
                    if(rok%400==0){miesiac[1]++; luty=true;}  
                    }
           //if(luty==true){cout << rok << " przestepny" << endl;}
            for(int j=0; j<12; j++)
            {
            //cout << rok << " " << pocz << " " << j+1 << " " << miesiac[j] << endl;
            int a=pocz+5;
            if(a>7){a%=7;}
            dzien[a]++;
            //cout << a << " " << dzien[a] << endl;
            int koniec=miesiac[j]%7;
            pocz+=koniec;
            if(pocz>7){pocz%=7;}        
            }
        
        if(luty==true){miesiac[1]--;}
        }
ofstream fout ("friday.out");
fout << dzien[6] << " " << dzien[7] << " ";
for(int i=1; i<=5; i++)
        {
        fout << dzien[i];
	if(i!=5) fout << " ";
        }          
fout << endl;
//system("pause");
return 0;
}
