#pragma once

#include "Observer.h"

#include "../../ClientBiz/ClientBiz/ClientBiz.h"
#include "SL_Rpc_Message.h"
#include "../../ClientBiz/Internal/MessageMapping.h"
//#include "atlsync.h"
#include "afxmt.h"
#include "utils.h"
#include<iostream>


#define BUSINESSMESSAGE_TRAVERSELIST -10000
#define WM_BUSINESSMESSAGE WM_USER + 3000


class CBusinessMessageItem
{
public:
	CBusinessMessageItem()
	{
		m_nMessageType = 0;
		m_nEerrorCode = 0;
		m_pMessage = NULL;
		m_nListType = 0;
	};

	~CBusinessMessageItem()
	{
		if(m_pMessage)
		{
			if(BUSINESSMESSAGE_TRAVERSELIST != m_nMessageType)
			{
				//ClientBiz::instance()->release_message( m_nMessageType, m_pMessage);	
			}
		}
	};

public:
	int m_nMessageType;			//���Ϊ -10000�ţ���ô�����Ϣ������Ա�б���Ϣ
	int m_nEerrorCode;			//�������
	void *m_pMessage;			//������Ϣ���ݣ���Ҫ����m_nMessageTypeȥ����
	short m_nListType;			//��m_nMessageTypeΪ-10000�ŵ�ʱ����õ���

};


class CBusinessMessage;
class CBusinessMessageObserver
{
public:
	CBusinessMessageObserver(){};
	~CBusinessMessageObserver(){};
	virtual void UpdateBusinessMessage(CBusinessMessage *pObserable, void *arg) = 0;

};



class CBusinessMessage: public CInstanceLockBase
{
public:
	DECLARE_SINGLETON(CBusinessMessage)

	CBusinessMessage(void);
	~CBusinessMessage(void);

	BOOL InitClientBizCallBack();
	

public:
	static int UIProc(int message_type, int error_code, void *message);
	//static int Traverselist(short list_type, void *message=NULL);	

	static void AddObserver(CBusinessMessageObserver *pObserver);				//���ӹ۲��ߣ������ط�ֻ��Ҫ�õ���һ�Ժ���

	static void ClearChanged();													
	static int  CountObservers();
	static bool HasChanged();
	static void DeleteObserver(CBusinessMessageObserver *pObserver);
	static void DeleteObservers();												//ɾ���۲��ߣ������ط�ֻ��Ҫ�õ���һ�Ժ���

	static void NotifyObservers();
	static void NotifyObservers(void *arg);
	static void SetChanged();

private:
	static list< CBusinessMessageObserver* > m_observers;
	static bool   m_bChanged;
	
	static CCriticalSection *m_pSection;

};

