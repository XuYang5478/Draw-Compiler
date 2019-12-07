#pragma once

#include<iostream>
#include<string>
#include<cmath>
using namespace std;

enum Token_Type								  //记号的类别，共22个
{
	ORIGIN, SCALE, ROT, IS, TO, STEP, DRAW, FOR, FROM,//保留字（一字一码）
	T,										  //参数
	SEMICO, L_BRACKET, R_BRACKET, COMMA,		  //分隔符
	PLUS, MINUS, MUL, DIV, POWER,			  //运算符
	FUNC,									  //函数（调用）
	CONST_ID,								  //常数
	COMMENT,									  //注释符
	NONTOKEN,								  //空记号（源程序结束）
	ERRTKEN									  //出错记号（非法输入）
};

struct Token					  //记号的数据结构
{
	Token_Type type = ERRTKEN;			  //类别
	string lexeme = "";					  //属性，原始输入的字符串
	double value = 0.0;					  //属性，若记号是常数则是常数的值
	double (*FuncPtr)(double) = NULL;	  //属性，若记号是函数则是函数指针
};

static Token TokenTable[] = {
	{CONST_ID,"PI",3.1415926,NULL},
	{CONST_ID,"E",2.71828,NULL},
	{T,"T",0.0,NULL},
	{FUNC,"SIN",0.0,sin},
	{FUNC,"COS",0.0,cos},
	{FUNC,"TAN",0.0,tan},
	{FUNC,"LN",0.0,log},
	{FUNC,"EXP",0.0,exp},
	{FUNC,"SQRT",0.0,sqrt},
	{ORIGIN,"ORIGIN",0.0,NULL},//坐标平移
	{SCALE,"SCALE",0.0,NULL},//比例设置
	{ROT,"ROT",0.0,NULL},//（逆时针）角度旋转
	{IS,"IS",0.0,NULL},
	{FOR,"FOR",0.0,NULL},
	{FROM,"FROM",0.0,NULL},
	{TO,"TO",0.0,NULL},
	{STEP,"STEP",0.0,NULL},
	{DRAW,"DRAW",0.0,NULL},
	{PLUS,"+",0.0,NULL},
	{MINUS,"-",0.0,NULL},
	{MUL,"*",0.0,NULL},
	{DIV,"/",0.0,NULL},
	{POWER,"**",0.0,NULL},
	{SEMICO,";",0.0,NULL},
	{L_BRACKET,"(",0.0,NULL},
	{R_BRACKET,")",0.0,NULL},
	{COMMA,",",0.0,NULL},
	{COMMENT,"--",0.0,NULL},
	{COMMENT,"//",0.0,NULL},
};

bool InitScanner(string fileName);//初始化词法分析器

Token GetToken();//通过词法分析器获得一个记号

void CloseScanner();//关闭词法分析器
