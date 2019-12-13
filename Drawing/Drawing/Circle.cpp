#include "stdafx.h"
#include "Circle.h"


IMPLEMENT_SERIAL(CCircle, CObject, 1)//实现类WSquare的序列化，指定版本为1

CCircle::CCircle(int x, int y, int r)
{
	Type = (ElementType)3;//图元类型
	OrgX = x;
	OrgY = y;
	Radius = r;
}

void CCircle::Draw(CDC * pDC)
{
	//创建画笔及用来保存原画笔的指针
	CPen pen, *pOldPen;
	pen.CreatePen(BorderType, BorderWidth, BorderColor);
	pOldPen = (CPen*)pDC->SelectObject(&pen);

	//创建刷子及用来保存原刷子的指针
	CBrush brush, *pOldBrush;
	brush.CreateHatchBrush(FillType, FillColor);
	pOldBrush = (CBrush*)pDC->SelectObject(&brush);

	//绘制图形（通过外置矩形来画椭圆）
	pDC->Ellipse(OrgX - Radius / 2, OrgY + Radius / 2, OrgX + Radius / 2, OrgY - Radius / 2);

	//使用当前画笔和刷子
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
		//保存文件
		ar << (WORD)Type;
		ar << OrgX << OrgY;
		ar << BorderColor << BorderType << BorderWidth;
		ar << FillColor << FillType;
		ar << Radius;
	}
	else
	{
		//读取文件
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
