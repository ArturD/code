/*
ID: adambry1
PROG: gift1
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <map>
#include <vector>

using namespace std;

map<string, int> U;
vector<string> order;
int main()
{
	ifstream fin ("gift1.in");
	ofstream fout ("gift1.out");
	
	int n;
	fin >> n;
	for(int i=0; i<n; i++) {
		string name;
		fin >> name;
		U[name] = 0;	
		order.push_back(name);
	}
	for(int i=0; i<n; i++) {
		string name;
		int m;
		int give;
		fin >> name >> give >> m;
		if(m != 0) {
			U[name] -= (give/m)*m;
			for(int i=0; i<m; i++) {
				string name2;
				fin >> name2;
				U[name2] += give/m;
			}	
		}
	}
	for(int i=0; i<n; i++) {
		fout << order[i] << " " << U[order[i]] << endl;
	}
	return 0;
}
