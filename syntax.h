#include "lexical.h"
typedef double (*FuncPtr)(double);

struct ExprNode
{
	Token_Type opCode;
	union {
		struct {
			ExprNode* Left, * Right;
		}CaseOperator;				//二元运算
		struct {
			ExprNode* Child;
			FuncPtr MathFuncPtr;
		}CaseFunc;					//函数调用
		double CaseConst;			//常数，绑定右值
		double* CaseParmPtr;			//常数，绑定左值
	}Content;
};

//建立语法树的程序框架
//ExprNode* MakeExprNode(Token_Type opcode, ...);

//分析器所需的辅助子程序
void FetchToken();
void MatchToken(Token_Type AToken);
void SyntaxError(int case_of);

//主要产生式的递归子程序
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