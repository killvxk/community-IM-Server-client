#ifndef SOCKETLITE_CRYPTO_RAND_H
#define SOCKETLITE_CRYPTO_RAND_H

class SL_Crypto_Rand
{
public:
    enum TYPE
    {
        RANDOM_CHAR = 0,        // ��unsinged char ��������ڴ��
        VISIBLE_CHAR,	        // ��char ������� �����ַ���(���̿�������)
        STANDARD_CHAR,	        // ��char ������� ��׼�ַ���(�����������ַ���)
        ENLARGE_CHAR,           // ��char ������� ��ǿ�ͱ�׼�ַ���(�����Զ���������ַ�)
        NUMBER_CHAR,            // ��char ������� ������(0-9)
        LOWERCASE_CHAR,         // ��char ������� Сд��ĸ(a-z)
        UPPERCASE_CHAR,         // ��char ������� ��д��ĸ(A-Z)

        TYPE_NUMS,
    };

    SL_Crypto_Rand()
    {
    }

    virtual ~SL_Crypto_Rand()
    {
    }

    virtual void seed() = 0;
    virtual int  seed(int seed) = 0;

    virtual int random_byte(char *out, int out_len, SL_Crypto_Rand::TYPE type, const char *special_char) = 0;
    virtual int random_byte(char *out, int out_len, int low, int high) = 0;
    virtual int random_int() = 0;
    virtual int random_int(int low, int high) = 0;
    virtual double random_double() = 0;
    virtual double random_double(double low, double high) = 0;
};

#endif

