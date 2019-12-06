#include<fstream>
#include<stack>
#include"lexical.h"

ifstream file;
Token token = { ERRTKEN,"",0.0,NULL };
string TokenBuffer;
char c;

//模板函数：将string类型变量转换为常用的数值类型（此方法具有普遍适用性）
template <class Type>
Type stringToNum(const string str)
{
	Type num = 0;
	int p = str.find('.');//小数点的位置,从0开始计数

	//转化小数点前面的字符为数字，从小数点开始往前加。i为位数指示器
	for (int t = p - 1, i = 0; t >= 0; t--) {
		if (isdigit((char)str[t])) {
			num += ((char)str[t] - '0') * pow(10, i);
			i++;
		}
		else  //如果不是数字字符，就抛出异常
			throw exception();
	}

	//转化小数点后面的字符为数字，从小数点开始往后加
	for (int t = p + 1, i = 1; t < str.length() - 1; t++) {//此处识别时，将最后的小数点忽略
		if (isdigit((char)str[t])) {
			num += ((char)str[t] - '0') * pow(10, -i);
			i++;
		}
		else  //如果不是数字字符，就抛出异常
			throw exception();
	}

	return num;
}

bool InitScanner(string fileName) {
	file.open(fileName);
	if (file.is_open()) {
		c = file.get();
		return true;
	}
	else
		return false;
}

Token GetToken() {
	TokenBuffer.clear();//初始时先把缓存区清空
	do {
		if (c == EOF) {
			token.type = NONTOKEN;
			token.lexeme = "";
			token.value = 0.0;
			return token;
		}

		else if (isspace(c)) {
			c = file.get();
			continue;
		}

		else if (isalpha(c)) {
			do {//每次读到的第一个输入是字符时，继续读后面的，直到读到空白为止
				TokenBuffer += toupper(c);//因为符号表中的都是大写，所以就把字符变成大写然后再加入缓存区。
				c = file.get();
			} while (isalnum(c));

			for (int i = 0; i < 29; i++) {
				if (TokenBuffer.compare(TokenTable[i].lexeme) == 0)
					return TokenTable[i];//缓存和符号表中的原始字符串相比较，如果一样，就直接把该Token返回。
			}

			token.type = ERRTKEN; //如果整个单词都识别完了，但不在符号表中，就当错误单词处理
			token.lexeme = TokenBuffer;
			token.value = 0.0;
			return token;
		}

		else if (isdigit(c)) {//如果读到的第一个字符是数字，就一直往下读，直到不是数字或者小数点为止
			do {
				TokenBuffer += c;
				c = file.get();
			} while (isalnum(c) || c == '.');//浮点数包含数字和小数点,将字符也加入是为了检测输入是否有错误以及未来识别科学计数法
			try {
				token.lexeme = TokenBuffer;
				token.type = CONST_ID;
				token.value = stringToNum<double>(TokenBuffer+".");//在字符串后面加上小数点，以识别整数
			}
			catch (exception e) {
				//异常处理
				token.lexeme = TokenBuffer;
				token.type = ERRTKEN;
				token.value = 0.0;
			}
			return token;
		}
		else {
			TokenBuffer.clear();
			switch (c) {
			case '-':
				if ((c = file.get()) && (c != '-')) {//识别到减号，如果下一个字符不是减号，就返回一个减号token
					token.type = MINUS;
					token.lexeme = "-";
					token.value = 0.0;
					return token;
				}
				else if (c == '-') { //如果下一个字符是减号，就返回一个注释符--的token
					token.type = COMMENT;
					token.lexeme = "--";
					token.value = 0.0;

					do {
						c = file.get();
					} while (c != '\n' && c != EOF); //忽略掉注释符这一行后面的所有字符
					return token;
				}
				break;//开启下一轮检查
			case '*':
				if ((c = file.get()) && (c != '*')) { //识别到乘号，如果下一个字符不是乘号，就返回一个乘号token
					token.type = MUL;
					token.lexeme = "*";
					token.value = 0.0;
					return token;
				}
				else if (c == '*') { //如果下一个字符是乘号，就返回一个乘方**的token
					token.type = POWER;
					token.lexeme = "**";
					token.value = 0.0;
					c = file.get(); //刷新c为下一个字符
					return token;
				}
				break;//开启下一轮检查
			case '/':
				if ((c = file.get()) && (c != '/')) { //识别到除号，如果下一个字符不是除号，就返回一个除号token
					token.type = DIV;
					token.lexeme = "/";
					token.value = 0.0;
					return token;
				}
				else if (c == '/') { //如果下一个字符是除号，就返回一个注释符//的token
					token.type = COMMENT;
					token.lexeme = "//";
					token.value = 0.0;

					do {
						c = file.get();
					} while (c != '\n' && c != EOF); //忽略掉注释符这一行后面的所有字符
					return token;
				}
				break;
			default:
				TokenBuffer += c;
				for (int i = 0; i < 29; i++) { //首先查找该字符是否为符号表中的字符，如果是，则直接返回该token
					if (TokenBuffer.compare(TokenTable[i].lexeme) == 0) {
						c = file.get();	//先更新c再返回
						return TokenTable[i];
					}
				}

				//不是符号表中规定的符号，当错误符号处理
				TokenBuffer += c;
				token.type = ERRTKEN;
				token.lexeme = TokenBuffer;
				token.value = 0.0;

				c = file.get();
				return token;
				break;
			}
		}
	} while (true);
}

void CloseScanner() {
	file.close();
}