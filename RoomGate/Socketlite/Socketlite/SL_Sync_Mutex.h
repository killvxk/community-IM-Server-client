#ifndef SOCKETLITE_SYNC_MUTEX_H
#define SOCKETLITE_SYNC_MUTEX_H

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
    #pragma once
#endif
#include "SL_Sync_Macros.h"
#include "SL_Singleton.h"

//SL_Sync_ThreadMutex����ƽ̨������:
//  1)��windows��,ͬһ�߳̿��Զ����������SL_Sync_ThreadMutex.lock(��EnterCriticalSection api)
//  2)��linux��,Ĭ�����ʱͬһ�̲߳��ܶ��������SL_Sync_ThreadMutex.lock(��pthread_mutex_lock api)

class SOCKETLITE_API SL_Sync_ThreadMutex
{
public:
    inline SL_Sync_ThreadMutex()
    { 
        SL_SYNC_THREADMUTEX_INIT(&mutex_); 
    }

    inline SL_Sync_ThreadMutex(bool recursive)
    { 
#ifndef SOCKETLITE_OS_WINDOWS        
        if (recursive)
        {
            pthread_mutexattr_t attr;
            pthread_mutexattr_init(&attr);
            if (recursive)
            {
                pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
            }        
            pthread_mutex_init(&mutex_, &attr);
            pthread_mutexattr_destroy(&attr);
        }
        else
        {
            SL_SYNC_THREADMUTEX_INIT(&mutex_);
        }
#else
        SL_SYNC_THREADMUTEX_INIT(&mutex_);
#endif
    }

    inline ~SL_Sync_ThreadMutex()
    { 
        SL_SYNC_THREADMUTEX_DESTROY(&mutex_);
    }

    inline void lock()
    { 
        SL_SYNC_THREADMUTEX_LOCK(&mutex_);
    }

    inline void unlock()
    { 
        SL_SYNC_THREADMUTEX_UNLOCK(&mutex_);
    }

    inline bool trylock()
    {
        SL_SYNC_THREADMUTEX_TRYLOCK_RETURN(&mutex_);
    }

    inline SL_SYNC_MUTEX_T* handle()
    {
        return &mutex_;
    }

private:
    SL_Sync_ThreadMutex(const SL_Sync_ThreadMutex &);
    SL_Sync_ThreadMutex& operator=(const SL_Sync_ThreadMutex &);

private:
    SL_SYNC_MUTEX_T mutex_;
};
typedef SL_Sync_ThreadMutex SL_Sync_Mutex;

class SOCKETLITE_API SL_Sync_NullMutex
{
public:
    inline SL_Sync_NullMutex() 
    {
    }

    inline ~SL_Sync_NullMutex() 
    {
    }

    inline static void lock() 
    {
    }

    inline static void unlock() 
    {
    }

    inline static bool trylock() 
    { 
        return false;
    }

    inline static SL_SYNC_MUTEX_T* handle() 
    { 
        return NULL; 
    }

private:
    SL_Sync_NullMutex(const SL_Sync_NullMutex &);
    SL_Sync_NullMutex& operator=(const SL_Sync_NullMutex &);
};
typedef SL_Singleton<SL_Sync_NullMutex> SL_Sync_NullMutex_T;

#endif

