#include "StdAfx.h" 
#include "CloseLineData.h"

//转换字符串到格式
void DataDay::get(CString line)
{
	if(line.GetLength()>3)
	{
		sscanf_s(line.GetBuffer(line.GetLength()),"%d-%d-%d,%lf,%lf,%lf,%lf,%llu,%lf",
			&m_nYear,&m_nMonth,&m_nDay,&m_dOpen,&m_dHigh,&m_dLow,&m_dClose,&m_i64Volume,&m_dAdjClose);
		m_strDate.Format("%d-%d-%d",m_nYear,m_nMonth,m_nDay);
		line.ReleaseBuffer();
	}
}


CDqeueData::CDqeueData()
	: m_count(0)
{

}

CDqeueData::~CDqeueData()
{

}

CDqeueData::CDqeueData(CString Res)
{
	ResToDeque(Res);
}

//function  change CString Res(HTTP Respond) To member List of Class DataDay(one day's data)
bool CDqeueData::ResToDeque(CString Res)
{
	CString next;
	CString CVSHead="Date,Open,High,Low,Close,Volume,Adj Close";

	if(!Res.IsEmpty())
	{
		//CString HttpHead=Res.Left(Res.Find("HTTP/1.1 "));   //HttpHead
		Res.Replace("HTTP/1.1 ","");
		if(Res.Left(Res.Find(" "))=="404")
		{
			return false;
		}

		m_Data.clear();
		DataDay data;

		next=Res.Left(Res.Find(CVSHead));
		Res.Replace(next+CVSHead+"\n",""); //Remove til data

		while(1) 
		{
			next=Res.Left(Res.Find("\n"));
			Res.Replace(next+"\n",""); //Read one line
			if(next.Compare("")!=0)    //Not Empty
			{
				data.get(next);
				m_Data.push_back(data);   //Format CString (cvs) to Class DataDay and push_back in list
				++m_count;
			}
			else
			{
				break;
			}
		} 
		return true;
	}
	return false;
}

//收盘价中最大的
bool CDqeueData::GetMaxClose(double& maxClose)
{
	std::deque<DataDay>::iterator iter=m_Data.begin();
	if(iter!=m_Data.end())
	{
		for(std::deque<DataDay>::iterator iter=m_Data.begin();iter!=m_Data.end();++iter)
		{
			if(iter->m_dClose>maxClose)
			{
				maxClose=iter->m_dClose;
			}
		}
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

//收盘价中最小的
bool CDqeueData::GetMinClose(double& minClose)
{
	std::deque<DataDay>::iterator iter=m_Data.begin();
	if(iter!=m_Data.end())
	{
		minClose=iter->m_dClose;
		for(std::deque<DataDay>::iterator iter=m_Data.begin();iter!=m_Data.end();++iter)
		{
			if(minClose>iter->m_dClose)
			{
				minClose=iter->m_dClose;
			}
		}
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

//转换数据到Point数组 返回当前鼠标所在的数据位置 
int CDqeueData::ToPoint(LPPOINT points,int numpoint,long nWidth,long nHeight,long nSx,long nSy,long MouseX,
	double &max,double &min)
{
	int nDataPos=0;
	if((SIZE_T)numpoint<=m_Data.size())
	{
		max=0.0f;
		min=m_Data[0].m_dClose;    //min初始值设为第0个
		for(int i=0;i<numpoint;++i)
		{
			if(max<m_Data[i].m_dClose)  
				max=m_Data[i].m_dClose;
			if(min>m_Data[i].m_dClose)
				min=m_Data[i].m_dClose;
		}

		for(int i=0;i<numpoint;++i)
		{
			points[i].x=nSx+(double)nWidth/(double)numpoint*i;
			if(i>0 && points[i-1].x<=MouseX && points[i].x>=MouseX)
				nDataPos=i;
			points[i].y=nSy+(1-(m_Data[i].m_dClose-min)/(max-min))*nHeight;
		}
	}
	return nDataPos;
}

//数据是否为空
bool CDqeueData::IsEmpty()
{
	if(m_Data.size()==0)
	{
		return true;
	}
	else
	{
		return false;
	}
}