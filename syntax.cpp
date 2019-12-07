#include"semantics.h"
using namespace std;

double Parameter = 0.0;		//为参数T分配的变量

Token stoken;
/*
ExprNode* MakeExprNode(Token_Type opcode, ...) {
	ExprNode* exprPtr = new (struct ExprNode);
	va_list argPtr;

	exprPtr->opCode = opcode;
	va_start(argPtr, opcode);

	switch (opcode) {
	case CONST_ID:				//常数节点
		exprPtr->Content.CaseConst = (double)va_arg(argPtr, double);
		break;
	case T:						//参数节点
		exprPtr->Content.CaseParmPtr = &Parameter;
		break;
	case FUNC:					//函数调用节点
		exprPtr->Content.CaseFunc.MathFuncPtr = (FuncPtr)va_arg(argPtr, FuncPtr);
		exprPtr->Content.CaseFunc.Child = (ExprNode*)va_arg(argPtr, ExprNode*);
		break;
	default:						//二元运算节点
		exprPtr->Content.CaseOperator.Left = (ExprNode*)va_arg(argPtr, ExprNode*);
		exprPtr->Content.CaseOperator.Right = (ExprNode*)va_arg(argPtr, ExprNode*);
		break;
	}
	va_end(argPtr);
	return exprPtr;
}
*/
ExprNode* MakeExprNode(Token_Type opcode) {
	ExprNode* expr = new(ExprNode);
	if (opcode == T) {
		expr->opCode = T;
		expr->Content.CaseParmPtr = &Parameter;
		return expr;
	}
	else
		return NULL;
}

ExprNode* MakeExprNode(Token_Type opcode, double num) {
	ExprNode* expr = new(ExprNode);
	expr->opCode = opcode;
	expr->Content.CaseConst = num;
	return expr;
}

ExprNode* MakeExprNode(Token_Type opcode, FuncPtr func, ExprNode* exprNode) {
	ExprNode* expr = new(ExprNode);
	expr->opCode = opcode;
	expr->Content.CaseFunc.MathFuncPtr = func;
	expr->Content.CaseFunc.Child = exprNode;
	return expr;
}

ExprNode* MakeExprNode(Token_Type opcode, ExprNode* expr1, ExprNode* expr2) {
	ExprNode* expr = new(ExprNode);
	expr->opCode = opcode;
	expr->Content.CaseOperator.Left = expr1;
	expr->Content.CaseOperator.Right = expr2;
	return expr;
}

void FetchToken() {
	stoken = GetToken();

	if (stoken.type == ERRTKEN) {
		SyntaxError(1);//词法错误
		stoken = GetToken();
	}
}

void MatchToken(Token_Type AToken) {
	if (stoken.type == NONTOKEN)
		return;
	if (stoken.type == AToken)
		cout << "Match Token --> " << stoken.lexeme << endl;
	else {
		cout << "Syntax Error! Need ";
		printf("%d#-Operation\n", AToken);
	}

	FetchToken();
}

void SyntaxError(int case_of) {
	switch (case_of) {
	case 1:cout << "Wrong word!\t\"" << stoken.lexeme << "\"" << endl;
		break;
	case 2:cout << "Wrong sentence!\t\"" << stoken.lexeme << "\"" << endl;
		break;
	default:cout << "Unknow error!" << endl;
		break;
	}
	FetchToken();
}

void Parser(string SrcFilePtr) {
	if (!InitScanner(SrcFilePtr)) {
		cout << "Open Source File Error!\n";
		return;
	}

	FetchToken();
	Program();
	CloseScanner();
}

//程序由语句构成，每条语句后面由分号结束
void Program() {
	cout << ">>> Enter Program()" << endl;

	while (stoken.type != NONTOKEN) {
		//语句的前面可能包含有注释符
		if (stoken.type == COMMENT)
			MatchToken(COMMENT);

		Statement();
		MatchToken(SEMICO);

		//分号的后面可能包含有注释符
		if (stoken.type == COMMENT)
			MatchToken(COMMENT);
	}

	cout << "<<< Exit Program()" << endl;
}

