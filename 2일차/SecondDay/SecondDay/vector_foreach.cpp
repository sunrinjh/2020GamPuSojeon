#include<iostream>
#include<vector>
using namespace std;
int main() {
	vector<double> vec(10);
	cout << "10개의 숫자를 입력해주세요 : ";
	for (double& elem : vec) {
		cin >> elem;
	}
	for (double elem : vec) {
		cout << elem << endl;
	}
	return 0;
}