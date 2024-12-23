/*
* Name: QinKuai
* Status: Finished
*/
#pragma once
#ifndef COMMON_H
#define COMMON_H
//����Windows�����µ�����ͷ�ļ�
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <iostream>
#pragma comment(lib, "Ws2_32.lib")

//#define SERVER_IP "127.0.0.1"
#define SERVER_IP "192.168.1.100"

#define SERVER_PORT 8888

//��TCP/IPЭ����BUFFER����1024
#define BUFFER_SIZE 0x400 // 1024

#define CHARS_MAX_LENGTH 0x400 //1024 1kB

#define INT_LENGTH 4

#define USHORT_LENGTH 2

#define DEFAULT_COMMAND 0
//����CS�����ڵ�½��ע��͵ǳ���ز���
//����Ӧ�Ĳ�����
//ע�����
#define REGISTER 1
//ע��ɹ�
#define REGISTER_SUCCESS 2
//ע��ʧ��
#define REGISTER_FAIL 3

//��½����
#define LOGIN 4
//��½�ɹ�
#define LOGIN_SUCCESS 5
//��½ʧ��
#define LOGIN_FAIL 6

//�ǳ�����
#define LOGOUT 7
//�ǳ��ɹ�
#define LOGOUT_SUCCESS 8
//�ǳ�ʧ��
#define LOGOUT_FAIL 9

//����CS��������Ϸ����ʱ�������
//����Ӧ�Ĳ�����
//��Ϣ����
#define USERDATA_UPDATE 10
//��Ϣ�ϴ��ɹ�
#define USEREDATA_UPDATE_SUCCESS 11
//��Ϣ�ϴ�ʧ��
#define USERDATA_UPDATE_FAIL 12

//����CS���������а�����ʱ���������
//����Ӧ�Ĳ�����
//�������а���Ϣ
#define RANKING 13
//�������а����ݳɹ�
#define RANKING_SUCCESS 14
//�������а�����ʧ��
#define RANKING_FAIL 15


#endif // !COMMON_H

