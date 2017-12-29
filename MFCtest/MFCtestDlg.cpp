
// MFCtestDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCtest.h"
#include "MFCtestDlg.h"
#include "afxdialogex.h"
#include "systemtray.h"
#include <iostream>
#include <string>
#include <WinSvc.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CSystemTray m_stMyProg;
char defaultServiceName[]=TEXT("SHARP_BS_SERVER8");
char serviceName[128];
char szPath[144];
SC_HANDLE hSC ;
SC_HANDLE hSvc ;
SERVICE_STATUS status;
CMenu trayMenu;  
 

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCtestDlg 对话框




CMFCtestDlg::CMFCtestDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMFCtestDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCtestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCtestDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CMFCtestDlg::OnBnClickedOk)
	ON_MESSAGE(WM_TRAY_MSG, OnTrayMsg)
	ON_BN_CLICKED(IDCANCEL, &CMFCtestDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCtestDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMFCtestDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CMFCtestDlg::OnBnClickedButton3)
	ON_COMMAND(ID_32773, &CMFCtestDlg::On32773)
	ON_COMMAND(ID_32774, &CMFCtestDlg::On32774)
	ON_COMMAND(ID_32775, &CMFCtestDlg::On32775)
END_MESSAGE_MAP()

// CMFCtestDlg 消息处理程序

BOOL CMFCtestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);
	trayMenu.LoadMenu(IDR_MENU1);
	m_stMyProg.Create(m_hWnd,::LoadIcon(theApp.m_hInstance,MAKEINTRESOURCE(IDRETRY)), _T("This is a SystemTray example"));
	
	if (__argc>1){	
		strcat(serviceName,__argv[1]); 
	} else {
		strcat(serviceName,defaultServiceName); 
	}
	SetWindowText(serviceName);
	GetCurrentDirectory(144,szPath);

    hSC=::OpenSCManager( NULL,NULL, GENERIC_EXECUTE);
	
	if( hSC == NULL)
    {
       SetDlgItemText(IDC_PATH,"打开服务管理失败");
    }
	hSvc = ::OpenService( hSC,serviceName,SERVICE_START | SERVICE_QUERY_STATUS | SERVICE_STOP);
	if( hSvc == NULL)
    {
       SetDlgItemText(IDC_PATH,"打开服务管理失败");
    } else {
		if( ::QueryServiceStatus( hSvc, &status) == FALSE)
		{
			SetDlgItemText(IDC_PATH,"获取服务状态失败");
			::CloseServiceHandle( hSvc);
			::CloseServiceHandle( hSC);
        
		} else {
			setStatus(status.dwCurrentState);
		}
	}
	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}
	
	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFCtestDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMFCtestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMFCtestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CMFCtestDlg::OnClose(){
	ShowWindow(SW_HIDE);
}


void CMFCtestDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	ShowWindow(SW_HIDE);
	//CDialogEx::OnOK();
}
LRESULT CMFCtestDlg::OnTrayMsg(WPARAM wParam, LPARAM lParam)
{
    switch (lParam)
        {
          case WM_LBUTTONDOWN:{
			  ShowWindow(SW_SHOW);
			  break;
		  }
		  case WM_RBUTTONDOWN:{
			CMenu *pPopUp = trayMenu.GetSubMenu(0);  
			CPoint pt;  
			GetCursorPos(&pt);  
			SetForegroundWindow();  
			pPopUp->TrackPopupMenu(TPM_RIGHTBUTTON, pt.x, pt.y, this);  
			PostMessage(WM_NULL, 0, 0); 
			}
			  break;
          default:
            break;
        }
    return 0;
}

void CMFCtestDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}


void CMFCtestDlg::OnBnClickedButton1()
{
	//WinExec("net start SHARP_BS_SERVER8",SW_HIDE);
	if( ::StartService( hSvc, NULL, NULL) == FALSE){
		SetDlgItemText(IDC_PATH,"服务启动失败");
		return;
	} else {
		SetDlgItemText(IDC_PATH,"服务启动中");
	}
	while( ::QueryServiceStatus( hSvc, &status) == TRUE)
        {
            ::Sleep( status.dwWaitHint);
            if( status.dwCurrentState == SERVICE_RUNNING)
            {
                setStatus(status.dwCurrentState);
				return;
            }
        }
}


void CMFCtestDlg::OnBnClickedButton2()
{
	//WinExec("net stop SHARP_BS_SERVER8",SW_HIDE);
	if( ::ControlService( hSvc,SERVICE_CONTROL_STOP, &status) == FALSE)
        {
			SetDlgItemText(IDC_PATH,"获取服务状态失败");
        }else {
			setStatus(status.dwCurrentState);
		}
	while( ::QueryServiceStatus( hSvc, &status) == TRUE)
        {
            ::Sleep( status.dwWaitHint);
            if( status.dwCurrentState == SERVICE_STOPPED)
            {
                setStatus(status.dwCurrentState);
				return;
            }
        }
}


void CMFCtestDlg::OnBnClickedButton3()
{
	OnBnClickedButton2();
	OnBnClickedButton1();
}

void CMFCtestDlg::setStatus(DWORD curStatus){
        CMenu *pPopUp = trayMenu.GetSubMenu(0); 
		CHAR str[20]="状态：";
		switch (status.dwCurrentState){
			case SERVICE_STOPPED:{
				strcat(str,"服务已停止");
				SetDlgItemText(IDC_PATH,str);
				pPopUp->ModifyMenuA(0,MF_BYPOSITION,ID_32776,str);
				}
			break;
			case SERVICE_START_PENDING:{
				strcat( str,"服务启动中");
				SetDlgItemText(IDC_PATH,str);
				pPopUp->ModifyMenuA(0,MF_BYPOSITION,ID_32776,str);
				}
			break;
			case SERVICE_STOP_PENDING:{
				strcat( str,"服务停止中");
				SetDlgItemText(IDC_PATH,str);
				pPopUp->ModifyMenuA(0,MF_BYPOSITION,ID_32776,str);
				}
			break;
			case SERVICE_RUNNING:{
				strcat( str,"服务已启动");
				SetDlgItemText(IDC_PATH,str);
				pPopUp->ModifyMenuA(0,MF_BYPOSITION,ID_32776,str);
				}
			break;			
			case SERVICE_CONTINUE_PENDING:{
				strcat( str,"服务启动中");
				SetDlgItemText(IDC_PATH,str);
				pPopUp->ModifyMenuA(0,MF_BYPOSITION,ID_32776,str);
				}
			break;			
			case SERVICE_PAUSE_PENDING:{
				strcat( str,"服务暂停中");
				SetDlgItemText(IDC_PATH,str);
				pPopUp->ModifyMenuA(0,MF_BYPOSITION,ID_32776,str);
				}
			break;			
			case SERVICE_PAUSED:{
				strcat( str,"服务已暂停");
				SetDlgItemText(IDC_PATH,str);
				pPopUp->ModifyMenuA(0,MF_BYPOSITION,ID_32776,str);
				}
			break;
			}
}

void CMFCtestDlg::On32773()
{
	 CMFCtestDlg::OnBnClickedButton1();
}


void CMFCtestDlg::On32774()
{
	CMFCtestDlg::OnBnClickedButton2();
}


void CMFCtestDlg::On32775()
{
	CMFCtestDlg::OnBnClickedButton3();
}
