#include "stdafx.h"
#include "Text.h"

IMPLEMENT_SERIAL(CText, CObject, 1)//ʵ����WText�����л���ָ���汾Ϊ1

CText::CText(int x, int y, CString content)
{
	Type = (ElementType)6;//ͼԪ����
	OrgX = x;
	OrgY = y;
	Content = content;
	//Angle = angle;
}



void CText::Draw(CDC * pDC)
{
	//��������ת�Ƕȵ�����
	LOGFONT logfont;
	lstrcpy(logfont.lfFaceName, _T("����_GB2312"));
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
		//�����ļ�
		ar << (WORD)Type;
		ar << OrgX << OrgY;
		ar << BorderColor << BorderType << BorderWidth;
		ar << FillColor << FillType;
		ar << Content << Angle;
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
