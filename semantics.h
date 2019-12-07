#pragma once

#include <graphics.h>
#include "syntax.h"

void SetOrigin(double x, double y);
void SetRotAngle(double angle);
void SetScale(double x, double y);

//辅助语义函数

//计算表达式的值：深度优先后序遍历语法树
double getExprValue(ExprNode* root);

//计算点的坐标值：首先获取坐标值，然后进行坐标变化
void CalcCoord(ExprNode* x_nptr, ExprNode* y_nptr, double& x_val, double& y_val);

//绘制一个点
void DrawPixel(unsigned long x, unsigned long y);

//循环绘制所有的点
void DrawLoop(double start, double end, double step, ExprNode* x_ptr, ExprNode* y_ptr);