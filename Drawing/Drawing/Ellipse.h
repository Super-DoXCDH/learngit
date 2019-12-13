#pragma once
#include "Shape.h"
class CEllipse : public CShape
{
protected:
	int HRadius;//椭圆的水平半轴
	int VRadius;//椭圆的垂直半轴
public:
	CEllipse(int x, int y, int hr, int vr);
	void Draw(CDC*pDC);
	bool IsMatched(CPoint pnt);
	void Serialize(CArchive& ar);
	void SetAttribute(int nX, int nY, COLORREF nBorderColor, int nBorderType, int nBorderWidth, COLORREF nFillColor, int nFillType);
	~CEllipse();

	DECLARE_SERIAL(CEllipse)//声明类WEllipse是支持序列化
};

