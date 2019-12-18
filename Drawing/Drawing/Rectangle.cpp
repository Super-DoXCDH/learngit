#include "stdafx.h"
#include "Rectangle.h"


IMPLEMENT_SERIAL(CRectangle, CObject, 1)//实现类WSquare的序列化，指定版本为1

CRectangle::CRectangle()
{
	Type = (ElementType)2;//图元类型
	Width = 200;//默认图形宽度为200，高度为100
	Height = 100;
}

CRectangle::CRectangle(int x, int y, int w, int h)
{
	Type = (ElementType)2;//图元类型
	OrgX = x;
	OrgY = y;
	Width = w;
	Height = h;
}

void CRectangle::Draw(CDC* pDC)
{
	//创建画笔及用来保存原画笔的指针
	CPen pen, *pOldPen;
	pen.CreatePen(BorderType, BorderWidth, BorderColor);
	pOldPen = (CPen*)pDC->SelectObject(&pen);

	//创建刷子及用来保存原刷子的指针
	CBrush brush, *pOldBrush;
	brush.CreateHatchBrush(FillType, FillColor);
	pOldBrush = (CBrush*)pDC->SelectObject(&brush);

	//绘制图形
	pDC->Rectangle(OrgX - Width / 2, OrgY + Height / 2, OrgX + Width / 2, OrgY - Height / 2);

	//使用当前画笔和刷子
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
		//保存文件
		ar << (WORD)Type;
		ar << OrgX << OrgY;
		ar << BorderColor << BorderType << BorderWidth;
		ar << FillColor << FillType;
		ar << Width << Height;
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
