#include "stdafx.h"
#include "Text.h"

IMPLEMENT_SERIAL(CText, CObject, 1)//实现类WText的序列化，指定版本为1

CText::CText(int x, int y, CString content)
{
	Type = (ElementType)6;//图元类型
	OrgX = x;
	OrgY = y;
	Content = content;
	//Angle = angle;
}



void CText::Draw(CDC * pDC)
{
	//创建带旋转角度的字体
	LOGFONT logfont;
	lstrcpy(logfont.lfFaceName, _T("楷体_GB2312"));
	logfont.lfWeight = 10;
	logfont.lfWidth = 40;
	logfont.lfHeight = 70;
	logfont.lfEscapement = Angle;
	logfont.lfUnderline = FALSE;
	logfont.lfItalic = FALSE;
	logfont.lfStrikeOut = FALSE;
	logfont.lfCharSet = GB2312_CHARSET;
	HFONT hFont, *hOldFont;
	hFont = CreateFontIndirect(&logfont);
	hOldFont = (HFONT*)pDC->SelectObject(hFont);
	pDC->SetBkColor(FillColor);
	pDC->SetTextColor(BorderColor);
	pDC->TextOutW(OrgX, OrgY, Content);
	pDC->SelectObject(hOldFont);
}

bool CText::IsMatched(CPoint pnt)
{
		return false;
}

void CText::Serialize(CArchive & ar)
{
	if (ar.IsStoring())
	{
		//保存文件
		ar << (WORD)Type;
		ar << OrgX << OrgY;
		ar << BorderColor << BorderType << BorderWidth;
		ar << FillColor << FillType;
		ar << Content << Angle;
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
		ar >> Content >> Angle;
	}
}

void CText::SetAttribute(int nX, int nY, COLORREF nBorderColor, int nBorderType, int nBorderWidth, COLORREF nFillColor, int nFillType)
{
	OrgX = nX;
	OrgY = nY;
	BorderColor = nBorderColor;
	BorderType = nBorderType;
	BorderWidth = nBorderWidth;
	FillColor = nFillColor;
	FillType = nFillType;
}


CText::~CText()
{

}
