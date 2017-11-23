#ifndef SOCKETLITE_CIRCULAR_QUEUE_H
#define SOCKETLITE_CIRCULAR_QUEUE_H

//ѭ������(���ζ���): ��ֻ��һ���̺߳�һд�߳�ʱ���ɲ����������������ڲ�����һ����

#include "SL_DataType.h"
#include "SL_Sync_Guard.h"
#include <vector>

template <typename T, typename TSyncMutex>
class SL_Circular_Queue
{
public:
    SL_Circular_Queue()
    {
    }

    ~SL_Circular_Queue()
    {
    }    

protected:
    TSyncMutex      mutex_;
    std::vector<T>  queue_;
    size_t          read_pos_;
    size_t          write_pos_;
};

#endif
