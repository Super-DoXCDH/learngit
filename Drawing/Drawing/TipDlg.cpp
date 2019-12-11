// TipDlg.cpp : ʵ���ļ�

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
	DDX_Text(pDX, IDC_STATIC14, m_Angle);

}


BEGIN_MESSAGE_MAP(CTipDlg, CDialogEx)
	ON_BN_CLICKED(IDC_MFCCOLORBUTTON2, &CTipDlg::OnBnClickedLinecolor)
	ON_BN_CLICKED(IDC_MFCCOLORBUTTON1, &CTipDlg::OnBnClickedFillcolor)
	ON_CBN_SELCHANGE(IDC_COMBO3, &CTipDlg::OnCbnSelchangeCombo)
	ON_BN_CLICKED(IDOK, &CTipDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// ��Ϣ�������


BOOL CTipDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	CComboBox* pComboBox = (CComboBox*)GetDlgItem(IDC_COMBO3);
	pComboBox->AddString(L"����");
	pComboBox->AddString(L"��Բ");
	pComboBox->AddString(L"�ı�");
	pComboBox->AddString(L"Բ��");
	pComboBox->AddString(L"������");
	pComboBox->AddString(L"��������");

	CListBox* pListBox = (CListBox*)GetDlgItem(IDC_LIST1);
	pListBox->AddString(L"SOLID");
	pListBox->AddString(L"DASH");
	pListBox->AddString(L"DASHDOT");

	pListBox = (CListBox*)GetDlgItem(IDC_LIST2);
	pListBox->AddString(L"SOLID");
	pListBox->AddString(L"BDIALOGAL");
	pListBox->AddString(L"CROSS");

	m_LineColor.EnableAutomaticButton(_T("Ĭ��ֵ"), RGB(0, 0, 0));
	m_LineColor.EnableOtherButton(_T("������ɫ"));
	m_LineColor.SetColor((COLORREF)-1);
	m_LineColor.SetColumnsNumber(10);

	m_FillColor.EnableAutomaticButton(_T("Ĭ��ֵ"), RGB(0, 0, 0));
	m_FillColor.EnableOtherButton(_T("������ɫ"));
	m_FillColor.SetColor((COLORREF)-1);
	m_FillColor.SetColumnsNumber(10);
	//����static text content
	//ShowMsg();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}


void CTipDlg::OnBnClickedLinecolor()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_nLineColor = m_LineColor.GetColor();
	if (m_nLineColor == -1)
	{
		m_nLineColor = m_LineColor.GetAutomaticColor();
	}
}


void CTipDlg::OnBnClickedFillcolor()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_nFillColor = m_FillColor.GetColor();
	if (m_nFillColor == -1)
	{
		m_nFillColor = m_FillColor.GetAutomaticColor();
	}
}


void CTipDlg::OnCbnSelchangeCombo()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int nIndex = m_ComboxType.GetCurSel();
	if (nIndex != 2)
	{
		CStatic* pStatic1 = (CStatic*)GetDlgItem(IDC_STATIC4);
		pStatic1->ShowWindow(SW_HIDE);
		CEdit* pEdit1 = (CEdit*)GetDlgItem(IDC_EDIT7);
		pEdit1->ShowWindow(SW_HIDE);

		pStatic1 = (CStatic*)GetDlgItem(IDC_STATIC14);
		pStatic1->ShowWindow(SW_HIDE);
		pEdit1 = (CEdit*)GetDlgItem(IDC_STATIC14);
		pEdit1->ShowWindow(SW_HIDE);
	}
	else
	{
		CStatic* pStatic1 = (CStatic*)GetDlgItem(IDC_STATIC4);
		pStatic1->ShowWindow(SW_SHOW);
		CEdit* pEdit1 = (CEdit*)GetDlgItem(IDC_EDIT7);
		pEdit1->ShowWindow(SW_SHOW);

		CStatic* pStatic2 = (CStatic*)GetDlgItem(IDC_STATIC14);
		pStatic2->ShowWindow(SW_SHOW);
		CEdit* pEdit2 = (CEdit*)GetDlgItem(IDC_STATIC14);
		pEdit2->ShowWindow(SW_SHOW);
	}
}


void CTipDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_nComboxIndex = m_ComboxType.GetCurSel();//��ȡ�����������
	m_nLineTypeIndex = m_LineType.GetCurSel();//��ȡ�����б��ѡ������
	m_nFilltypeIndex = m_FillType.GetCurSel();//��ȡ��������б��ѡ������
	CDialogEx::OnOK();
}


void CTipDlg::ShowMsg() {

	GetDlgItem(IDC_STATIC11)->SetWindowText(L"ͼԪ����");
	GetDlgItem(IDC_STATIC10)->SetWindowText(L"��״����");
	GetDlgItem(IDC_STATIC3)->SetWindowText(L"ԭ��X");
	GetDlgItem(IDC_STATIC1)->SetWindowText(L"ԭ��Y");
	GetDlgItem(IDC_STATIC2)->SetWindowText(L"���");
	GetDlgItem(IDC_STATIC5)->SetWindowText(L"�߶�");
	GetDlgItem(IDC_STATIC4)->SetWindowText(L"�ı�");
	GetDlgItem(IDC_STATIC14)->SetWindowText(L"�Ƕ�");
	GetDlgItem(IDC_STATIC22)->SetWindowText(L"�߿���");
	GetDlgItem(IDC_STATIC6)->SetWindowText(L"�߿�");
	GetDlgItem(IDC_STATIC12)->SetWindowText(L"��ɫ");
	GetDlgItem(IDC_STATIC7)->SetWindowText(L"����");
	GetDlgItem(IDC_STATIC8)->SetWindowText(L"�����");
	GetDlgItem(IDC_STATIC9)->SetWindowText(L"�����");
	GetDlgItem(IDC_STATIC13)->SetWindowText(L"���ɫ");

}

