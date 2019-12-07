#pragma once

#include <graphics.h>
#include "syntax.h"

void SetOrigin(double x, double y);
void SetRotAngle(double angle);
void SetScale(double x, double y);

//�������庯��

//������ʽ��ֵ��������Ⱥ�������﷨��
double getExprValue(ExprNode* root);

//����������ֵ�����Ȼ�ȡ����ֵ��Ȼ���������仯
void CalcCoord(ExprNode* x_nptr, ExprNode* y_nptr, double& x_val, double& y_val);

//����һ����
void DrawPixel(unsigned long x, unsigned long y);

//ѭ���������еĵ�
void DrawLoop(double start, double end, double step, ExprNode* x_ptr, ExprNode* y_ptr);