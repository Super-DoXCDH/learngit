#include "stdafx.h"
#include "Rectangle.h"


IMPLEMENT_SERIAL(CRectangle, CObject, 1)//ʵ����WSquare�����л���ָ���汾Ϊ1

CRectangle::CRectangle()
{
	Type = (ElementType)2;//ͼԪ����
	Width = 200;//Ĭ��ͼ�ο��Ϊ200���߶�Ϊ100
	Height = 100;
}

CRectangle::CRectangle(int x, int y, int w, int h)
{
	Type = (ElementType)2;//ͼԪ����
	OrgX = x;
	OrgY = y;
	Width = w;
	Height = h;
}

void CRectangle::Draw(CDC* pDC)
{
	//�������ʼ���������ԭ���ʵ�ָ��
	CPen pen, *pOldPen;
	pen.CreatePen(BorderType, BorderWidth, BorderColor);
	pOldPen = (CPen*)pDC->SelectObject(&pen);

	//����ˢ�Ӽ���������ԭˢ�ӵ�ָ��
	CBrush brush, *pOldBrush;
	brush.CreateHatchBrush(FillType, FillColor);
	pOldBrush = (CBrush*)pDC->SelectObject(&brush);

	//����ͼ��
	pDC->Rectangle(OrgX - Width / 2, OrgY + Height / 2, OrgX + Width / 2, OrgY - Height / 2);

	//ʹ�õ�ǰ���ʺ�ˢ��
	pDC->SelectObject(pOldPen);
	pDC->SelectObject(pOldBrush);
}

bool CRectangle::IsMatched(CPoint pnt)
{
	if (((OrgX - Width / 2) <= pnt.x) && (pnt.x <= (OrgX + Width / 2)) && ((OrgY - Height / 2) <= pnt.y) && (pnt.y <= (OrgY + Height / 2)))
		return true;
	else
		return false;
}

void CRectangle::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		//�����ļ�
		ar << (WORD)Type;
		ar << OrgX << OrgY;
		ar << BorderColor << BorderType << BorderWidth;
		ar << FillColor << FillType;
		ar << Width << Height;
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
		ar >> Width >> Height;
	}
}

void CRectangle::SetAttribute(int nX, int nY, COLORREF nBoderColor, int nBoderType, int nBoderWidth, COLORREF nFillColor, int nFillType)
{
	OrgX = nX;
	OrgY = nY;
	BorderColor = nBoderColor;
	BorderType = nBoderType;
	BorderWidth = nBoderWidth;
	FillColor = nFillColor;
	FillType = nFillType;
}

CRectangle::~CRectangle()
{
}
