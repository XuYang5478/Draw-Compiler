#include "lexical.h"
typedef double (*FuncPtr)(double);

struct ExprNode
{
	Token_Type opCode;
	union {
		struct {
			ExprNode* Left, * Right;
		}CaseOperator;				//��Ԫ����
		struct {
			ExprNode* Child;
			FuncPtr MathFuncPtr;
		}CaseFunc;					//��������
		double CaseConst;			//����������ֵ
		double* CaseParmPtr;			//����������ֵ
	}Content;
};

//�����﷨���ĳ�����
//ExprNode* MakeExprNode(Token_Type opcode, ...);

//����������ĸ����ӳ���
void FetchToken();
void MatchToken(Token_Type AToken);
void SyntaxError(int case_of);

//��Ҫ����ʽ�ĵݹ��ӳ���
void Parser(string SrcFilePtr);
void Program();
void Statement();
void OriginStatement();
void RotStatement();
void ScaleStatement();
void ForStatement();

ExprNode* Expression();
ExprNode* Term();
ExprNode* Factor();
ExprNode* Component();
ExprNode* Atom();

void printSyntaxTree(ExprNode* root, int indent);