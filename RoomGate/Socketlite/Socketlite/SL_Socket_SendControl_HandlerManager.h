#ifndef SOCKETLITE_SOCKET_SEND_CONTROL_HANDLER_MANAGER_H
#define SOCKETLITE_SOCKET_SEND_CONTROL_HANDLER_MANAGER_H

#include <list>
#include <vector>
#include "SL_Sync_Atomic.h"
#include "SL_Sync_SpinMutex.h"
#include "SL_Sync_Mutex.h"
#include "SL_Sync_Condition.h"
#include "SL_Thread.h"
#include "SL_Socket_Handler.h"

//����:��α���ģ����SL_Socket_SendControl_Handler<>��ָ��?
//�������1:
//      �����д��SL_Socket_Handler���ָ��,
//      ͨ��dynamic_cast<SL_Socket_SendControl_Interface*>(handler), 
//      ��dynamic_cast���������ͳ����Ч�ʣ��ڸ���c++�ı������϶������,һ����˵,
//      ʹ�õ�dynamic_cast�Ĳ���Ч�ʽ���15%�����Ǻ������ġ����������ĳ����ܹ�����dynamic_cast,�ǾͲ�Ҫ��.
//      ��:std::list<SL_Socket_Handler*>   sendcontrol_list_;
//�������2:
//      �����д��<SL_Socket_Handler*, SL_Socket_SendControl_Interface*>�Ľṹ��
//      ���ڴ�ռ��Ҫ��Щ(sizeof(void*)

class SL_Socket_SendControl_Interface;
class SL_Socket_SendControl_HandlerManager
{
public:
    //ϵͳ��ǰʱ���,����ϵͳʱ�䱻�û��ı��Ӱ��(���ڼ��ٵ�ǰʱ���ϵͳ����) ��λ: us ֻ�����ڼ�ʱ
    static uint64 current_timestamp_us_;

    //ϵͳ��ǰʱ��(���ڼ���ȡ��ǰʱ��ϵͳ����) ��λ: us
    static uint64 current_time_us_;

    //ϵͳ��ǰʱ���,����ϵͳʱ�䱻�û��ı��Ӱ��(���ڼ��ٵ�ǰʱ���ϵͳ����) ��λ: ms ֻ�����ڼ�ʱ
    static uint64 current_timestamp_;

    //ϵͳ��ǰʱ��(���ڼ��ٵ�ǰʱ��ϵͳ����) ��λ: s
    static uint64 current_time_;

public:
    SL_Socket_SendControl_HandlerManager();
    virtual ~SL_Socket_SendControl_HandlerManager();

    int     open(int  thread_number=1, 
                 int  send_block_size=65536, 
                 int  iovec_count=1024, 
                 int  keepalive_time_ms=0, 
                 int  send_delaytime_ms=1, 
                 int  scan_waittime_us=1000, 
                 int  close_delaytime_ms=60000, 
                 bool timedwait_signal=true,
                 bool direct_send_flag=true);

    int     close();
    int     event_loop(int timeout_ms=10);

    int     add_handler(SL_Socket_Handler *handler, SL_Socket_SendControl_Interface *sendcontrol);
    int     wakeup_thread(int thread_index);
    size_t  handler_size();

    static uint64 get_current_timestamp()
    {
        return current_timestamp_;
    }

    static uint64 get_current_time()
    {
        return current_time_;
    }

    static uint64 get_current_timestamp_us()
    {
        return current_timestamp_us_;
    }

    static uint64 get_current_time_us()
    {
        return current_time_us_;
    }

protected:
    virtual int assign_thread();

private:
#ifdef SOCKETLITE_OS_WINDOWS
    static unsigned int WINAPI send_proc(void *arg);
#else
    static void* send_proc(void *arg);
#endif

private:
    SL_IOVEC    *iovec_;
    int         iovec_count_;           //ϵͳ����writev����iovec����ĸ���
    int         thread_number_;         //�߳���(��<=0,��ʾ������ר�ŷ����߳�)
    int         send_block_size_;       //�������ݿ�Ĵ�С(ÿ����һ�η���һ��)
    uint        keepalive_time_ms_;     //keepalive���
    uint        send_delaytime_ms_;     //�����ӳ�ʱ��(ms)
    uint        scan_waittime_us_;      //ɨ��һ���,waitʱ��(us)
    uint        close_delaytime_ms_;    //�ر��ӳ�ʱ��(ms), �������ر�socket, �ͻ��˿����ղ�������͵Ĳ�������

    typedef std::pair<SL_Socket_Handler*, SL_Socket_SendControl_Interface* > ITEM_SENDCONTROL;
    struct SendThread
    {
        void   *parent;
        uint    index;                  //�߳����̼߳���������
        uint    handlers_list_size;     //handler���ϵĴ�С
        uint    temp_handlers_size;     //��ʱ���ϵĴ�С

        std::list<ITEM_SENDCONTROL>     handlers_list;
        SL_Thread                       thread;
        SL_Sync_SpinMutex               mutex;
        std::list<ITEM_SENDCONTROL>     temp1_handlers;
        std::list<ITEM_SENDCONTROL>     temp2_handlers;
        std::list<ITEM_SENDCONTROL>     *temp_handlers_active;
        std::list<ITEM_SENDCONTROL>     *temp_handlers_standby;
        
        //˯�߻��ѿ���
        SL_Sync_ThreadMutex             timedwait_mutex;
        SL_Sync_Condition               timedwait_condition;
        SL_Sync_Atomic_Int32            timedwait_flag;
    };
    std::vector<SendThread* > send_threads_;
    int  next_thread_index_;

    //���ڿ����Ƿ񴥷������ź�(�򴥷������źűȽϺ�ʱ)
    bool timedwait_signal_;

    //ֱ�ӷ��ͱ�ʶ(���߼��߳�ֱ�ӷ�������,���ڷ����߳�,ʡȥ���ݿ������߳��л�)
    bool direct_send_flag_;

    template <typename TSocketHandler, typename TByteBuffer, typename TSyncMutex, typename TEncryptCipher, typename TDecryptCipher> friend class SL_Socket_SendControl_Handler;
};

#endif

