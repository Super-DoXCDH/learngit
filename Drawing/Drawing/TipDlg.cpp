// TipDlg.cpp : 实现文件

#include "stdafx.h"
#include "Drawing.h"
#include "TipDlg.h"
#include "afxdialogex.h"
#include "Resource.h"
#include "Shape.h"


IMPLEMENT_DYNAMIC(CTipDlg, CDialogEx)


CTipDlg::CTipDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_SHAPE_DLG, pParent)
	, m_ShapeX(0)
	, m_ShapeY(0)
	, m_ShapeWidth(100)
	, m_ShapeHeight(200)
	, m_LineWidth(5)
	, m_TextContent(_T(""))
	, m_Angle(0)
{

}

CTipDlg::~CTipDlg()
{
}

// 连接变量
void CTipDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	
	DDX_Text(pDX, IDC_EDIT1, m_ShapeX);
	DDX_Text(pDX, IDC_EDIT2, m_ShapeY);
	DDX_Text(pDX, IDC_EDIT4, m_ShapeWidth);
	DDX_Text(pDX, IDC_EDIT3, m_ShapeHeight);
	DDX_Control(pDX, IDC_MFCCOLORBUTTON2, m_LineColor);
	DDX_Control(pDX, IDC_MFCCOLORBUTTON1, m_FillColor);
	DDX_Control(pDX, IDC_COMBO3, m_ComboxType);
	DDX_Text(pDX, IDC_EDIT6, m_LineWidth);
	DDX_Control(pDX, IDC_LIST2, m_FillType);
	DDX_Control(pDX, IDC_LIST1, m_LineType);
	DDX_Text(pDX, IDC_EDIT7, m_TextContent);
	DDX_Text(pDX, IDC_EDIT5, m_Angle);

}


BEGIN_MESSAGE_MAP(CTipDlg, CDialogEx)
	ON_BN_CLICKED(IDC_MFCCOLORBUTTON2, &CTipDlg::OnBnClickedLinecolor)
	ON_BN_CLICKED(IDC_MFCCOLORBUTTON1, &CTipDlg::OnBnClickedFillcolor)
	ON_CBN_SELCHANGE(IDC_COMBO3, &CTipDlg::OnCbnSelchangeCombo)
	ON_BN_CLICKED(IDOK, &CTipDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// 消息处理程序


BOOL CTipDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CComboBox* pComboBox = (CComboBox*)GetDlgItem(IDC_COMBO3);
	pComboBox->AddString(L"矩形");
	pComboBox->AddString(L"椭圆");
	pComboBox->AddString(L"文本");
	pComboBox->AddString(L"圆形");
	pComboBox->AddString(L"正方形");
	pComboBox->AddString(L"正三角形");

	CListBox* pListBox = (CListBox*)GetDlgItem(IDC_LIST1);
	pListBox->AddString(L"SOLID");
	pListBox->AddString(L"DASH");
	pListBox->AddString(L"DASHDOT");

	pListBox = (CListBox*)GetDlgItem(IDC_LIST2);
	pListBox->AddString(L"SOLID");
	pListBox->AddString(L"BDIALOGAL");
	pListBox->AddString(L"CROSS");

	m_LineColor.EnableAutomaticButton(_T("默认值"), RGB(0, 0, 0));
	m_LineColor.EnableOtherButton(_T("其余颜色"));
	m_LineColor.SetColor((COLORREF)-1);
	m_LineColor.SetColumnsNumber(10);

	m_FillColor.EnableAutomaticButton(_T("默认值"), RGB(0, 0, 0));
	m_FillColor.EnableOtherButton(_T("其余颜色"));
	m_FillColor.SetColor((COLORREF)-1);
	m_FillColor.SetColumnsNumber(10);
	//设置static text content
	//ShowMsg();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CTipDlg::OnBnClickedLinecolor()
{
	// TODO: 在此添加控件通知处理程序代码
	m_nLineColor = m_LineColor.GetColor();
	if (m_nLineColor == -1)
	{
		m_nLineColor = m_LineColor.GetAutomaticColor();
	}
}


void CTipDlg::OnBnClickedFillcolor()
{
	// TODO: 在此添加控件通知处理程序代码
	m_nFillColor = m_FillColor.GetColor();
	if (m_nFillColor == -1)
	{
		m_nFillColor = m_FillColor.GetAutomaticColor();
	}
}


void CTipDlg::OnCbnSelchangeCombo()
{
	// TODO: 在此添加控件通知处理程序代码  返回的下标不是文本
	int nIndex = m_ComboxType.GetCurSel();
	if (nIndex != 2)
	{
		CStatic* pStatic1 = (CStatic*)GetDlgItem(IDC_STATIC4);
		pStatic1->ShowWindow(SW_HIDE);

		CEdit* pEdit1 = (CEdit*)GetDlgItem(IDC_EDIT7);
		pEdit1->ShowWindow(SW_HIDE);

		pStatic1 = (CStatic*)GetDlgItem(IDC_STATIC14);
		pStatic1->ShowWindow(SW_HIDE);	

		CEdit* pEdit2 = (CEdit*)GetDlgItem(IDC_EDIT5);
		pEdit2->ShowWindow(SW_HIDE);

	}
	else
	{
		CStatic* pStatic1 = (CStatic*)GetDlgItem(IDC_STATIC4);
		pStatic1->ShowWindow(SW_SHOW);

		CEdit* pEdit1 = (CEdit*)GetDlgItem(IDC_EDIT7);
		pEdit1->ShowWindow(SW_SHOW);

		pStatic1 = (CStatic*)GetDlgItem(IDC_STATIC14);
		pStatic1->ShowWindow(SW_SHOW);

		CEdit* pEdit2 = (CEdit*)GetDlgItem(IDC_EDIT5);
		pEdit2->ShowWindow(SW_SHOW);
	
	}
}


void CTipDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	m_nComboxIndex = m_ComboxType.GetCurSel();//获取下拉框的索引
	m_nLineTypeIndex = m_LineType.GetCurSel();//获取线型列表框选择内容
	m_nFilltypeIndex = m_FillType.GetCurSel();//获取填充类型列表框选择内容
	CDialogEx::OnOK();
}


