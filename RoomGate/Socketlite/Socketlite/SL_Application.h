#ifndef SOCKETLITE_APPLICATION_H
#define SOCKETLITE_APPLICATION_H
#include "SL_DataType.h"
#include "SL_Sync_SpinMutex.h"

template <typename T>
class SL_Application
{
public:

    //ʹ��Singleton����ģʽLazy Evaluation����ʵ����
    static T* instance()
    {
        //ʹ��˫��鼼�� - double check
        if (NULL == app_)
        {
            mutex_.lock();
            if (NULL == app_)
            {
                app_ = new T();
            }
            mutex_.unlock();
        }
        return app_;
    }
    
    static void uninstance()
    {
        mutex_.lock();
        if (NULL != app_)
        {
            delete app_;
            app_ = NULL;
        }
        mutex_.unlock();
    }

    uint64 get_current_timestamp_us()
    {
        return current_timestamp_us_;
    }

    uint64 get_current_time_us()
    {
        return current_time_us_;
    }

    void set_current_timestamp_us(uint64 current_timestamp_us)
    {
        current_timestamp_us_ = current_timestamp_us;
    }

    void set_current_time_us(uint64 current_time_us)
    {
        current_time_us_ = current_time_us;
    }

    //���غ���Ϊ��λ��ʱ���
    uint64 get_current_timestamp()
    {
        return current_timestamp_us_ / 1000;
    }

    //������Ϊ��λ�ĵ�ǰʱ��
    uint64 get_current_time()
    {
        return current_time_us_ / 1000000LL;
    }

protected:
    SL_Application()
        : current_timestamp_us_(0)
        , current_time_us_(0)
    {
    }

    virtual ~SL_Application()
    {
    }
    
    //��������init����
    virtual int init()
    {
        return 0;
    }

    //��������fini����
    virtual int fini()
    {
        return 0;
    }

protected:
    //ϵͳ��ǰʱ���,����ϵͳʱ�䱻�û��ı��Ӱ��(���ڼ��ٵ�ǰʱ���ϵͳ����) ��λ: us ֻ�����ڼ�ʱ
    uint64                      current_timestamp_us_;

    //ϵͳ��ǰʱ��(���ڼ���ȡ��ǰʱ��ϵͳ����) ��λ: us
    uint64                      current_time_us_;

    static SL_Sync_SpinMutex    mutex_;
    static T                    *app_;
};

template<typename T>
SL_Sync_SpinMutex SL_Application<T>::mutex_;

template<typename T>
T* SL_Application<T>::app_ = NULL;

#endif

