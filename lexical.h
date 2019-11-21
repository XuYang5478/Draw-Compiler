#include<iostream>
#include<string>
using namespace std;

enum Token_Type								  //记号的类别，共22个
{
	ORIGIN, SCALE, ROT, IS, TO, STEP, DRAW, FOR, FROM,//保留字（一字一码）
	T,										  //参数
	SEMICO, L_BRACKET, R_BRACKET, COMMA,		  //分隔符
	PLUS, MINUS, MUL, DIV, POWER,			  //运算符
	FUNC,									  //函数（调用）
	CONST_ID,								  //常数
	NONTOKEN,								  //空记号（源程序结束）
	ERRTKEN									  //出错记号（非法输入）
};

struct Token					  //记号的数据结构
{
	Token_Type type;			  //类别
	string lexeme;			  //属性，原始输入的字符串
	double value;			  //属性，若记号是常数则是常数的值
	double (*FuncPtr)(double);//属性，若记号是函数则是函数指针
};

static Token TokenTable[] = {
	{CONST_ID,"PI",3.1415926,NULL},
	{CONST_ID,"E",2.71828,NULL},
	{T,"T",0.0,NULL}
}
