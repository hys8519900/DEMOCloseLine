
// DemoCloseLineDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DemoCloseLine.h"
#include "DemoCloseLineDlg.h"
#include "afxdialogex.h"
#include <vector>


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CDemoCloseLineDlg �Ի���




CDemoCloseLineDlg::CDemoCloseLineDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDemoCloseLineDlg::IDD, pParent)
	, m_nStockCode(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDemoCloseLineDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_nStockCode);
	DDV_MinMaxInt(pDX, m_nStockCode, 0, 999999);
}

BEGIN_MESSAGE_MAP(CDemoCloseLineDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
//	ON_WM_SHOWWINDOW()
ON_WM_SIZE()
ON_BN_CLICKED(IDC_BUTTON1, &CDemoCloseLineDlg::OnBnClickedButton1)
ON_WM_MOUSEMOVE()
ON_EN_SETFOCUS(IDC_EDIT1, &CDemoCloseLineDlg::OnEnSetfocusEdit1)
ON_EN_KILLFOCUS(IDC_EDIT1, &CDemoCloseLineDlg::OnEnKillfocusEdit1)
END_MESSAGE_MAP()


// CDemoCloseLineDlg ��Ϣ�������

BOOL CDemoCloseLineDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	SetTimer(ID_TIMER,1,NULL);   //1ms�ػ�һ��PIC�ؼ�
	m_nDataPos=0;
	((CEdit*)GetDlgItem(IDC_EDIT1))->SetWindowText("�������Ʊ����");

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CDemoCloseLineDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CDemoCloseLineDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CDemoCloseLineDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CDemoCloseLineDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CDC*  pDC;
	CRect rect;

	pDC=GetDlgItem(IDC_PIC_MAIN)->GetDC();
	GetDlgItem(IDC_PIC_MAIN)->GetClientRect(rect);
	ASSERT_VALID(pDC);
	CMemDC* pDCmem=new CMemDC(*pDC,rect);
	CDC&   memDC=pDCmem->GetDC();
	////////////////////////////////////////////
	//use memDC draw

	memDC.FillSolidRect(rect,RGB(255,255,255));
	CPen pen1(PS_SOLID,1,RGB(0,0,0));
	memDC.SelectObject(pen1);

	CRect LineRect=rect;           //�ϰ벿�ֿ��С
	LineRect.left+=40;
	LineRect.bottom-= (rect.bottom-rect.top)*3/7;

	CRect ColRect=rect;			//�°벿�ֿ��С
	ColRect.top=LineRect.bottom+5;
	ColRect.left+=40;
	
	memDC.Rectangle(LineRect);
	memDC.Rectangle(ColRect);   //�������������

	//��������
	long Tperwidth=LineRect.Height()/5;
	long Dperwidth=ColRect.Height()/5;
	//����������
	CPen penCoordAxis(PS_SOLID,1,RGB(240,230,200));
	memDC.SelectObject(penCoordAxis);
	for(int i=1;i<=4;++i)
	{
		memDC.MoveTo(40+2,i*Tperwidth-2);
		memDC.LineTo(LineRect.right+2,i*Tperwidth-2);  //top y

		memDC.MoveTo(40+2,ColRect.top+i*Dperwidth-2);
		memDC.LineTo(ColRect.right+2,ColRect.top+i*Dperwidth-2); //down y

		memDC.MoveTo(rect.Width()/5*i,2);
		memDC.LineTo(rect.Width()/5*i,rect.bottom-2); //x
	}

	if(!m_data.IsEmpty())
	{
		//���ϰ벿������ͼ
		double max,min;

		CPen pen2(PS_SOLID,1,RGB(0,0,240));
		memDC.SelectObject(pen2);
		POINT aryPoint[100];             //100����
		m_nDataPos=m_data.ToPoint(aryPoint,100,LineRect.Width(),LineRect.Height(),40,0,m_Mouse_x,max,min);
		//TRACE("%d\n",m_nDataPos);
		memDC.Polyline(aryPoint,100);


		//���°벿����״ͼ
		CBrush brush;
		brush.CreateSolidBrush(RGB(0,0,240));
		memDC.SelectObject(brush);
		CPoint aryPointBrush[100];            //100����
		m_nDataPos=m_data.ToPoint(aryPointBrush,100,ColRect.Width(),ColRect.Height(),40,ColRect.top,m_Mouse_x,max,min);
		for(int i=0;i<100;++i)
		{
			memDC.Rectangle(aryPointBrush[i].x-1,aryPointBrush[i].y,aryPointBrush[i].x+1,rect.bottom);
		}


		//���̶�����
		if(!m_data.IsEmpty())
		{
			CFont m_Font;
			m_Font.CreatePointFont(100,"����",pDC);
			memDC.SelectObject(&m_Font);
			memDC.SetTextColor(RGB(0,0,0));
			memDC.SetBkMode(TRANSPARENT);
			for(int i=0;i<6;++i)
			{
				CString m_Text;
				m_Text.Format("%4.2lf",max-(max-min)/5*i);
				memDC.TextOut(0,(LineRect.Height()/5-2)*i-2,m_Text);
				memDC.TextOut(0,ColRect.top+(ColRect.Height()/5-2)*i-2,m_Text);
			}
		}


		//if mouse in the IDC_PIC_MAIN ��ʮ��
		CPen pen3(PS_SOLID,1,RGB(190,190,190));
		memDC.SelectObject(pen3);
		if(m_Mouse_x>0 && m_Mouse_y>0)
		{
			memDC.MoveTo(m_Mouse_x,0);
			memDC.LineTo(m_Mouse_x,rect.bottom); //����

			if(!m_data.IsEmpty())  //������ʱ�������
			{
				memDC.MoveTo(40,aryPoint[m_nDataPos].y);
				memDC.LineTo(LineRect.right,aryPoint[m_nDataPos].y);
			}
			else
			{
				memDC.MoveTo(40,m_Mouse_y);
				memDC.LineTo(LineRect.right,m_Mouse_y);
			}

		}
	}
	


	////////////////////////////////////////////

	delete pDCmem;

	ReleaseDC(pDC);

	//CDialogEx::OnTimer(nIDEvent);
}


