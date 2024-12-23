/*
* Name: QinKuai
* Status: Finished
*/

#include "rankBase.h"

//��̬������ʼ��
int RankBase::gameAmount = GAMEAMOUNT;
RankBase* RankBase::rankBaseInstance = nullptr;

//���صĹ�����
RankBase::RankBase() {
	this->rank.resize(RankBase::gameAmount + 1);
}

//��֤��ʵ��ֻ������һ��
RankBase* RankBase::getRankBase() {
	if (RankBase::rankBaseInstance == nullptr) {
		RankBase::rankBaseInstance = new RankBase();
	}
	return RankBase::rankBaseInstance;
}

//�������ݿ��л�ȡ�������а��ַ�������
//ת��Ϊ���а�������Ϣ
//�����ݿ��е����ݳ�ʼ�������ϵ�RankBase��
int RankBase::stringToScoreRank(int gameLevel, std::string str) {
	//��ӦgameLevel�������ʼ��
	this->rank[gameLevel].resize(10);

	int length = str.length();
	int counter = 0;
	int tempID = 0;
	int index = 0;
	int offset = 0;
	while (true) {
		index = str.find(RANK_SPLIT, offset);
		if (index == -1) {
			return -1;
		}
		std::string temp = str.substr(offset, index - offset);
		tempID = atoi(temp.c_str());

		if (tempID <= 0) {
			return -1;
		}
		this->rank[gameLevel][counter++] = tempID;
		offset = index + 1;
	}
}

//�ڷ������˴����û����������Ϣ�����仯��
//�˷������Ը�����RankBase�ϵ����а���Ϣ
std::string RankBase::scoreRankToString(int gameLevel) {
	std::string str("");
	int count = 0;
	int tempID = 0;
	int length = (UserBase::getUserBase()->getUsersLength() < 10) ? UserBase::getUserBase()->getUsersLength() : 10;

	for (int i = 0; i < length; i++) {
		tempID = this->rank[gameLevel][i];
		str.append(intToString(tempID));
		str += RANK_SPLIT;
	}
	return str;
}

//���δ���������ݿ���û�
//�������û�ע��ʱ
//���ɲ�����Ϣ�������а��в��������Ϣ
bool RankBase::insertToRankBase(const int ID) {
	if (canInsert()) {
		for (int i = 0; i <= GAMEAMOUNT; i++) {
			this->rank[i][UserBase::getUserBase()->getUsersLength() - 1] = ID;
		}
		return true;
	}
	return false;
}

//�����Ա��������а���
//int��ʾgameLevel
bool RankBase::canInsert() {
	if (UserBase::getUserBase()->getUsersLength() > 10) {
		return false;
	}
	return true;
}

//����ȡ���ĸ�ʽ�����ַ�תת��Ϊ���а���Ϣ
//�������ӦgameLevel��������
bool RankBase::updateToRankBase(const int ID) {
	//i�������е�gameLevel
	for (int i = 0; i <= GAMEAMOUNT; i++) {
		if (needToUpdate(ID, i)) {
			//��ʾ���а������и��û�
			//�����еķ����¸���
			int index = findID(ID, i);
			if (index != -1) {
				//����������ԭ�û�ID
				std::vector<int>::iterator it = this->rank[i].begin();
				it += index;
				this->rank[i].erase(it);
				//�����µ�ԭ�û�ID
				for (it = this->rank[i].begin(); it < this->rank[i].end(); it++) {
					int oldScore = UserBase::getUserBase()->findUser(*it)->getRankScore(i);
					int newScore = UserBase::getUserBase()->findUser(ID)->getRankScore(i);
					if (newScore > oldScore) {
						this->rank[i].insert(it, ID);
						break;
					}
					if (*(it + 1) == 0 || (it + 1) == this->rank[i].end()) {
						this->rank[i].insert(it + 1, ID);
						break;
					}
				}
			//��ʾ���а��л�û�и��û�
			//ֱ�Ӳ�����û��ķ�����Ϣ
			} else {
				for (std::vector<int>::iterator it = this->rank[i].begin(); it < this->rank[i].end(); it++) {
					int oldScore = UserBase::getUserBase()->findUser(*it)->getRankScore(i);
					int newScore = UserBase::getUserBase()->findUser(ID)->getRankScore(i);
					if (newScore > oldScore) {
						this->rank[i].insert(it, ID);
						break;
					}
				}
				//�޳������һ���������Ԫ��
				//��֤����ʼ�ճ���Ϊ10
				this->rank[i].pop_back();
			}
		}
	}
	return true;
}

//ȷ���Ƿ���Ҫ�����а������и�����Ϣ
//ֻҪ��ӦgameLevel�ķ������ڵ�ǰ���а�����һλ�ķ���
//��ȷ������
bool RankBase::needToUpdate(const int ID, int gameLevel) {
	int last = (UserBase::getUserBase()->getUsersLength() < 10) ? UserBase::getUserBase()->getUsersLength() - 1 : 9;
	//�����а�����һλΪ�����IDʱ
	//ֱ���������
	//���Ա�֤��εķ���һ����֮ǰ�ĸ�
	if (this->rank[gameLevel][last] == ID) {
		return true;
	}
	int lastScore = UserBase::getUserBase()->findUser(this->rank[gameLevel][last])->getRankScore(gameLevel);
	int newScore = UserBase::getUserBase()->findUser(ID)->getRankScore(gameLevel);
	if (lastScore >= newScore) {
		return false;
	}
	return true;
}

//�������а��е�ID
//ID�����ڷ���-1
int RankBase::findID(int ID, int gameLevel) {
	for (int i = 0; i < 10; i++) {
		if (ID == this->rank[gameLevel][i]) {
			return i;
		}
	}
	return -1;
}

//��ȡ��ָ��gameLevel�����а�����
std::vector<int>& RankBase::getRankByLevel(int level) {
	return this->rank[level];
}

int RankBase::getGameAmount() {
	return RankBase::gameAmount;
}