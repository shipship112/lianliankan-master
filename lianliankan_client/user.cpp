/*
* Name: QinKuai
* Status: Finished
*/

#include "user.h"

User::User() {};

User::User(std::string username, std::string password) {
	this->userName = username;
	this->password = password;
	
	this->score = 0;
	this->clearGameNumber = 0;
	this->gameScore.resize(GAMEAMOUNT);
	for (int i = 0; i < GAMEAMOUNT; i++) {
		this->gameScore[i] = 0;
	}
	
	this->coins = 0;
	this->timeDelayItemAmount = 0;
	this->reconstructItemAmount = 0;
	this->propmtItemAmount = 0;
	this->loginStatus = false;
}

int User::getID() {
	return this->ID;
}

void User::setID(int id) {
	this->ID = id;
}


std::string User::getUserName() {
	return this->userName;
}

void User::setUserName(std::string username) {
	this->userName = username;
}

std::string User::getPassword() {
	return this->password;
}

void User::setPassword(std::string password) {
	this->password = password;
}

int User::getScore() {
	return this->score;
}

void User::setScore(int score) {
	this->score = score;
}

void User::updateScore() {
	int score = 0;
	for (int i = 1; i <= GAMEAMOUNT; i++) {
		score += this->getGameScore(i);
	}
	this->setScore(score);
}

ushort User::getClearGameNumber() {
	return this->clearGameNumber;
}

void User::setClearGameNumber(ushort number) {
	this->clearGameNumber = number;
}

int User::getGameScore(int gameLevel) {
	if (gameLevel <= 0 || gameLevel > GAMEAMOUNT) {
		return -1;
	}
	return this->gameScore[gameLevel - 1];
}

void User::setGameScore(int score, int gameLevel) {
	if (gameLevel <= 0 || gameLevel > GAMEAMOUNT) {
		return;
	}
	this->gameScore[gameLevel - 1] = score;
}

//��ȡ�����а���������Ӧ�ķ���
//0��ʾ�ܷ�
//֮���������ʾ���ݷ���
int User::getRankScore(int gameLevel) {
	if (gameLevel < 0 || gameLevel > GAMEAMOUNT) {
		return -1;
	}
	return (gameLevel == 0) ? this->score : this->getGameScore(gameLevel);
}

//���������а���������Ӧ�ķ���
//0��ʾ�ܷ�
//֮���������ʾ���ݷ���
void User::setRankScore(int score, int level) {
	if (level == 0) {
		this->setScore(score);
	} else {
		this->setGameScore(score, level);
	}
}

//��ÿ�ֵ÷���ɵ�����ת��Ϊ�ַ���
//�Ա��ڴ������ݿ�
int User::scoreArrayTochars(char*& chars) {
	int count = 0;
	int gameScore = 0;
	for (int i = 1; i <= GAMEAMOUNT; i++) {
		gameScore = this->getGameScore(i);
		//��ر�֤����������8λ����
		_itoa_s(gameScore, chars + count, 8, 10);
		count += numberLength(gameScore);
		//��ӷָ���
		memset(chars + count, SPLIT_FLAG, 1);
		count++;
	}

	return count;
}

//��ÿ�ֵ÷ֵ��ַ���ת��Ϊ�÷�����
//�Ա�ó����ݿ��е�����
int User::charsToScoreArray(const std::string& str) {
	int scorePerGame = 0;
	int index = 0;
	int offset = 0;
	for (int i = 1; i <= GAMEAMOUNT; i++) {
		index = str.find(SPLIT_FLAG, offset);
		std::string temp = str.substr(offset, index - offset);
		scorePerGame = atoi(temp.c_str());

		if (scorePerGame < 0) {
			return -1;
		}
		this->setGameScore(scorePerGame, i);
		offset = index + 1;
	}
	return offset;
}

int User::getCoins() {
	return this->coins;
}

void User::setCoins(int coins) {
	this->coins = coins;
}

ushort User::getTimeDelayItemAmount() {
	return this->timeDelayItemAmount;
}

void User::setTimeDelayItemAmount(ushort amount) {
	this->timeDelayItemAmount = amount;
}

ushort User::getReconstructItemAmount() {
	return this->reconstructItemAmount;
}

void User::setReconstructItemAmount(ushort amount) {
	this->reconstructItemAmount = amount;
}

ushort User::getPropmtItemAmount() {
	return this->propmtItemAmount;
}

void User::setPropmtItemAmount(ushort amount) {
	this->propmtItemAmount = amount;
}

bool User::getLoginStatus() {
	return this->loginStatus;
}

void User::setLoginStatus(bool status) {
	this->loginStatus = status;
}