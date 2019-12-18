#pragma once
#include "Shape.h"
class CText : public CShape
{
protected:
	CString Content;//文本的内容
	
public:
	CText();
	CText(int x, int y, CString content);
	void Draw(CDC* pDC);//绘制文本函数
	bool IsMatched(CPoint pnt);
	void Serialize(CArchive& ar);
	void SetAttribute(int nX, int nY, COLORREF nBorderColor, int nBorderType, int nBorderWidth, COLORREF nFillColor, int nFillType);
	~CText();

	DECLARE_SERIAL(CText)//声明类WText是支持序列化
};

