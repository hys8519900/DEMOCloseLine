
// DemoCloseLineDlg.h : ͷ�ļ�
//

#pragma once

#include "CloseLineData.h"
#include "Http.h"

// CDemoCloseLineDlg �Ի���
class CDemoCloseLineDlg : public CDialogEx
{
// ����
public:
	CDemoCloseLineDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_DEMOCLOSELINE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

//member
public:
	CDqeueData m_data;
private:
	long m_Mouse_x,m_Mouse_y;
	int  m_nDataPos;

// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
//	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	int m_nStockCode;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnEnSetfocusEdit1();
	afx_msg void OnEnKillfocusEdit1();
	virtual void OnOK();
};
