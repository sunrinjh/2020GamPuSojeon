#include<iostream>
#include <vector>
using namespace std;
int main() {
	const int SIZE = 3;
	vector<int> a{ 1, 2, 3};
	cout << "บคลอ : ";
	for (int i = 0; i < SIZE; i++) {
		cout << a.at(i) << endl;
	}
	cout << endl;
	for (int i : a){
		cout << i << ' ';

	}
	cout << endl;
	a[1] = 37;
	for (int i = 0; i < SIZE; i++) {
		cout << a[i] << ' ';
	}
	cout << endl;
	vector<int> v(10);
	vector<int> v1(10, 1);
	for (int i : v) {
		cout << i << ' ';
	}
	cout << endl;
	for (int i : v1) {
		cout << i << ' ';
	}
	cout << endl;
	return 0;
}