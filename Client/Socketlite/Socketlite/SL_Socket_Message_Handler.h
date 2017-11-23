#ifndef SOCKETLITE_SOCKET_MESSAGE_HANDLER_H
#define SOCKETLITE_SOCKET_MESSAGE_HANDLER_H

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
    #pragma once
#endif
#include "SL_ByteBuffer.h"
#include "SL_Socket_Handler.h"
#include "SL_Socket_Source.h"

//SL_Socket_Message_Handler���������ݰ��ĸ�ʽ: ���ݰ�����+���ݰ�����
//�����ڽṹ
//struct SL_Message 
//{
//    ushort len; 
//    char   content[0];
//}

class SL_Socket_Message_Handler : public SL_Socket_Handler
{
public:
    SL_Socket_Message_Handler()
        : need_len_(0)
        , last_error_msglen_(0)
        , last_left_(0)
    {
    }

    virtual ~SL_Socket_Message_Handler() 
    {
    }

    virtual int handle_open(SL_SOCKET fd, SL_Socket_Source *socket_source, SL_Socket_Runner *socket_runner)
    {
        SL_Socket_Handler::handle_open(fd, socket_source, socket_runner);
        msg_buffer_.reserve(socket_source_->get_msgbuffer_size());
        msg_buffer_.reset();
        need_len_           = 0;
        last_error_msglen_  = 0;
        last_left_          = 0;
        return 0;
    }

    //���յ�������Ϣʱ,�ص��˺���
    virtual int handle_message(const char *msg, int len)
    {
        return 0;
    }

    int handle_read();
    int write_message(const char *msg, int len);

    //Ŀǰû�п��ǿ�ƽ̨���ֽ�˳��
    //һ���ֽ�˳��:BIG Endian��LITTLE Endian
    //1)ȡ����Ϣ����
    static int get_msglen(const char *msg, int len, int msglen_bytes, int byteorder);
    //2)������Ϣ����
    static int set_msglen(char *msg, int len, int msglen_bytes, int byteorder);

protected:
    SL_ByteBuffer   msg_buffer_;            //��Ϣ����
    int             need_len_;              //���һ����Ϣ��������Ҫ����
    int             last_error_msglen_;     //�������ʱ���ݰ�����
    int8            last_left_;             //���յ������ݳ���С����Ϣlen����ռ����ʱ��Ч��һ��Ϊ0
};

#endif

