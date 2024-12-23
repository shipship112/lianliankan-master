/*
* Name: QinKuai
* Status: Finished
*/

#pragma once
#ifndef SERVER_H
#define SERVER_H
#define EXIT "exit"
#define HELP "help"

#include <string>
#include <string.h>
#include <iostream>

#include "netMsg.h"
#include "common.h"
#include "log.h"
#include "userBase.h"
#include "userDatabase.h"
#include "rankBase.h"
#include "rankDatabase.h"

#define HELPMSG std::cout<<"**    exit: exit the server\n**    help: to know command\n";
#define CMDERROR std::cout<<"**    INVALID COMMAND LINE\n";

class Server {
public:
	Server();
	~Server();
	bool init();
	void start();
	void close();

	//��Ӧ�ͻ��˲����ķ���
	NetMsg* userRegister(NetMsg*);
	NetMsg* userLogin(NetMsg*);
	NetMsg* userLogout(NetMsg*);
	NetMsg* userdataUpdate(NetMsg*);
	NetMsg* userRanking(NetMsg*, int);
private:
	//TCP socket�ĵ�ַ�ṹ
	SOCKADDR_IN addr;
	//socket��ֵ
	SOCKET socket1;
};


#endif // !SERVER_H

