#pragma once  
class CHttp  
{  
public:  
     CHttp(void);  
    ~CHttp(void);  
    virtual bool put(CString inbuff,CString *outbuff);  
    virtual bool get(CString url,CString *result);  
  
    virtual bool Myconnect(unsigned long ip,CString port);  
    virtual void BulidCookie(CString urlsc);   
  
    CString cookie;   
	CString referer;  
  
  
protected:  
    DWORD dwTimeOut;  
    SOCKET MySocket;  
    bool m_bConnect;  
   
    CString host;    
  
    int m_nContent;  
    bool chunked;  
public:
	virtual int Init(void);
	virtual int UInit(void);
};  