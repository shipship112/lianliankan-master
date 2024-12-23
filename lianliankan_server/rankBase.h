/*
* Name: QinKuai
* Status: Finished
*/
#pragma once

#ifndef RANKBASE_H
#define RANKBASE_H

#define RANK_SPLIT '$'
#include "gameSettings.h"
#include <string>
#include <vector>
#include "userBase.h"
#include "databaseCommon.h"

//for test
#include <iostream>

//���������ڷ���������ʱֱ�ӽ����а���Ϣ
//���������Բ���
class RankBase {
public:
	//��֤��ʵ��ֻ������һ��
	static RankBase* getRankBase();

	//�����ݿ��е����ݳ�ʼ�������ϵ�RankBase��
	//int��ʾ���õ�gameLevel
	//string��ʾ���ݿ��еĸ�ʽ���ַ���
	//�÷������н�������������
	int stringToScoreRank(int, std::string);

	//�����а���Ϣת��Ϊ�ṹ���ַ���
	//���ڴ������ݿ�
	//int��ʾgameLevel
	std::string scoreRankToString(int);

	//���δ���������ݿ���û�
	//�������û�ע����ɺ�
	//���ɲ�����Ϣ�������а��в��������Ϣ
	bool insertToRankBase(const int);

	//�����Ա��������а���
	//���Ǽ��鵱ǰ��ע�������Ƿ񳬹���10��
	//��ȷ�����û�ע��ʱ�Ƿ���Ҫ�������а�
	bool canInsert();
	
	//����Ѵ��������ݿ���û�
	//�ڷ������˴����û����������Ϣ�����仯��
	//�˷������Ը�����RankBase�ϵ����а���Ϣ
	bool updateToRankBase(const int);

	//ȷ���Ƿ���Ҫ�����а������и�����Ϣ
	//int����ָ��gameLevel
	//ֻҪ��ӦgameLevel�ķ������ڵ�ǰ���а�����һλ�ķ���
	//��ȷ������
	bool needToUpdate(const int, int);

	//�������а��е�ID
	//���ҵ����ظ�ID���ڵ�index
	//ID�����ڷ���-1
	//�ڶ���int��ʾgameLevel
	int findID(int, int);

	//��ȡ��ָ��gameLevel�����а�����
	std::vector<int>& getRankByLevel(int);

	static int getGameAmount();
private:
	RankBase();
	//��ʵ��
	static RankBase* rankBaseInstance;
	//��ʵ����ά��һ�����а��б�
	//���а���ͨ��ֱ�Ӵ洢�û�IDʵ��
	//ͨ��gameLevel��ȡ��Ӧ����Ϸ�����а�
	std::vector<std::vector<int>> rank;
	//��¼������Ϸ���е���Ϸ����
	static int gameAmount;
};

#endif // !RANKBASE_H

