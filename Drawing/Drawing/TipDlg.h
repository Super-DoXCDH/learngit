#pragma once


class CTipDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CTipDlg)

public:
	CTipDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CTipDlg();

	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SHAPE_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedLinecolor();
	afx_msg void OnBnClickedFillcolor();
	afx_msg void OnCbnSelchangeCombo();
	afx_msg void OnBnClickedOk();
	virtual void CTipDlg::ShowMsg();
public:
	int m_ShapeX;
	int m_ShapeY;

	int m_ShapeWidth;
	int m_ShapeHeight;

	//自定义的变量
	int m_nComboxIndex;
	int m_nLineTypeIndex;
	int m_nFilltypeIndex;
	COLORREF m_nLineColor;
	COLORREF m_nFillColor;

	CComboBox m_ComboxType;

	UINT m_LineWidth;
	CListBox m_LineType;
	CMFCColorButton m_LineColor;

	CListBox m_FillType;
	CMFCColorButton m_FillColor;

	CString m_TextContent;
	int m_Angle;
	afx_msg void OnStnClickedStatic7();
};
