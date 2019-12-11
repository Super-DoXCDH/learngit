#pragma once
#include "Shape.h"
#define SQRT3 1.73
#define SQRT2 1.41

class CTriangle : public CShape
{
protected:
	int Length;//正三角形的边长
public:
	CTriangle();
	CTriangle(int x, int y, int length);
	void Draw(CDC*pDC);
	bool IsMatched(CPoint pnt);
	void Serialize(CArchive& ar);
	void SetAttribute(int nX, int nY, COLORREF nBoderColor, int nBoderType, int nBoderWidth, COLORREF nFillColor, int nFillType);
	~CTriangle();

	DECLARE_SERIAL(CTriangle)//声明类WRectangle是支持序列化
};


