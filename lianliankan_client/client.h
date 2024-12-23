/*
* Name: QinKuai
* Status: Unfinised
*/
#pragma once
#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include <string.h>
#include "common.h"
#include "netMsg.h"

//for test
#include <iostream>

class Client {
public:
	//ֻ��ͨ�����������ȡ������ʵ��
	static Client* getClientInstance();
	//��������
	bool start();
	//�ر�����
	bool close();
	//ͨ��ָ��string��ʵ��ͬһ������ͬʵ��
	NetMsg* request(NetMsg*&, int, int);
private:
	//ά��һ�������ľ�̬ʵ��
	static Client* client;
	//���صĹ�����
	Client();
	//��ʼ��������ز���
	bool init();

	//�û�ע��
	NetMsg* send_register(NetMsg*&);
	//�û���¼
	NetMsg* send_login(NetMsg*&);
	//�û��ǳ�
	NetMsg* send_logout(NetMsg*&);
	//�û���������
	NetMsg* send_update(NetMsg*&);
	//��ȡ���а�
	NetMsg* send_ranking(NetMsg*&, int);

	//���˷���NetMsg
	bool sendToServer(NetMsg*&);
	//���պ�˵�NetMsg
	bool recvFromServer(NetMsg*&);

	//TCP socket�ĵ�ַ�ṹ
	SOCKADDR_IN addr;
	//socket��ֵ
	SOCKET socket1;
};

#endif // !CLIENT_H

