#include "stdafx.h"
#include "Drawing.h"
#include "Square.h"
#include "Shape.h"

IMPLEMENT_SERIAL(CSquare, CObject, 1)//ʵ����WSquare�����л���ָ���汾Ϊ1

CSquare::CSquare()
{
	Type = (ElementType)1;//ͼԪ����
	width = 100;//Ĭ��ͼ�ο��Ϊ100
}

CSquare::CSquare(int x, int y, int w)
{
	Type = (ElementType)1;//ͼԪ����
	OrgX = x;
	OrgY = y;
	width = w;
}

void CSquare::Draw(CDC* pDC)
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
	pDC->Rectangle(OrgX - width / 2, OrgY + width / 2, OrgX + width / 2, OrgY - width / 2);

	//ʹ�õ�ǰ���ʺ�ˢ��
	pDC->SelectObject(pOldPen);
	pDC->SelectObject(pOldBrush);
}

bool CSquare::IsMatched(CPoint pnt)
{
	if (((OrgX - width / 2) <= pnt.x) && (pnt.x <= (OrgX + width / 2)) && ((OrgY - width / 2) <= pnt.y) && (pnt.y <= (OrgY + width / 2)))
		return true;
	else
		return false;
}

void CSquare::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		//�����ļ�
		ar << (WORD)Type;
		ar << OrgX << OrgY;
		ar << BorderColor << BorderType << BorderWidth;
		ar << FillColor << FillType;
		ar << width;
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
		ar >> width;
	}
}

void CSquare::SetAttribute(int nX, int nY, COLORREF nBorderColor, int nBorderType, int nBorderWidth, COLORREF nFillColor, int nFillType)
{
	OrgX = nX;
	OrgY = nY;
	BorderColor = nBorderColor;
	BorderType = nBorderType;
	BorderWidth = nBorderWidth;
	FillColor = nFillColor;
	FillType = nFillType;
}

CSquare::~CSquare()
{
}