//语句有4类：Origin、Scale、Rot、For
void Statement() {
	cout << ">>> Enter Statement()" << endl;

	ExprNode* expr;
	switch (stoken.type) {
	case ORIGIN:
		MatchToken(ORIGIN);
		OriginStatement();
		break;
	case SCALE:
		MatchToken(SCALE);
		ScaleStatement();
		break;
	case ROT:
		MatchToken(ROT);
		RotStatement();
		break;
	case FOR:
		MatchToken(FOR);
		ForStatement();
		break;
	default:
		expr = Expression(); printSyntaxTree(expr, 0);
		break;
	}

	cout << "<<< Exit Statement()" << endl;
}

/*Origin语句为：
  ORIGIN IS (3, PI/2)
  ORIGIN IS L_BRACKET Expression COMMA Expression R_BRACKET
*/
void OriginStatement() {
	cout << ">>> Enter OriginStatement()" << endl;

	ExprNode* x_ptr, * y_ptr;
	MatchToken(IS);
	MatchToken(L_BRACKET);
	x_ptr = Expression(); printSyntaxTree(x_ptr, 0);
	MatchToken(COMMA);
	y_ptr = Expression(); printSyntaxTree(y_ptr, 0);
	MatchToken(R_BRACKET);

	SetOrigin(getExprValue(x_ptr), getExprValue(y_ptr));//计算数据并设置坐标平移全程量

	cout << "<<< Exit OriginStatement()" << endl;
}

/*Rot语句为：
  ROT IS 3.0
  ROT IS Expression
*/
void RotStatement() {
	cout << ">>> Enter RotStatement()" << endl;

	ExprNode* degree;
	MatchToken(IS);
	degree = Expression(); printSyntaxTree(degree, 0);

	SetRotAngle(getExprValue(degree));	//计算数据并设置旋转角度

	cout << "<<< Exit RotStatement()" << endl;
}

/*Scale语句为：
  SCALE IS (2.0, 3.0)
  SCALE IS L_BRACKET Expression COMMA Expression R_BRACKET
*/
void ScaleStatement() {
	cout << ">>> Enter ScaleStatement()" << endl;

	ExprNode* x_ptr, * y_ptr;
	MatchToken(IS);
	MatchToken(L_BRACKET);
	x_ptr = Expression(); printSyntaxTree(x_ptr, 0);
	MatchToken(COMMA);
	y_ptr = Expression(); printSyntaxTree(y_ptr, 0);
	MatchToken(R_BRACKET);

	SetScale(getExprValue(x_ptr), getExprValue(y_ptr));	//计算数据并设置缩放比例

	cout << "<<< Exit ScaleStatement()" << endl;
}

/*For语句为：
**FOR T FROM 0 TO 5 STEP 1 DRAW (2T, 5T)
**FOR T FROM Expression TO Expression STEP Expression DRAW L_BRACKET Expression COMMA Expression R_BRACKET
*/
void ForStatement() {
	cout << ">>> Enter ForStatement()" << endl;

	ExprNode* start_ptr, * end_ptr, * step_ptr, * x_ptr, * y_ptr;
	MatchToken(T);
	MatchToken(FROM);
	start_ptr = Expression(); printSyntaxTree(start_ptr, 0);
	MatchToken(TO);
	end_ptr = Expression(); printSyntaxTree(end_ptr, 0);
	MatchToken(STEP);
	step_ptr = Expression(); printSyntaxTree(step_ptr, 0);
	MatchToken(DRAW);
	MatchToken(L_BRACKET);
	x_ptr = Expression(); printSyntaxTree(x_ptr, 0);
	MatchToken(COMMA);
	y_ptr = Expression(); printSyntaxTree(y_ptr, 0);
	MatchToken(R_BRACKET);

	DrawLoop(getExprValue(start_ptr), getExprValue(end_ptr), getExprValue(step_ptr), x_ptr, y_ptr);

	cout << "<<< Exit ForStatement()" << endl;
}

