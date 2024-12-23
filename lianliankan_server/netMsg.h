/*
* Name: QinKuai
* Status: Finished
*/
#pragma once
#ifndef NETMSG_H
#define NETMSG_H

#define DEFAULT_MODE 0
#define SECRET_MODE 1

#include <vector>
#include "user.h"
#include "common.h"

class NetMsg {
public:
	NetMsg();
	NetMsg(std::vector<User>&, ushort);
	~NetMsg();
	//���л�
	//������ָ����û�����
	//ת��Ϊ�ַ�����ʵ�����紫��
	//�ڶ���������ʾ���л���ģʽ
	//DEFAULT_MODE���л��û�������Ϣ
	//SECRET_MODE���л��û������������������Ϣ
	//RANKING_MODEֻ���л��û��ıȷ���Ϣ
	int serialize(char*&, int);

	//��̨�������л����а�
	//�������а��string-int��Ӧ��
	//��int��ʾָ�����������а�ľ���
	//0��ʾ�ܷ���
	//֮���������ʾ��Ӧ����
	int server_ranking_serialize(char*&, int);

	//�ͻ����������л����а�������Ϣ
	//int ��ʾgameLevel
	int client_ranking_serialize(char*&, int);

	//�����л�
	//�����紫��������ַ���
	//ת��Ϊһ����������ָ����û�����Ķ���
	//�ڶ���������ʾ���л���ģʽ
	//DEFAULT_MODE�����л��û�������Ϣ
	//SECRET_MODE�����л��û������������������Ϣ
	//RANKING_MODEֻ�����л��û��ıȷ���Ϣ
	int deserialize(const char*m, int);

	//��̨���Խ���ǰ̨�����а�����
	int server_ranking_deserialize(char*&, int&);

	//ǰ̨���Խ�����̨���͵����а���Ϣ
	//�����л�string-int��
	//��ȡ�����а���û��б�
	//����ȡ���ķ���ֱ�Ӽ��ص�score������
	//int&��ȡ����Ĺؿ����
	//�ͻ��˴���int���Լ�����������ҵ�gameLevel�Ƿ����
	int client_ranking_deserialize(char*&, int&);

	//�������ַ����е�command����
	//����command
	ushort command_deserialize(char*&);

	void addUserToList(User&);
	std::vector<User>& getUsers();
	void setUsers(std::vector<User>&);
	ushort getCommand();
	void setCommand(ushort);
private:
	//�ں���ĳһ�û�
	std::vector<User> users;
	//�û��б��е��û���
	ushort list_size;
	//ָ���Ĳ�������
	ushort command;
};

#endif // !NETMSG_H

