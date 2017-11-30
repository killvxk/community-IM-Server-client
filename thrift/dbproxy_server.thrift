
namespace cpp community.dbproxy_server

enum MessageType
{
    MT_LOGIN_CHECK_REQ 		= 5000,
    MT_LOGIN_CHECK_RES,
	
	MT_USER_LOGIN_REQ,
    MT_USER_LOGIN_RES,
	
    MT_LOGIN_GET_USERINFO_REQ,
    MT_LOGIN_GET_USERINFO_RES,
	
	MT_GET_USER_IDENTITY_REQ,
	MT_GET_USER_IDENTITY_RES,
	
	MT_LOGIN_REGIST0R_REQ,
	MT_LOGIN_REGIST0R_RES,
	
	MT_ROOMGATE_REGIST0R_REQ,
	MT_ROOMGATE_REGIST0R_RES,
	
	MT_ROOM_REGIST0R_REQ,
	MT_ROOM_REGIST0R_RES,
	
    MT_ROOM_ENTER_ROOM_REQ,
    MT_ROOM_ENTER_ROOM_RES,
    
    MT_LEAVE_ROOM_PENDING_REQ,
    MT_LEAVE_ROOM_PENDING_RES,

    MT_LEAVE_ROOM_COMPLETE_REQ,
    MT_LEAVE_ROOM_COMPLETE_RES,

    MT_ROOM_UPDATE_ROOMINFO_REQ,
    MT_ROOM_UPDATE_ROOMINFO_RES,
    
    MT_ROOMGATE_UPDATE_USERINFO_REQ,
    MT_ROOMGATE_UPDATE_USERINFO_RES,
    
    MT_ROOM_UPDATE_ROOM_ONLINE_COUNT_REQ,
    MT_ROOM_UPDATE_ROOM_ONLINE_COUNT_RES,
}

struct UserLoginReq
{
	1:i32		user_id,
	2:string 	user_name,
	3:string	session_id,
	4:i64		log_time,
}

struct LoginCheckReq
{
    1:string    user_name,
    2:string    check_sum,
    3:string    client_mac,
    4:string    client_ip,
}

struct LoginCheckRes
{
    1:i16       error_code,
    2:string    error_text,
}

struct LoginGetUserInfoReq
{
    1:string    user_name,
}

struct UserInfo
{
	1:i32       user_id,                        //�û�ID
    2:string    user_name,                      //�û���
    3:string	password,			//�û�����
    4:string    email,                          //����
    5:string    nick_name,                      //�ǳ�
    6:string    avatar_url,                     //�û�ͷ��url
    7:string    birthdate,                      //��������
    8:i16      base_role_id,                   //������ɫ
    9:byte     gender,                         //�Ա�(0�� 1Ů 2����)
    10:string   chinese_zodiac,                 //��Ф
    11:string   zodiac,                         //����
    12:string   blood_type                      //Ѫ��
    13:string   interest,                       //�û�����,��Ȥ
    14:string   character,                      //�û��Ը�
    15:string	sign_name,			//����ǩ��
    16:i16      chest,                          //��Χ
    17:i16      waist,                          //��Χ
    18:i16      hip,                            //��Χ
    19:string   address,                        //����
}

struct LoginGetUserInfoRes
{
    1:i16       error_code,
    2:string    error_text,
	3:UserInfo	user_info,
}

//���ӷ����Ա(�������ݱ�tb_room_member)
struct RoomAddMemberReq
{
    1:i32	user_id,          //�û�id
}

//ɾ�������Ա(�������ݱ�tb_room_member)
struct RoomRemoveMemberReq
{
    1:i32	user_id,
}

//�����û���Ϣ
struct RoomGateUpdateUserinfoReq
{
    1:string    nick_name,                      //�û��ǳ�
    2:string    avatar_url,                     //�û�ͷ��url
    3:i32       decolor,                        //��ɫ���
    4:string    sign_name,                      //����ǩ��
    5:byte      gender,                         //�Ա�(0�� 1Ů 2����)
    6:string    birthdate,                      //��������
    7:string    chinese_zodiac,                 //��Ф
    8:string    zodiac,                         //����
    9:string    blood_type                      //Ѫ��
    10:string   interest,                       //�û����á���Ȥ
    11:string   character,                      //�û��Ը�
    12:i16      chest,                          //��Χ
    13:i16      waist,                          //��Χ
    14:i16      hip,                            //��Χ
    15:string   address,                        //��ַ(����)
}

struct GetUserIdentityReq
{
	1:i32	user_id,
}

struct GetUserIdentityRes
{
	1:i16       error_code,
    2:string    error_text,
	3:string	user_key,
	4:string	session_id,
}

struct ServerRegisterReq
{
	1:i16 		serice_type,
	2:i32 		service_id,
	3:string 	service_name,
	4:i64		log_time,
}

struct RoomGateUserRegisterReq
{
	1:i32 		user_id,
	2:i32 		room_gate_id,
	3:string 	session_id,
	4:i64		log_time,
}

//���·���ԣ����ŵķ���roomgateֱ����dbp�����Ϣ(�������ݱ�tb_room_info)
struct RoomUpdateRoominfoReq
{
    1:string    room_name,                      //��������
    2:i32       room_flags,                     //�����ʶ
    3:string    room_broadinfo,                 //���乫��
    4:string    recharge_broadinfo,             //�����ֵ����
    5:string    welcome_phrase,                 //���件ӭ��
    6:bool      is_change_password,             //�Ƿ������
    7:string    password,                       //��������(���������������ʱΪ��, ���ڸ�����)
    8:bool      is_change_image,                //�Ƿ�ķ���ͼƬ
    9:string    room_image_url,                 //����ͼƬurl
    10:i16	room_broadinfo_status,		//����㲥���״̬
    11:i16	recharge_broadinfo_status,	//��ֵ�������״̬
    12:i16	welcome_phrase_status,		//���件ӭ�����״̬
    13:i16	room_broadinfo_minutes,		//���乫����ʾ���
    14:i16	recharge_broadinfo_minutes,	//��ֵ������ʾ���
    15:i16	welcome_phrase_minutes,		//���件ӭ����ʾ���
}

struct RoomEnterRoomReq
{
	1:string 	room_password,
    2:i16       base_role_id,                   //������ɫ
    3:i16       use_role_id,                    //��ǰʹ�ý�ɫid
    4:string    user_ip,                        //�û�ip
    5:string    user_mac,                       //�û�mac
    6:bool      is_temp_user,                   //�Ƿ�Ϊ�ο�
}

struct RoomEnterRoomRes
{ 
    1:i16       error_code,
    2:string    error_text,
    3:bool      is_in_blacklist,                //�Ƿ��ں�������
    4:bool      is_favorite,                    //�Ƿ��ղط���
}