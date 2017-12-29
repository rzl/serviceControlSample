
// MFCtestDlg.h : 头文件
//

#pragma once


// CMFCtestDlg 对话框
class CMFCtestDlg : public CDialogEx
{
	
// 构造
public:
	CMFCtestDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MFCTEST_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
	

// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnClose();;
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnBnClickedOk();
	afx_msg LRESULT OnTrayMsg(WPARAM  wParam, LPARAM  lParam);
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	void setStatus(DWORD curStatus);
	afx_msg void On32773();
	afx_msg void On32774();
	afx_msg void On32775();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
