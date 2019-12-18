
// DrawingView.cpp : CDrawingView 类的实现
//
#include "stdafx.h"
#include "Shape.h"
#include "Square.h"
#include "Rectangle.h"
#include "Ellipse.h"
#include "Circle.h"
#include "Triangle.h"
#include "Text.h"
#include "TipDlg.h"

// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "Drawing.h"
#endif

#include "DrawingDoc.h"
#include "DrawingView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDrawingView

IMPLEMENT_DYNCREATE(CDrawingView, CScrollView)

BEGIN_MESSAGE_MAP(CDrawingView, CScrollView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CScrollView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
//	ON_WM_MBUTTONDBLCLK()
ON_WM_MBUTTONDOWN()
//ON_WM_MBUTTONDBLCLK()
ON_WM_RBUTTONDBLCLK()
END_MESSAGE_MAP()

// CDrawingView 构造/析构

CDrawingView::CDrawingView()
{
	// TODO: 在此处添加构造代码

}

CDrawingView::~CDrawingView()
{
}

BOOL CDrawingView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CScrollView::PreCreateWindow(cs);
}

// CDrawingView 绘制

void CDrawingView::OnDraw(CDC* pDC)
{

	CDrawingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	// TODO:  在此处为本机数据添加绘制代码
	for (int i = 0; i < pDoc->m_Elements.GetCount(); i++)
	{
		CShape* p = (CShape*)pDoc->m_Elements[i];
		p->Draw(pDC);
	}
}




void CDrawingView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: 计算此视图的合计大小
	sizeTotal.cx = sizeTotal.cy = 100;
	SetScrollSizes(MM_TEXT, sizeTotal);
}


// CDrawingView 打印

BOOL CDrawingView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CDrawingView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CDrawingView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CDrawingView 诊断

#ifdef _DEBUG
void CDrawingView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CDrawingView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CDrawingDoc* CDrawingView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDrawingDoc)));
	return (CDrawingDoc*)m_pDocument;
}
#endif //_DEBUG


// CDrawingView 消息处理程序


