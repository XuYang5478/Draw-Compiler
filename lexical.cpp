#include<fstream>
#include<stack>
#include"lexical.h"

ifstream file;
Token token = { ERRTKEN,"",0.0,NULL };
string TokenBuffer;
char c;

//ģ�庯������string���ͱ���ת��Ϊ���õ���ֵ���ͣ��˷��������ձ������ԣ�
template <class Type>
Type stringToNum(const string str)
{
	Type num = 0;
	int p = str.find('.');//С�����λ��,��0��ʼ����

	//ת��С����ǰ����ַ�Ϊ���֣���С���㿪ʼ��ǰ�ӡ�iΪλ��ָʾ��
	for (int t = p - 1, i = 0; t >= 0; t--) {
		if (isdigit((char)str[t])) {
			num += ((char)str[t] - '0') * pow(10, i);
			i++;
		}
		else  //������������ַ������׳��쳣
			throw exception();
	}

	//ת��С���������ַ�Ϊ���֣���С���㿪ʼ�����
	for (int t = p + 1, i = 1; t < str.length() - 1; t++) {//�˴�ʶ��ʱ��������С�������
		if (isdigit((char)str[t])) {
			num += ((char)str[t] - '0') * pow(10, -i);
			i++;
		}
		else  //������������ַ������׳��쳣
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
	TokenBuffer.clear();//��ʼʱ�Ȱѻ��������
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
			do {//ÿ�ζ����ĵ�һ���������ַ�ʱ������������ģ�ֱ�������հ�Ϊֹ
				TokenBuffer += toupper(c);//��Ϊ���ű��еĶ��Ǵ�д�����ԾͰ��ַ���ɴ�дȻ���ټ��뻺������
				c = file.get();
			} while (isalnum(c));

			for (int i = 0; i < 29; i++) {
				if (TokenBuffer.compare(TokenTable[i].lexeme) == 0)
					return TokenTable[i];//����ͷ��ű��е�ԭʼ�ַ�����Ƚϣ����һ������ֱ�ӰѸ�Token���ء�
			}

			token.type = ERRTKEN; //����������ʶ�ʶ�����ˣ������ڷ��ű��У��͵����󵥴ʴ���
			token.lexeme = TokenBuffer;
			token.value = 0.0;
			return token;
		}

		else if (isdigit(c)) {//��������ĵ�һ���ַ������֣���һֱ���¶���ֱ���������ֻ���С����Ϊֹ
			do {
				TokenBuffer += c;
				c = file.get();
			} while (isalnum(c) || c == '.');//�������������ֺ�С����,���ַ�Ҳ������Ϊ�˼�������Ƿ��д����Լ�δ��ʶ���ѧ������
			try {
				token.lexeme = TokenBuffer;
				token.type = CONST_ID;
				token.value = stringToNum<double>(TokenBuffer+".");//���ַ����������С���㣬��ʶ������
			}
			catch (exception e) {
				//�쳣����
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
				if ((c = file.get()) && (c != '-')) {//ʶ�𵽼��ţ������һ���ַ����Ǽ��ţ��ͷ���һ������token
					token.type = MINUS;
					token.lexeme = "-";
					token.value = 0.0;
					return token;
				}
				else if (c == '-') { //�����һ���ַ��Ǽ��ţ��ͷ���һ��ע�ͷ�--��token
					token.type = COMMENT;
					token.lexeme = "--";
					token.value = 0.0;

					do {
						c = file.get();
					} while (c != '\n' && c != EOF); //���Ե�ע�ͷ���һ�к���������ַ�
					return token;
				}
				break;//������һ�ּ��
			case '*':
				if ((c = file.get()) && (c != '*')) { //ʶ�𵽳˺ţ������һ���ַ����ǳ˺ţ��ͷ���һ���˺�token
					token.type = MUL;
					token.lexeme = "*";
					token.value = 0.0;
					return token;
				}
				else if (c == '*') { //�����һ���ַ��ǳ˺ţ��ͷ���һ���˷�**��token
					token.type = POWER;
					token.lexeme = "**";
					token.value = 0.0;
					c = file.get(); //ˢ��cΪ��һ���ַ�
					return token;
				}
				break;//������һ�ּ��
			case '/':
				if ((c = file.get()) && (c != '/')) { //ʶ�𵽳��ţ������һ���ַ����ǳ��ţ��ͷ���һ������token
					token.type = DIV;
					token.lexeme = "/";
					token.value = 0.0;
					return token;
				}
				else if (c == '/') { //�����һ���ַ��ǳ��ţ��ͷ���һ��ע�ͷ�//��token
					token.type = COMMENT;
					token.lexeme = "//";
					token.value = 0.0;

					do {
						c = file.get();
					} while (c != '\n' && c != EOF); //���Ե�ע�ͷ���һ�к���������ַ�
					return token;
				}
				break;
			default:
				TokenBuffer += c;
				for (int i = 0; i < 29; i++) { //���Ȳ��Ҹ��ַ��Ƿ�Ϊ���ű��е��ַ�������ǣ���ֱ�ӷ��ظ�token
					if (TokenBuffer.compare(TokenTable[i].lexeme) == 0) {
						c = file.get();	//�ȸ���c�ٷ���
						return TokenTable[i];
					}
				}

				//���Ƿ��ű��й涨�ķ��ţ���������Ŵ���
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