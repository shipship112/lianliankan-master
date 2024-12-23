/*
* Name: QinKuai
* Status: Unfinished
*/

#ifndef CLIENT_H
#define CLIENT_H
#include "common.h"

class Client {
public:
	Client();
	~Client();
	
	//����Server�Ĳ���
	bool userRegister();
	bool registerBack();
	bool userLogin();
	bool loginBack();
	bool userLogout();
	bool logoutBack();
	bool userUpdate();
	bool updateBack();
	bool ranking();
	bool rankingBack();
private:
	//TCP socket�ĵ�ַ�ṹ
	SOCKADDR_IN addr;
	//socket��ֵ
	SOCKET client_socket;
};

#endif // !CLIENT_H

