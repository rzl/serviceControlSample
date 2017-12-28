#pragma once
#ifndef __CSYSTEMTRAY_H
#define __CSYSTEMTRAY_H

#include "shellapi.h"

#define WM_TRAY_MSG WM_USER + 0x01                  //�Զ�����Ϣ�����Խ����������̵ķ���
class CSystemTray
{
public:
    CSystemTray(void);
public:
    ~CSystemTray(void);
    void Destroy();
    BOOL Create(HWND hParent, HICON hIcon, LPCTSTR szToolTip);  //hParent �ǽ���WM_TRAY_MSG��Ϣ�Ĵ���
    BOOL ModifyIcon(HICON hIcon);
    BOOL ModifyToolTipText(LPCTSTR szToolTip);
    BOOL ModifyBalloonText(LPCTSTR szTitle, LPCTSTR szInfo);
    BOOL ModifyBalloonIcon(HICON hIcon);
    BOOL SetFocus();
    //BOOL AnimateIcon(HICON *pIconArray, UINT nSize, DWORD dwTimeInter);
private:
    void Wait(int nSeconds);
    HWND m_hParent;
    HICON m_hIconTray, m_hIconBalloon;
    NOTIFYICONDATA m_nidSystemTray;
};

#endif

