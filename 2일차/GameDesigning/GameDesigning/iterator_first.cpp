#include<iostream>
#include<vector>
using namespace std;
int main() {
	vector <int> vec{ 10,20,30,40,50 };
	vector <int>::iterator iter = begin(vec);
	vector<int>::iterator iter1 = vec.begin();
	cout << *iter << endl;
	iter++;
	cout << *iter << endl;
	vector<int> vc{ 1,2,3,4,5 };
	for (auto iter = begin(vc); iter != end(vc); iter++) {
		cout << *iter << ' ';
	}
	cout << endl;
}