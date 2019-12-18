#include "stdafx.h"
#include "Drawing.h"
#include "Square.h"
#include "Shape.h"

IMPLEMENT_SERIAL(CSquare, CObject, 1)//实现类WSquare的序列化，指定版本为1

CSquare::CSquare()
{
	Type = (ElementType)1;//图元类型
	width = 100;//默认图形宽度为100
}

CSquare::CSquare(int x, int y, int w)
{
	Type = (ElementType)1;//图元类型
	OrgX = x;
	OrgY = y;
	width = w;
}

void CSquare::Draw(CDC* pDC)
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
	pDC->Rectangle(OrgX - width / 2, OrgY + width / 2, OrgX + width / 2, OrgY - width / 2);

	//使用当前画笔和刷子
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
		//保存文件
		ar << (WORD)Type;
		ar << OrgX << OrgY;
		ar << BorderColor << BorderType << BorderWidth;
		ar << FillColor << FillType;
		ar << width;
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
