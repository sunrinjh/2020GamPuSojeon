#include<iostream>
#include<list>
using namespace std;
int main() {
	bool done = false;
	char command;
	int value;
	list<int>commandList;
	while (!done) {
		cout << "명령어를 입력해주세요 : I) insert P) print L) length E) erase Q) quit >>";
		cin >> command;
		switch (command) {
		case 'I':
		case 'i':
			if (cin >> value) {
				commandList.push_back(value);
			}
			else {
				done = true;
			}
			break;

		case 'P':
		case 'p':
			for (const auto& elem : commandList) {
				cout << elem << ' ';
			}
			cout << endl;
			break;
		case 'L':
		case 'l':
			cout << "Numbers of Elements : " << commandList.size() << endl;
			break;
		case 'E':
		case 'e':
			commandList.clear();
			break;
		case 'Q':
		case 'q':
			done = true;
			break;
		}

	}
}