#pragma once
#include "stdafx.h"

#if !defined(AFX_SHAPE_H__0800ED02_2AF6_43A7_892D_38DF1FE9C573__INCLUDED_)
#define AFX_SHAPE_H__0800ED02_2AF6_43A7_892D_38DF1FE9C573__INCLUDED_

#if _MSC_VER > 1000

#endif // _MSC_VER > 1000
enum ElementType{
	NOTSET, SQUARE,
	RECTANGLE,
	CIRCLE,
	ELLIPSE,
	TRIANGLE,
	TEXT };

class CShape : public CObject
{
public:
	ElementType Type;//ͼԪ����
	int OrgX;//���ԭ�������
	int OrgY;
	int Angle;

	COLORREF BorderColor;//ͼ�α߿����ɫ
	int BorderType;//ͼ�α߿����ͣ�ʵ�ߣ����ߣ�����ߣ�
	int BorderWidth;//ͼ�α߿���

	COLORREF FillColor;//ͼ�������ɫ
	int FillType;//ͼ��������ͣ�ʵ�ģ�˫�Խǣ� ʮ�ֽ��棩
public:
	CShape();
	virtual ~CShape();
	//���麯��
	virtual void Draw(CDC* pDC) = 0;//����ͼԪ����
	virtual bool IsMatched(CPoint pnt) = 0;//�ж������Ƿ�����ͼ����
	virtual void Serialize(CArchive& ar) = 0;//���л�����
	virtual void SetAttribute(int nX, int nY, COLORREF nBoderColor, int nBoderType, int BoderWidth, COLORREF FillColor, int nFillType) = 0;//�ı�ͼ�����Ա���
};


#endif // !defined(AFX_SHAPE_H__0800ED02_2AF6_43A7_892D_38DF1FE9C573__INCLUDED_)

