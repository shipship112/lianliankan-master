/*
* Name: QinKuai
* Status: Finished
*/
#pragma once
#ifndef USER_H
#define USER_H

#define SPLIT_FLAG '$'

#include <string>
#include <string.h>
#include <vector>
#include "gameSettings.h"
#include "tool.h"

typedef unsigned short ushort;

class User {
public:
	User();
	User(std::string, std::string);

	int getID();
	void setID(int);
	std::string getUserName();
	void setUserName(std::string);
	std::string getPassword();
	void setPassword(std::string);

	int getScore();
	void setScore(int);
	void updateScore();
	ushort getClearGameNumber();
	void setClearGameNumber(ushort);
	int getGameScore(int);
	void setGameScore(int, int);
	//��ȡ�����а���������Ӧ�ķ���
	//0��ʾ�ܷ�
	//֮���������ʾ���ݷ���
	int getRankScore(int);
	//���������а���������Ӧ�ķ���
	//0��ʾ�ܷ�
	//֮���������ʾ��ӦgameLevel�ķ���
	void setRankScore(int, int);
	//��ÿ�ֵ÷���ɵ�����ת��Ϊ�ַ���
	//�Ա��ڴ������ݿ�
	int scoreArrayTochars(char*&);
	//��ÿ�ֵ÷ֵ��ַ���ת��Ϊ�ȷ�����
	//�Ա�ó����ݿ��е�����
	int charsToScoreArray(const std::string&);

	int getCoins();
	void setCoins(int);
	ushort getReconstructItemAmount();
	void setReconstructItemAmount(ushort);
	ushort getTimeDelayItemAmount();
	void setTimeDelayItemAmount(ushort);
	ushort getPropmtItemAmount();
	void setPropmtItemAmount(ushort);

	bool getLoginStatus();
	void setLoginStatus(bool);
private:
	//�û���Ӧ��ID
	int ID;
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
	//��ʾ���߳�����
	ushort propmtItemAmount;

	//��¼�û��ĵ�½״̬
	bool loginStatus;

	//�ڴ˻����Ͽ��Լ���
	//�־ֻ���
	//int score_game1;
	//�û���ǰ�ѵ���ľ�����ǰ����������Ϸӵ�ж����Ϸ
	//int finished;
};

#endif // !USER_H

