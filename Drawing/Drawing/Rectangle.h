#pragma once
#include "Shape.h"
class CRectangle : public CShape
{
protected:
	int Width;//矩形的宽
	int Height;//矩形的高
public:
	CRectangle();
	CRectangle(int x, int y, int w, int h);
	void Draw(CDC*pDC);
	bool IsMatched(CPoint pnt);
	void Serialize(CArchive& ar);
	void SetAttribute(int nX, int nY, COLORREF nBoderColor, int nBoderType, int BoderWidth, COLORREF FillColor, int nFillType);
	~CRectangle();

	DECLARE_SERIAL(CRectangle)//声明类WRectangle是支持序列化
};