//void CDemoCloseLineDlg::OnShowWindow(BOOL bShow, UINT nStatus)
//{
//	CDialogEx::OnShowWindow(bShow, nStatus);
//
//	// TODO: �ڴ˴������Ϣ����������
//}


void CDemoCloseLineDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	if(nType==SIZE_MINIMIZED)
	{

	}
	else if (nType==SIZE_MAXIMIZED)
	{
		CRect rect;
		CWnd *pChildWnd=GetDlgItem(IDC_PIC_MAIN);
		GetClientRect(rect);
		if(pChildWnd)
		{
			pChildWnd->MoveWindow(rect.left,rect.top,rect.Width(),rect.Height(),TRUE);
		}

		
		CDemoCloseLineDlg::OnTimer(ID_TIMER);
	}
	else if (nType==SIZE_RESTORED && GetDlgItem(IDC_PIC_MAIN)!=NULL) //NOT INITIALIZE
	{
	    // TODO: �ڴ˴������Ϣ����������
			//�������ڿؼ��洰�ڴ�С�ı�
			CRect rect;
			CWnd *pChildWnd=GetDlgItem(IDC_PIC_MAIN);
			GetClientRect(rect);
			if(pChildWnd)
			{
				pChildWnd->MoveWindow(rect.left,rect.top,2*rect.Width()/3,rect.Height(),TRUE);
			}

			int idnamesLT[4]={IDC_EDIT1,IDC_BUTTON1,IDC_STATIC_NAME,IDC_STATIC_DATE};
			for(int i=0,toplus=0;
				i<4;++i,toplus=toplus+40)
			{
				pChildWnd=GetDlgItem(idnamesLT[i]);
				GetClientRect(rect);
				if(pChildWnd)
				{
					pChildWnd->MoveWindow(rect.left+2*rect.Width()/3,rect.top+toplus,rect.Width()/3,20,TRUE);
				}
			}

			int idnamesLD[2][6]={{IDC_STATIC1,IDC_STATIC2,IDC_STATIC3,IDC_STATIC4,IDC_STATIC5,IDC_STATIC6},
			{IDC_STATIC_OPEN,IDC_STATIC_HIGH,IDC_STATIC_LOW,IDC_STATIC_CLOSE,IDC_STATIC_VOLUME,IDC_STATIC_ADJCLOSE}};
			for(int i=0,toplus=160;i<6;++i,toplus=toplus+40)
			{
				pChildWnd=GetDlgItem(idnamesLD[0][i]);
				CWnd* pChildWnd2=GetDlgItem(idnamesLD[1][i]);
				GetClientRect(rect);
				if(pChildWnd)
				{
					pChildWnd->MoveWindow(rect.left+2*rect.Width()/3,rect.top+toplus,rect.Width()/9,20,TRUE);
					pChildWnd2->MoveWindow(rect.left+2*rect.Width()/3+rect.Width()/6,rect.top+toplus,rect.Width()/6-2,20,TRUE);
				}

			}

			CDemoCloseLineDlg::OnTimer(ID_TIMER);
			
	}
}

void CDemoCloseLineDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);

	if(1<=m_nStockCode &&m_nStockCode<=999999)
	{
		CString url="http://ichart.yahoo.com/table.csv?s=";
		CString Respond;

		CString inArea,sinaArea;
		if(m_nStockCode>=600000)
		{
			inArea="SS";
			sinaArea="sh";
		}
		else
		{
			inArea="sz";
			sinaArea="sz";
		}


		CTime curTime=CTime::GetCurrentTime();
		url.Format("http://ichart.yahoo.com/table.csv?s="
			"%06d.%s&a=04&b=19&c=2013&d=%02d&e=%02d&f=%d&g=d",m_nStockCode,inArea,
			curTime.GetMonth()-1,curTime.GetDay(),curTime.GetYear());  //format url

		CHttp   http;
		http.Init();

		http.get(url,&Respond);    //use socket call STOCK API

		if(FALSE==m_data.ResToDeque(Respond)) //format Respond to deque CDqeueData 
		{
			AfxMessageBox("û���ҵ��ô���Ĺ�Ʊ");
		}

		

		//��ù�Ʊ����
		url.Format("http://hq.sinajs.cn/list=%s%06d",sinaArea,m_nStockCode);
		http.get(url,&Respond);

		if(Respond.Compare("")!=0)
		{
			CString temp;
			temp=Respond.Left(Respond.Find("\""));
			Respond.Replace(temp+"\"","");

			m_data.m_StockName=Respond.Left(Respond.Find(","));

			//��ʾ��Ʊ����
			SetDlgItemText(IDC_STATIC_NAME,m_data.m_StockName);
		}
		
	}
	else
	{
		m_nStockCode=0;
	}
	
	
}


void CDemoCloseLineDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	//ClientToScreen(&point);
	CRect rect;
	GetDlgItem(IDC_PIC_MAIN)->GetClientRect(rect);
	//GetDlgItem(IDC_PIC_MAIN)->ClientToScreen(rect);
	CPoint drawpoint=point;
	drawpoint.x-=40;
	if(rect.PtInRect(drawpoint))   //����Ƿ��ڷ�Χ֮��
	{
		m_Mouse_x=point.x;
		m_Mouse_y=point.y;
		if(!m_data.IsEmpty() && !IsZoomed())  //�������Ҵ��ڲ������
		{
			CString temp;
			SetDlgItemText(IDC_STATIC_DATE,m_data.m_Data[m_nDataPos].m_strDate);
			temp.Format("%4.2lf",m_data.m_Data[m_nDataPos].m_dOpen);
			SetDlgItemText(IDC_STATIC_OPEN,temp);
			temp.Format("%4.2lf",m_data.m_Data[m_nDataPos].m_dHigh);
			SetDlgItemText(IDC_STATIC_HIGH,temp);
			temp.Format("%4.2lf",m_data.m_Data[m_nDataPos].m_dLow);
			SetDlgItemText(IDC_STATIC_LOW,temp);
			temp.Format("%4.2lf",m_data.m_Data[m_nDataPos].m_dClose);
			SetDlgItemText(IDC_STATIC_CLOSE,temp);
			temp.Format("%llu",m_data.m_Data[m_nDataPos].m_i64Volume);
			SetDlgItemText(IDC_STATIC_VOLUME,temp);
			temp.Format("%4.2lf",m_data.m_Data[m_nDataPos].m_dAdjClose);
			SetDlgItemText(IDC_STATIC_ADJCLOSE,temp);

		}
	}
	else
	{
		m_Mouse_x=m_Mouse_y=0;
	}
	CDialogEx::OnMouseMove(nFlags, point);

}


void CDemoCloseLineDlg::OnEnSetfocusEdit1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	((CEdit*)GetDlgItem(IDC_EDIT1))->SetWindowText("");
}


void CDemoCloseLineDlg::OnEnKillfocusEdit1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	
	//((CEdit*)GetDlgItem(IDC_EDIT1))->SetWindowText("�����Ʊ����");
}



void CDemoCloseLineDlg::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���
	OnBnClickedButton1();
	//CDialogEx::OnOK();
}
