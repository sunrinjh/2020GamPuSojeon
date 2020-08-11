#include<iostream>
using namespace std;
template<typename T>
T get_max(T x, T y) {
	if (x > y) {
		return x;
	}
	else {
		return y;
	}
}
template <typename T1, typename T2>
void ShowData(T1 t1, T2 t2) {
	cout << t1 << "+" << t2 << endl;
}
int main() {
	int x, y;
	float x1, x2;
	cin >> x >> y;
	cout << "정수 : " << get_max<int>(x, y) << endl; // <int> 같은 자료형표시는 없어도 됨.
	cin >> x1 >> x2;
	cout << "실수 : " << get_max<float>(x1, x2) << endl;
	char c;
	int a;
	float b;
	cin >> a >> b >> c;
	ShowData(a, b);
	ShowData(b, c);
	ShowData(a,c);
}