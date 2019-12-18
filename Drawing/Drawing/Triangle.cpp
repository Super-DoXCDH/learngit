#include "stdafx.h"
#include "Triangle.h"
#include <math.h>

IMPLEMENT_SERIAL(CTriangle, CObject, 1)//ʵ����WSquare�����л���ָ���汾Ϊ1
CTriangle::CTriangle()
{
	Type = (ElementType)5;//ͼԪ����
	Length = 100;
}

CTriangle::CTriangle(int x, int y, int length)
{
	Type = (ElementType)5;//ͼԪ����
	OrgX = x;
	OrgY = y;
	Length = length;
}

void CTriangle::Draw(CDC * pDC)
{
	// �������ʼ���������ԭ���ʵ�ָ��
	CPen pen, *pOldPen;
	pen.CreatePen(BorderType, BorderWidth, BorderColor);
	pOldPen = (CPen*)pDC->SelectObject(&pen);

	//����ˢ�Ӽ���������ԭˢ�ӵ�ָ��
	CBrush brush, *pOldBrush;
	brush.CreateHatchBrush(FillType, FillColor);
	pOldBrush = (CBrush*)pDC->SelectObject(&brush);

	//����ͼ��
	double x1 = double(OrgX), y1 = double(OrgY) + double(Length) / SQRT3;
	double x2 = double(OrgX) - double(Length) / 2, y2 = double(OrgY) - double(Length) / (2 * SQRT3);
	double x3 = double(OrgX) + double(Length) / 2, y3 = double(OrgY) - double(Length) / (2 * SQRT3);
	CPoint points[3] = { CPoint(double(x1), double(y1)), CPoint(double(x2), double(y2)), CPoint(double(x3), double(y3)) };
	pDC->Polygon(points, 3);

	//ʹ�õ�ǰ���ʺ�ˢ��
	pDC->SelectObject(pOldPen);
	pDC->SelectObject(pOldBrush);
}

bool CTriangle::IsMatched(CPoint pnt)
{
	double x1 = OrgX, y1 = OrgY + Length / sqrt(3);
	double x2 = OrgX - Length / 2, y2 = OrgY - Length / (2 * sqrt(3));
	double x3 = OrgX + Length / 2, y3 = OrgY - Length / (2 * sqrt(3));
	if ( (y1 >= pnt.y) && (x2 <= pnt.x) && (y2 <= pnt.y) && (x3 >= pnt.x) && (y3 <= pnt.y))
		return true;
	else
	    return false;
}

void CTriangle::Serialize(CArchive & ar)
{

	if (ar.IsStoring())
	{
		//�����ļ�
		ar << (WORD)Type;
		ar << OrgX << OrgY;
		ar << BorderColor << BorderType << BorderWidth;
		ar << FillColor << FillType;
		ar << Length;
	}
	else
	{
		//��ȡ�ļ�
		WORD w;
		ar >> w;
		Type = (ElementType)w;
		ar >> OrgX >> OrgY;
		ar >> BorderColor >> BorderType >> BorderWidth;
		ar >> FillColor >> FillType;
		ar >> Length;
	}
}

void CTriangle::SetAttribute(int nX, int nY, COLORREF nBorderColor, int nBorderType, int nBorderWidth, COLORREF nFillColor, int nFillType)
{
	OrgX = nX;
	OrgY = nY;
	BorderColor = nBorderColor;
	BorderType = nBorderType;
	BorderWidth = nBorderWidth;
	FillColor = nFillColor;
	FillType = nFillType;
}


CTriangle::~CTriangle()
{
}