void CDrawingView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CDrawingDoc* pDoc = GetDocument();
	CClientDC	dc(this);
	CPoint pntLogical = point;
	OnPrepareDC(&dc);
	dc.DPtoLP(&pntLogical);//DP->LP进行转换 

	if ((nFlags&MK_CONTROL) == MK_CONTROL)//Ctrl键按下
	{
		CTipDlg dlg;
		
		//记录鼠标按下的位置
		dlg.m_ShapeX = pntLogical.x;
		dlg.m_ShapeY = pntLogical.y;

		//焦点是否在确定键上，弹出对话框

		if (dlg.DoModal() == IDOK)
		{
			//获取用户修改位置的坐标
			pntLogical.x = dlg.m_ShapeX;
			pntLogical.y = dlg.m_ShapeY;

			//获取用户输入的宽度和高度
			int width = dlg.m_ShapeWidth;
			int height = dlg.m_ShapeHeight;

			//根据对话框用户选择的下拉框的选项索引绘制对应的图形
			switch (dlg.m_nComboxIndex)
			{
			case 0:
			{
				CRectangle* p = NULL;
				p = new CRectangle(pntLogical.x, pntLogical.y, width, height);

				p->BorderWidth = dlg.m_LineWidth;
				p->BorderType = dlg.m_nLineTypeIndex;
				p->BorderColor = dlg.m_nLineColor;

				p->FillType = dlg.m_nFilltypeIndex;
				p->FillColor = dlg.m_nFillColor;

				pDoc->m_Elements.Add(p);
				break;
			}
			case 1:
			{
				CEllipse * p;
				p = new CEllipse(pntLogical.x, pntLogical.y, width, height);

				p->BorderWidth = dlg.m_LineWidth;
				p->BorderType = dlg.m_nLineTypeIndex;
				p->BorderColor = dlg.m_nLineColor;

				p->FillType = dlg.m_nFilltypeIndex;
				p->FillColor = dlg.m_nFillColor;

				pDoc->m_Elements.Add(p);
				break;
			}
			case 2:
			{
				CText *p = NULL;
				CString content = dlg.m_TextContent;
				p = new CText(pntLogical.x, pntLogical.y, content);
				p->Angle = dlg.m_Angle;
				p->BorderWidth = dlg.m_LineWidth;
				p->BorderType = dlg.m_nLineTypeIndex;
				p->BorderColor = dlg.m_nLineColor;

				p->FillType = dlg.m_nFilltypeIndex;
				p->FillColor = dlg.m_nFillColor;


				pDoc->m_Elements.Add(p);
				break;
			}
			case 3:
			{
				CCircle *p = NULL;
				p = new CCircle(pntLogical.x, pntLogical.y, width);

				p->BorderWidth = dlg.m_LineWidth;
				p->BorderType = dlg.m_nLineTypeIndex;
				p->BorderColor = dlg.m_nLineColor;

				p->FillType = dlg.m_nFilltypeIndex;
				p->FillColor = dlg.m_nFillColor;

				pDoc->m_Elements.Add(p);
				break;
			}
			case 4:
			{
				CSquare* p = NULL;
				p = new CSquare(pntLogical.x, pntLogical.y, width);

				p->BorderWidth = dlg.m_LineWidth;
				p->BorderType = dlg.m_nLineTypeIndex;
				p->BorderColor = dlg.m_nLineColor;

				p->FillType = dlg.m_nFilltypeIndex;
				p->FillColor = dlg.m_nFillColor;

				pDoc->m_Elements.Add(p);
				break;
			}
			case 5:
			{
				CTriangle* p = NULL;
				p = new CTriangle(pntLogical.x, pntLogical.y, width);

				p->BorderWidth = dlg.m_LineWidth;
				p->BorderType = dlg.m_nLineTypeIndex;
				p->BorderColor = dlg.m_nLineColor;

				p->FillType = dlg.m_nFilltypeIndex;
				p->FillColor = dlg.m_nFillColor;

				pDoc->m_Elements.Add(p);
				break;
			}
			default:
				MessageBox(L"请您选择图形类型！");
				break;
			}
			Invalidate();//刷新窗口
		}

	}
	else
	{
		//未按下Ctrl键时左击，则逐个比较，看是否命中图元
		int i;
		CShape* p;
		for (i = 0; i < pDoc->m_Elements.GetCount(); i++)
		{
			p = (CShape*)pDoc->m_Elements[i];
			if (p->IsMatched(pntLogical))
			{
				//修改图元属性，从图元属性值里面取值赋值给对话框的变量
				CTipDlg dlg;

				dlg.m_ShapeX = p->OrgX;
				dlg.m_ShapeY = p->OrgY;

				if (dlg.DoModal() == IDOK)
				{
					//利用改了以后对话框中图元的属性更新到文档图元数组的对象中
					//共有属性修改，如果修改非共有属性则要每个单独考虑
					p->OrgX = dlg.m_ShapeX;
					p->OrgY = dlg.m_ShapeY;

					p->BorderColor = dlg.m_LineColor.GetColor();
					p->BorderWidth = dlg.m_LineWidth;
					p->BorderType = dlg.m_nLineTypeIndex;

					p->FillColor = dlg.m_FillColor.GetColor();
					p->FillType = dlg.m_nFilltypeIndex;

					p->SetAttribute(p->OrgX, p->OrgY, p->BorderColor, p->BorderType, p->BorderWidth, p->FillColor, p->FillType);

				}
				Invalidate();//刷新窗口
			}
		}
	}
	CScrollView::OnLButtonDown(nFlags, point);
}


//鼠标中键双击删除匹配图像
void CDrawingView::OnRButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CDrawingDoc* pDoc = GetDocument();
	int i;
	CShape* p;
	CClientDC	dc(this);
	CPoint pntLogical = point;
	OnPrepareDC(&dc);
	dc.DPtoLP(&pntLogical);//DP->LP进行转换 


	for (i = 0; i < pDoc->m_Elements.GetCount(); i++)
	{
		p = (CShape*)pDoc->m_Elements[i];
		if (p->IsMatched(pntLogical))
		{
			AfxMessageBox(L"删除图元");

			pDoc->m_Elements.RemoveAt(i);
		}
	}
	Invalidate();//刷新窗口

	CScrollView::OnRButtonDblClk(nFlags, point);
}



