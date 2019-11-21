#include<iostream>
#include<string>
using namespace std;

enum Token_Type								  //�Ǻŵ���𣬹�22��
{
	ORIGIN, SCALE, ROT, IS, TO, STEP, DRAW, FOR, FROM,//�����֣�һ��һ�룩
	T,										  //����
	SEMICO, L_BRACKET, R_BRACKET, COMMA,		  //�ָ���
	PLUS, MINUS, MUL, DIV, POWER,			  //�����
	FUNC,									  //���������ã�
	CONST_ID,								  //����
	NONTOKEN,								  //�ռǺţ�Դ���������
	ERRTKEN									  //����Ǻţ��Ƿ����룩
};

struct Token					  //�Ǻŵ����ݽṹ
{
	Token_Type type;			  //���
	string lexeme;			  //���ԣ�ԭʼ������ַ���
	double value;			  //���ԣ����Ǻ��ǳ������ǳ�����ֵ
	double (*FuncPtr)(double);//���ԣ����Ǻ��Ǻ������Ǻ���ָ��
};

static Token TokenTable[] = {
	{CONST_ID,"PI",3.1415926,NULL},
	{CONST_ID,"E",2.71828,NULL},
	{T,"T",0.0,NULL}
}
