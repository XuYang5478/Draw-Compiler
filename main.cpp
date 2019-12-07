#include<iomanip>
#include"semantics.h"
using namespace std;

int main(int argc, char* argv[]) {
	Token ttoken;
	if (argc < 2) {
		cout << "Please input Source File!\n";
		return 0;
	}

	/*词法分析测试*/
	if (!InitScanner(argv[1])) {
		cout << "Open Source File Error!\n";
		return 0;
	}

	cout << "记号类别    字符串    常数值    函数指针\n";
	cout << "-----------------------------------------\n";
	while (1) {
		ttoken = GetToken();
		if (ttoken.type != NONTOKEN) {
			printf("%4d", ttoken.type);	//打印枚举值
			cout << setw(12) << ttoken.lexeme << setw(12) << ttoken.value
				<< setw(12) << hex << ttoken.FuncPtr << endl;
		}
		else
			break;
	};
	cout << "-----------------------------------------\n";
	CloseScanner();

	initgraph(1280, 720);		//初始化绘图窗口

	/*语法&语义分析&绘图*/
	Parser(argv[1]);

	getchar();
	closegraph();		//关闭绘图窗口

	return 0;
}