/*
* Name: QinKuai
* Status: Finished
*/
#pragma once
#ifndef NETMSG_H
#define NETMSG_H

#define DEFAULT_MODE 0
#define SECRET_MODE 1
#define RANKING_MODE 2

#include <list>
#include "user.h"
#include "common.h"

class NetMsg {
public:
	NetMsg();
	NetMsg(std::list<User>&, ushort);
	~NetMsg();
	//���л�
	//������ָ����û�����
	//ת��Ϊ�ַ�����ʵ�����紫��
	//�ڶ���������ʾ���л���ģʽ
	//DEFAULT_MODE���л��û�������Ϣ
	//SECRET_MODE���л��û������������������Ϣ
	//RANKING_MODEֻ���л��û��ıȷ���Ϣ
	int serialize(char*&, int);
	//�����л�
	//�����紫��������ַ���
	//ת��Ϊһ����������ָ����û�����Ķ���
	//�ڶ���������ʾ���л���ģʽ
	//DEFAULT_MODE�����л��û�������Ϣ
	//SECRET_MODE�����л��û������������������Ϣ
	//RANKING_MODEֻ�����л��û��ıȷ���Ϣ
	int deserialize(const char*m, int);

	void addUserToList(User&);
	std::list<User>& getUsers();
	void setUsers(std::list<User>&);
	ushort getCommand();
	void setCommand(ushort);
private:
	//�ں���ĳһ�û�
	std::list<User> users;
	//�û��б��е��û���
	ushort list_size;
	//ָ���Ĳ�������
	ushort command;
};

#endif // !NETMSG_H

