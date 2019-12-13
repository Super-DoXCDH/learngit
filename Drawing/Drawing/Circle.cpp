#include "stdafx.h"
#include "Circle.h"


IMPLEMENT_SERIAL(CCircle, CObject, 1)//ʵ����WSquare�����л���ָ���汾Ϊ1

CCircle::CCircle(int x, int y, int r)
{
	Type = (ElementType)3;//ͼԪ����
	OrgX = x;
	OrgY = y;
	Radius = r;
}

void CCircle::Draw(CDC * pDC)
{
	//�������ʼ���������ԭ���ʵ�ָ��
	CPen pen, *pOldPen;
	pen.CreatePen(BorderType, BorderWidth, BorderColor);
	pOldPen = (CPen*)pDC->SelectObject(&pen);

	//����ˢ�Ӽ���������ԭˢ�ӵ�ָ��
	CBrush brush, *pOldBrush;
	brush.CreateHatchBrush(FillType, FillColor);
	pOldBrush = (CBrush*)pDC->SelectObject(&brush);

	//����ͼ�Σ�ͨ�����þ���������Բ��
	pDC->Ellipse(OrgX - Radius / 2, OrgY + Radius / 2, OrgX + Radius / 2, OrgY - Radius / 2);

	//ʹ�õ�ǰ���ʺ�ˢ��
	pDC->SelectObject(pOldPen);
	pDC->SelectObject(pOldBrush);
}

bool CCircle::IsMatched(CPoint pnt)
{
	if (((OrgX - Radius / 2) <= pnt.x) && (pnt.x <= (OrgX + Radius / 2)) && ((OrgY - Radius / 2) <= pnt.y) && (pnt.y <= (OrgY + Radius / 2)))
		return true;
	else
		return false;
}

void CCircle::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		//�����ļ�
		ar << (WORD)Type;
		ar << OrgX << OrgY;
		ar << BorderColor << BorderType << BorderWidth;
		ar << FillColor << FillType;
		ar << Radius;
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
		ar >> Radius;
	}
}

void CCircle::SetAttribute(int nX, int nY, COLORREF nBorderColor, int nBorderType, int nBorderWidth, COLORREF nFillColor, int nFillType)
{
	OrgX = nX;
	OrgY = nY;
	BorderColor = nBorderColor;
	BorderType = nBorderType;
	BorderWidth = nBorderWidth;
	FillColor = nFillColor;
	FillType = nFillType;
}

CCircle::~CCircle()
{
}
