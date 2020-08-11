#include "NoPersonException.h"
#include <iostream>
using namespace std;
int main() {
	int pizzaSclices = 12;
	int persons = 0;
	int slicesPerPerson = 0;
	try {
		cout << "��� ���� �Է��Ͻÿ� : ";
		cin >> persons;
		if (persons <= 0) {
			throw NoPersonException(persons);
		}
		slicesPerPerson = pizzaSclices / persons;
		cout << "�ѻ���� ���ڴ� " << slicesPerPerson << "�Դϴ�." << endl;
	}
	catch (NoPersonException e) {
		cout << "���� : ����� " << e.getPersons() << "�� �Դϴ�." << endl;
	}
	return 0;

}