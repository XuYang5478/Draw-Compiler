#include"semantics.h"

//ȫ�̱���
extern double Parameter;					//Ϊ����T����ı���
double Origin_x = 0.0, Origin_y = 0.0;  //���ڼ�¼ƽ�ƾ���
double Rot_ang = 0.0;					//���ڼ�¼��ת�Ƕ�
double Scale_x = 1, Scale_y = 1;			//���ڼ�¼��������

void SetOrigin(double x, double y) {
	Origin_x = x;
	Origin_y = y;
}

void SetRotAngle(double angle) {
	Rot_ang = angle;
}

void SetScale(double x, double y) {
	Scale_x = x;
	Scale_y = y;
}

double getExprValue(ExprNode* root) {
	if (root == NULL)
		return 0.0;

	switch (root->opCode) {
	case PLUS:
		return getExprValue(root->Content.CaseOperator.Left) + getExprValue(root->Content.CaseOperator.Right);
		break;
	case MINUS:
		return getExprValue(root->Content.CaseOperator.Left) - getExprValue(root->Content.CaseOperator.Right);
		break;
	case MUL:
		return getExprValue(root->Content.CaseOperator.Left) * getExprValue(root->Content.CaseOperator.Right);
		break;
	case DIV:
		return getExprValue(root->Content.CaseOperator.Left) / getExprValue(root->Content.CaseOperator.Right);
		break;
	case POWER:
		return pow(getExprValue(root->Content.CaseOperator.Left), getExprValue(root->Content.CaseOperator.Right));
		break;

	case FUNC:
		return (*root->Content.CaseFunc.MathFuncPtr)(getExprValue(root->Content.CaseFunc.Child));
		break;
	case CONST_ID:
		return root->Content.CaseConst;
		break;
	case T:
		return *(root->Content.CaseParmPtr);
		break;

	default:
		return 0.0;
		break;
	}
}

void CalcCoord(ExprNode* x_nptr, ExprNode* y_nptr, double& x_val, double& y_val) {
	double local_x, local_y, temp;
	local_x = getExprValue(x_nptr);								//������ԭʼ����
	local_y = getExprValue(y_nptr);
	local_x *= Scale_x;											//�����任
	local_y *= Scale_y;
	temp = local_x * cos(Rot_ang) + local_y * sin(Rot_ang);		//��ת�任
	local_y = local_y * cos(Rot_ang) - local_x * sin(Rot_ang);
	local_x = temp;
	local_x += Origin_x;											//ƽ�Ʊ任
	local_y += Origin_y;
	x_val = local_x;												//���ر任��������
	y_val = local_y;
	cout << "( " << local_x << ", " << local_y << " )\n";
}

void DrawPixel(unsigned long x, unsigned long y) {
	putpixel(x, y, 0xFFFFFF);
}

void DrawLoop(double start, double end, double step, ExprNode* x_ptr, ExprNode* y_ptr) {
	double x=0.0, y=0.0;
	for (Parameter = start; Parameter <= end; Parameter += step) {
		CalcCoord(x_ptr, y_ptr, x, y);					//����ʵ������
		DrawPixel((unsigned long)x, (unsigned long)y);	//����������Ƶ�
	}
}
