/*
* Name: QinKuai
* Status: Unfinised
*/
#pragma once
#ifndef USER_H
#define USER_H

#ifndef INT_LENGTH
#define INT_LENGTH 4
#endif // !INT_LENGTH

#define SPLIT_FLAG '$'

#include <string>
#include <string.h>
#include "tool.h"
#include <vector>

typedef unsigned short ushort;

class User {
public:
	User();
	User(std::string, std::string);

	std::string getUserName();
	void setUserName(std::string);
	std::string getPassword();
	void setPassword(std::string);

	int getScore();
	void setScore(int);
	ushort getClearGameNumber();
	void setClearGameNumber(ushort);
	int getGameScore(int);
	void setGameScore(int, int);
	//��ÿ�ֵ÷���ɵ�����ת��Ϊ�ַ���
	//�Ա��ڴ������ݿ�
	int scoreArrayTochars(char*&);
	//��ÿ�ֵ÷ֵ��ַ���ת��Ϊ�ȷ�����
	//�Ա�ó����ݿ��е�����
	int charsToScoreArray(const char*&);

	int getCoins();
	void setCoins(int);
	ushort getReconstructItemAmount();
	void setReconstructItemAmount(ushort);
	ushort getTimeDelayItemAmount();
	void setTimeDelayItemAmount(ushort);

	bool getLoginStatus();
	void setLoginStatus(bool);
private:
	//�û���
	//15���ַ�����
	std::string userName;
	//�û�����
	std::string password;

	//�������
	//�ܵ÷�
	int score;
	//��ǰ�Ѿ�ͨ�صľֵȼ�
	//1��ʾͨ���˹ؿ�1���Դ�����
	ushort clearGameNumber;
	//ÿ����Ϸ�Ļ���
	std::vector<int> gameScore;

	//�������
	//�����
	int coins;
	//��ʱ���߳�����
	ushort timeDelayItemAmount;
	//�ع����߳�����
	ushort reconstructItemAmount;

	//��¼�û��ĵ�½״̬
	bool loginStatus;

	//�ڴ˻����Ͽ��Լ���
	//�־ֻ���
	//int score_game1;
	//�û���ǰ�ѵ���ľ�����ǰ����������Ϸӵ�ж����Ϸ
	//int finished;
};

#endif // !USER_H

