#include<easyx.h>
#include<iomanip>
#include<fstream>
#include"lexical.h"
using namespace std;

int main(int argc, char* argv[]) {
	Token ttoken;
	if (argc < 2) {
		cout << "Please input Source File!\n";
		return 0;
	}

	if (!InitScanner(argv[1])) {
		cout << "Open Source File Error!\n";
		return 0;
	}

	cout << "�Ǻ����    �ַ���    ����ֵ    ����ָ��\n";
	cout << "-----------------------------------------\n";
	while (1) {
		ttoken = GetToken();
		if (ttoken.type != NONTOKEN) {
			printf("%4d", ttoken.type);	//��ӡö��ֵ
			cout << setw(12) << ttoken.lexeme << setw(12) << ttoken.value
				<< setw(12) << hex << ttoken.FuncPtr << endl;
		}
		else
			break;
	};
	cout << "-----------------------------------------\n";
	CloseScanner();

	return 0;
}