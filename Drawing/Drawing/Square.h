
#if !defined(AFX_SQUARE_H__A6E7CDBA_2B9E_48B1_AD01_67EAE87D362A__INCLUDED_)
#define AFX_SQUARE_H__A6E7CDBA_2B9E_48B1_AD01_67EAE87D362A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Shape.h"
#include "stdafx.h"
					 //正方形类CSquare
class CSquare : public CShape
{
protected:
	int width;//正方形的宽
public:
	CSquare(int x, int y, int width);
	void Draw(CDC*pDC);
	bool IsMatched(CPoint pnt);
	void Serialize(CArchive& ar);
	void SetAttribute(int nX, int nY, COLORREF nBorderColor, int nBorderType, int BorderWidth, COLORREF FillColor, int nFillType);
	~CSquare();

	DECLARE_SERIAL(CSquare)//声明类WSquare是支持序列化
};

#endif // !defined(AFX_SQUARE_H__A6E7CDBA_2B9E_48B1_AD01_67EAE87D362A__INCLUDED_)
