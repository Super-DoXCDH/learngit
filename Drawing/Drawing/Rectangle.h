#pragma once
#include "Shape.h"
class CRectangle : public CShape
{
protected:
	int Width;//���εĿ�
	int Height;//���εĸ�
public:
	CRectangle();
	CRectangle(int x, int y, int w, int h);
	void Draw(CDC*pDC);
	bool IsMatched(CPoint pnt);
	void Serialize(CArchive& ar);
	void SetAttribute(int nX, int nY, COLORREF nBoderColor, int nBoderType, int BoderWidth, COLORREF FillColor, int nFillType);
	~CRectangle();

	DECLARE_SERIAL(CRectangle)//������WRectangle��֧�����л�
};


