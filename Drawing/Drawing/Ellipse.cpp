#include "stdafx.h"
#include "Ellipse.h"

IMPLEMENT_SERIAL(CEllipse, CObject, 1)//实现类WSquare的序列化，指定版本为1

CEllipse::CEllipse(int x, int y, int hr, int vr)
{
	Type = (ElementType)4;//图元类型
	OrgX = x;
	OrgY = y;
	HRadius = hr;
	VRadius = vr;
}

void CEllipse::Draw(CDC * pDC)
{
	// 创建画笔及用来保存原画笔的指针
	CPen pen, *pOldPen;
	pen.CreatePen(BorderType, BorderWidth, BorderColor);
	pOldPen = (CPen*)pDC->SelectObject(&pen);

	//创建刷子及用来保存原刷子的指针
	CBrush brush, *pOldBrush;
	brush.CreateHatchBrush(FillType, FillColor);
	pOldBrush = (CBrush*)pDC->SelectObject(&brush);

	//绘制图形（通过外置矩形来画椭圆）
	pDC->Ellipse(OrgX - HRadius / 2, OrgY + VRadius / 2, OrgX + HRadius / 2, OrgY - VRadius / 2);

	//使用当前画笔和刷子
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
		//保存文件
		ar << (WORD)Type;
		ar << OrgX << OrgY;
		ar << BorderColor << BorderType << BorderWidth;
		ar << FillColor << FillType;
		ar << HRadius << VRadius;
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
