#pragma once





// singleton
#define DECLARE_SINGLETON(x)	\
	static x *m_pInstance;			\
	static x *Instance()			\
{								\
	if (!m_pInstance)			\
	m_pInstance = new x;	\
	return m_pInstance;			\
}								\
	static void ReleaseInstance()	\
{								\
	delete m_pInstance;			\
	m_pInstance = NULL;			\
}

#define IMPLEMENT_SINGLETON(x)	x *x::m_pInstance = NULL;



// usage: #pragma mesage(__FILELINE__, "message-text")
#define __STR2__(x) #x
#define __STR1__(x) __STR2__(x)
#define __FILELINE__ __FILE__ "("__STR1__(__LINE__)") : "


class CInstanceLockBase
{
public:
	CRITICAL_SECTION m_cs;
	void Lock() { EnterCriticalSection(&m_cs); }
	void Unlock() { LeaveCriticalSection(&m_cs); }

} ;

class CInstanceLock
{
public:
	CInstanceLockBase * _pObj;

public:
	CInstanceLock(CInstanceLockBase * pObj)
	{
		_pObj = pObj;
		if (NULL != _pObj)
			_pObj->Lock();
	}
	~CInstanceLock()
	{
		if (NULL != _pObj)
			_pObj->Unlock();
	}
};



/*
CSIDL_BITBUCKET   ����վ    
CSIDL_CONTROLS   �������    
CSIDL_DESKTOP   Windows   ����Desktop    
CSIDL_DESKTOPDIRECTORY   Desktop��Ŀ¼    
CSIDL_DRIVES   �ҵĵ���    
CSIDL_FONTS   ����Ŀ¼    
CSIDL_NETHOOD   �����ھ�    
CSIDL_NETWORK   �����ھ�����Ŀ¼    
CSIDL_PERSONAL   �ҵ��ĵ�    
CSIDL_PRINTERS   ��ӡ��    
CSIDL_PROGRAMS   ������    
CSIDL_RECENT   ����򿪵��ĵ�    
CSIDL_SENDTO   �����͵����˵���    
CSIDL_STARTMENU   �����������˵���    
CSIDL_STARTUP   ����Ŀ¼    
CSIDL_TEMPLATES   �ĵ�ģ�� 
*/
wstring GetSysDirectory(int nCsidl);

LPCTSTR GetModuleFilePath();

int duMessageBox(HWND hWnd, LPCTSTR lpText, LPCTSTR lpCaption, UINT uType);


UINT GetRandom(UINT nLowerLimit, UINT UpperLimit);

wstring&   replace_all(wstring& str,const wstring& old_value,const wstring& new_value);

wstring&   replace_all_distinct(wstring& str,const wstring& old_value,const wstring& new_value);