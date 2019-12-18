#include "stdafx.h"
#include "Triangle.h"
#include <math.h>

IMPLEMENT_SERIAL(CTriangle, CObject, 1)//实现类WSquare的序列化，指定版本为1
CTriangle::CTriangle()
{
	Type = (ElementType)5;//图元类型
	Length = 100;
}

CTriangle::CTriangle(int x, int y, int length)
{
	Type = (ElementType)5;//图元类型
	OrgX = x;
	OrgY = y;
	Length = length;
}

void CTriangle::Draw(CDC * pDC)
{
	// 创建画笔及用来保存原画笔的指针
	CPen pen, *pOldPen;
	pen.CreatePen(BorderType, BorderWidth, BorderColor);
	pOldPen = (CPen*)pDC->SelectObject(&pen);

	//创建刷子及用来保存原刷子的指针
	CBrush brush, *pOldBrush;
	brush.CreateHatchBrush(FillType, FillColor);
	pOldBrush = (CBrush*)pDC->SelectObject(&brush);

	//绘制图形
	double x1 = double(OrgX), y1 = double(OrgY) + double(Length) / SQRT3;
	double x2 = double(OrgX) - double(Length) / 2, y2 = double(OrgY) - double(Length) / (2 * SQRT3);
	double x3 = double(OrgX) + double(Length) / 2, y3 = double(OrgY) - double(Length) / (2 * SQRT3);
	CPoint points[3] = { CPoint(double(x1), double(y1)), CPoint(double(x2), double(y2)), CPoint(double(x3), double(y3)) };
	pDC->Polygon(points, 3);

	//使用当前画笔和刷子
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
		//保存文件
		ar << (WORD)Type;
		ar << OrgX << OrgY;
		ar << BorderColor << BorderType << BorderWidth;
		ar << FillColor << FillType;
		ar << Length;
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
