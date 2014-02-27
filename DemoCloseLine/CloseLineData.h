#pragma once

#include <deque>

class DataDay
{
//member
public:
	CString m_strDate;
	int    m_nYear;
	int    m_nMonth;
	int    m_nDay;
	double m_dOpen;
	double m_dHigh;
	double m_dLow;
	double m_dClose;
	INT64   m_i64Volume;
	double m_dAdjClose;

//function
public:
    void get(CString line);

};

class CDqeueData
{
//member
public:
	UINT m_count;
public:
	std::deque<DataDay> m_Data;
	CString m_StockName;

public:
	CDqeueData();
	~CDqeueData();
	CDqeueData(CString Res);



//function
public:
	 bool ResToDeque(CString Res);
	 bool GetMaxClose(double& maxClose);
	 bool GetMinClose(double& minClose);
	 int  ToPoint(LPPOINT points,int numpoint,long nWidth,long nHeight,long nSx,long nSy,long MouseX,double &max,double &min);
	 bool IsEmpty();
};