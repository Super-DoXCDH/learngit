#pragma once
#include "stdafx.h"

#if !defined(AFX_SHAPE_H__0800ED02_2AF6_43A7_892D_38DF1FE9C573__INCLUDED_)
#define AFX_SHAPE_H__0800ED02_2AF6_43A7_892D_38DF1FE9C573__INCLUDED_

#if _MSC_VER > 1000

#endif // _MSC_VER > 1000
enum ElementType{
	NOTSET, SQUARE,
	RECTANGLE,
	CIRCLE,
	ELLIPSE,
	TRIANGLE,
	TEXT };

class CShape : public CObject
{
public:
	ElementType Type;//图元类型
	int OrgX;//鼠标原点的坐标
	int OrgY;
	int Angle;

	COLORREF BorderColor;//图形边框的颜色
	int BorderType;//图形边框线型（实线，虚线，虚点线）
	int BorderWidth;//图形边框宽度

	COLORREF FillColor;//图形填充颜色
	int FillType;//图形填充类型（实心，双对角， 十字交叉）
public:
	CShape();
	virtual ~CShape();
	//纯虚函数
	virtual void Draw(CDC* pDC) = 0;//绘制图元函数
	virtual bool IsMatched(CPoint pnt) = 0;//判断鼠标点是否落在图形内
	virtual void Serialize(CArchive& ar) = 0;//序列化函数
	virtual void SetAttribute(int nX, int nY, COLORREF nBoderColor, int nBoderType, int BoderWidth, COLORREF FillColor, int nFillType) = 0;//改变图形属性表函数
};


#endif // !defined(AFX_SHAPE_H__0800ED02_2AF6_43A7_892D_38DF1FE9C573__INCLUDED_)