ExprNode* Expression() {
	cout << ">>> Enter Expression()" << endl;

	ExprNode* left, * right;
	Token_Type token_tmp;
	left = Term();
	while (stoken.type == PLUS || stoken.type == MINUS) {
		token_tmp = stoken.type;
		MatchToken(token_tmp);
		right = Term();
		left = MakeExprNode(token_tmp, left, right);
	}
	cout << "<<< Exit Expression()" << endl;
	return left;
}

ExprNode* Term() {
	cout << ">>> Enter Term()" << endl;

	ExprNode* left, * right;
	Token_Type token_tmp;
	left = Factor();
	while (stoken.type == MUL || stoken.type == DIV) {
		token_tmp = stoken.type;
		MatchToken(token_tmp);
		right = Factor();
		left = MakeExprNode(token_tmp, left, right);
	}
	cout << "<<< Exit Term()" << endl;
	return left;
}

ExprNode* Factor() {
	cout << ">>> Enter Factor()" << endl;

	ExprNode* left, * right;
	Token_Type token_tmp = stoken.type;
	switch (stoken.type) {
	case PLUS:
		left = MakeExprNode(CONST_ID, 0);
		MatchToken(token_tmp);
		right = Factor();
		cout << "<<< Exit Factor()" << endl;
		return MakeExprNode(token_tmp, left, right);
	case MINUS:
		left = MakeExprNode(CONST_ID, 0);
		MatchToken(token_tmp);
		right = Factor();
		cout << "<<< Exit Factor()" << endl;
		return MakeExprNode(token_tmp, left, right);
	default:
		cout << "<<< Exit Factor()" << endl;
		return Component();
	}
}

ExprNode* Component() {
	cout << ">>> Enter Component()" << endl;

	ExprNode* left, * right;
	Token_Type token_tmp;
	left = Atom();
	if (stoken.type == POWER) {
		token_tmp = stoken.type;
		MatchToken(token_tmp);
		right = Component();
		cout << "<<< Exit Component()" << endl;
		return MakeExprNode(token_tmp, left, right);
	}
	else {
		cout << "<<< Exit Component()" << endl;
		return left;
	}
}

ExprNode* Atom() {
	cout << ">>> Enter Atom()" << endl;

	ExprNode* expr;
	Token token_tmp = stoken;
	switch (token_tmp.type) {
	case CONST_ID:
		MatchToken(token_tmp.type);
		expr = MakeExprNode(token_tmp.type, token_tmp.value);
		break;
	case T:
		MatchToken(token_tmp.type);
		expr = MakeExprNode(token_tmp.type);
		break;
	case FUNC:
		MatchToken(token_tmp.type);
		MatchToken(L_BRACKET);
		expr = MakeExprNode(token_tmp.type, token_tmp.FuncPtr, Expression());
		MatchToken(R_BRACKET);
		break;
	case L_BRACKET:
		MatchToken(token_tmp.type);
		expr = Expression();
		MatchToken(R_BRACKET);
		break;
	default:
		MatchToken(ERRTKEN);
		expr = NULL;
	}
	cout << "<<< Exit Atom()" << endl;
	return expr;
}

void printSpace(int indent) {
	for (int i = 0; i < indent; i++)
		cout << '\t';
}
void printSyntaxTree(ExprNode* root, int indent) {
	if (root == NULL)
		return;

	printSpace(indent);
	switch (root->opCode) {
	case CONST_ID:
		cout << root->Content.CaseConst << endl;
		break;
	case T:
		cout << "T" << endl;
		break;
	case FUNC:
		cout << root->Content.CaseFunc.MathFuncPtr << endl;
		printSyntaxTree(root->Content.CaseFunc.Child, indent + 1);
		break;
	default:
		printf("%d#Operator\n", root->opCode);
		printSyntaxTree(root->Content.CaseOperator.Left, indent + 1);
		printSyntaxTree(root->Content.CaseOperator.Right, indent + 1);
	}
}
