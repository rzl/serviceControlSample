
// MFCtestDlg.h : ͷ�ļ�
//

#pragma once


// CMFCtestDlg �Ի���
class CMFCtestDlg : public CDialogEx
{
	
// ����
public:
	CMFCtestDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MFCTEST_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��
	

// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
};
