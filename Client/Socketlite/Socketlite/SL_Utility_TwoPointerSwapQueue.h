#ifndef SOCKETLITE_UTILITY_TWOPOINTER_SWAP_QUEUE_H
#define SOCKETLITE_UTILITY_TWOPOINTER_SWAP_QUEUE_H
#include <algorithm>
#include <queue>
#include "SL_Sync_Mutex.h"
#include "SL_Sync_SpinMutex.h"

//˫ָ�뽻������
//�ر�˵��:
//1)TQueue�������ṩ�ӿڣ�push_back/pop_front/front/empty
//2)Ŀǰstl�����з���: list/deque

template <typename TValue, typename TQueue, typename TPushMutex=SL_Sync_NullMutex, typename TPopMutex=SL_Sync_NullMutex>
class SL_Utility_TwoPointerSwapQueue
{
public:
    inline SL_Utility_TwoPointerSwapQueue()
    {
        queue_active_   = &queue1_;
        queue_standby_  = &queue2_;
    }

    inline SL_Utility_TwoPointerSwapQueue(uint max_size)
    {
        queue_active_   = &queue1_;
        queue_standby_  = &queue2_;
    }

    inline ~SL_Utility_TwoPointerSwapQueue()
    {
    }

    inline int push(const TValue &value)
    {
        push_mutex_.lock();
        queue_standby_->push_back(value);
        push_mutex_.unlock();
        return 1;
    }

    inline int pop(TValue &value)
    {
        pop_mutex_.lock();
        if (!queue_active_->empty())
        {
            value = queue_active_->front();
            queue_active_->pop_front();
            pop_mutex_.unlock();
            return 1;
        }
        pop_mutex_.unlock();
        return -1;
    }

    inline bool swap_pointer()
    {
        if (!queue_standby_->empty())
        {
            push_mutex_.lock();
            std::swap(queue_standby_, queue_active_);
            push_mutex_.unlock();
            return true;
        }
        return false;
    }

public:
    TQueue      *queue_active_;
    TQueue      *queue_standby_;
    TQueue      queue1_;
    TQueue      queue2_;
    TPushMutex  push_mutex_;
    TPopMutex   pop_mutex_;
};

#endif

