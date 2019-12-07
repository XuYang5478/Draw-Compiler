#pragma once

#include<iostream>
#include<string>
#include<cmath>
using namespace std;

enum Token_Type								  //�Ǻŵ���𣬹�22��
{
	ORIGIN, SCALE, ROT, IS, TO, STEP, DRAW, FOR, FROM,//�����֣�һ��һ�룩
	T,										  //����
	SEMICO, L_BRACKET, R_BRACKET, COMMA,		  //�ָ���
	PLUS, MINUS, MUL, DIV, POWER,			  //�����
	FUNC,									  //���������ã�
	CONST_ID,								  //����
	COMMENT,									  //ע�ͷ�
	NONTOKEN,								  //�ռǺţ�Դ���������
	ERRTKEN									  //����Ǻţ��Ƿ����룩
};

struct Token					  //�Ǻŵ����ݽṹ
{
	Token_Type type = ERRTKEN;			  //���
	string lexeme = "";					  //���ԣ�ԭʼ������ַ���
	double value = 0.0;					  //���ԣ����Ǻ��ǳ������ǳ�����ֵ
	double (*FuncPtr)(double) = NULL;	  //���ԣ����Ǻ��Ǻ������Ǻ���ָ��
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
	{ORIGIN,"ORIGIN",0.0,NULL},//����ƽ��
	{SCALE,"SCALE",0.0,NULL},//��������
	{ROT,"ROT",0.0,NULL},//����ʱ�룩�Ƕ���ת
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

bool InitScanner(string fileName);//��ʼ���ʷ�������

Token GetToken();//ͨ���ʷ����������һ���Ǻ�

void CloseScanner();//�رմʷ�������
