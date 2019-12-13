#pragma once
#include "Shape.h"
class CEllipse : public CShape
{
protected:
	int HRadius;//��Բ��ˮƽ����
	int VRadius;//��Բ�Ĵ�ֱ����
public:
	CEllipse(int x, int y, int hr, int vr);
	void Draw(CDC*pDC);
	bool IsMatched(CPoint pnt);
	void Serialize(CArchive& ar);
	void SetAttribute(int nX, int nY, COLORREF nBorderColor, int nBorderType, int nBorderWidth, COLORREF nFillColor, int nFillType);
	~CEllipse();

	DECLARE_SERIAL(CEllipse)//������WEllipse��֧�����л�
};

