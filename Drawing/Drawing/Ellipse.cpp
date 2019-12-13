#include "stdafx.h"
#include "Ellipse.h"

IMPLEMENT_SERIAL(CEllipse, CObject, 1)//ʵ����WSquare�����л���ָ���汾Ϊ1

CEllipse::CEllipse(int x, int y, int hr, int vr)
{
	Type = (ElementType)4;//ͼԪ����
	OrgX = x;
	OrgY = y;
	HRadius = hr;
	VRadius = vr;
}

void CEllipse::Draw(CDC * pDC)
{
	// �������ʼ���������ԭ���ʵ�ָ��
	CPen pen, *pOldPen;
	pen.CreatePen(BorderType, BorderWidth, BorderColor);
	pOldPen = (CPen*)pDC->SelectObject(&pen);

	//����ˢ�Ӽ���������ԭˢ�ӵ�ָ��
	CBrush brush, *pOldBrush;
	brush.CreateHatchBrush(FillType, FillColor);
	pOldBrush = (CBrush*)pDC->SelectObject(&brush);

	//����ͼ�Σ�ͨ�����þ���������Բ��
	pDC->Ellipse(OrgX - HRadius / 2, OrgY + VRadius / 2, OrgX + HRadius / 2, OrgY - VRadius / 2);

	//ʹ�õ�ǰ���ʺ�ˢ��
	pDC->SelectObject(pOldPen);
	pDC->SelectObject(pOldBrush);
}

bool CEllipse::IsMatched(CPoint pnt)
{
	if (((OrgX - HRadius / 2) <= pnt.x) && (pnt.x <= (OrgX + HRadius / 2)) && ((OrgY - VRadius / 2) <= pnt.y) && (pnt.y <= (OrgY + VRadius / 2)))
		return true;
	else
		return false;
}

void CEllipse::Serialize(CArchive & ar)
{
	if (ar.IsStoring())
	{
		//�����ļ�
		ar << (WORD)Type;
		ar << OrgX << OrgY;
		ar << BorderColor << BorderType << BorderWidth;
		ar << FillColor << FillType;
		ar << HRadius << VRadius;
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
		ar >> HRadius >> VRadius;
	}
}

void CEllipse::SetAttribute(int nX, int nY, COLORREF nBoderColor, int nBoderType, int nBoderWidth, COLORREF nFillColor, int nFillType)
{
	OrgX = nX;
	OrgY = nY;
	BorderColor = nBoderColor;
	BorderType = nBoderType;
	BorderWidth = nBoderWidth;
	FillColor = nFillColor;
	FillType = nFillType;
}


CEllipse::~CEllipse()
{
}
