#include<iostream>
using namespace std;
class A {
public:
	A() {
		cout << "������ A" << endl;
	}
	~A() {
		cout << "�Ҹ��� A" << endl;
	}
};
class B : public A {
public:
	B() {
		cout << "������ B" << endl;
	}
	~B() {
		cout << "�Ҹ��� B" << endl;
	}
};
class C : public B {
public:
	C() {
		cout << "������ C" << endl;
	}
	~C() {
		cout << "�Ҹ��� C" << endl;
	}
};
int main() {
	C c;
	return 0;
}