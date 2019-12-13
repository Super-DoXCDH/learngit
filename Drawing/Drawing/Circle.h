#pragma once
#include "Shape.h"
class CCircle : public CShape
{
protected:
	int Radius;//Բ�İ뾶
public:
	CCircle(int x, int y, int r);
	void Draw(CDC*pDC);
	bool IsMatched(CPoint pnt);
	void Serialize(CArchive& ar);
	void SetAttribute(int nX, int nY, COLORREF nBorderColor, int nBorderType, int BorderWidth, COLORREF FillColor, int nFillType);
	~CCircle();

	DECLARE_SERIAL(CCircle)//������WRectangle��֧�����л�
};

