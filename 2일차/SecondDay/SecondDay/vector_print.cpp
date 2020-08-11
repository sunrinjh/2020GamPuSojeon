#include<iostream>
#include<vector>
using namespace std;
void print(const vector<int> &v) {
	for (unsigned i = 0; i < v.size(); i++) {
		cout << v[i] << ' ';
	}
	cout << endl;
}
int main() {
	vector <int> vec{ 10,20,30 };
	print(vec);
	vec[0] = 100;
	vec.at(1) = 200;
	print(vec);
	vec.push_back(400);
	print(vec);
	vec.pop_back();
	print(vec);
	cout << endl;
	for (int& elem : vec) {
		cout << "ภิทย : ";
		cin >> elem;
	}
	cout << endl << "[บคลอ] : " << endl;
	for (int elem : vec) {
		cout << elem << ' ';
	}
	return 0;
}