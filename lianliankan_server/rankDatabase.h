/*
* Name: QinKuai
* Status: Finished
*/
#pragma once

#ifndef RANKDATABASE_H
#define RANKDATABASE_H

#include "databaseCommon.h"
#include <jdbc/cppconn/driver.h>
#include <jdbc/cppconn/exception.h>
#include <jdbc/cppconn/resultset.h>
#include <jdbc/cppconn/statement.h>

#include "rankBase.h"
#include "log.h"

class RankDatabase {
public:
	//�����ݿ��е����ݼ��ص�RankBase��
	static bool databaseToRanking();
	//�������ݿ��е����а�����
	//int��ʾ��Ӧ��gameLevel
	//std::string��ʾ�µ�������Ϣ
	//ʹ���û�ID��������
	static bool updateToDatabase(int, std::string);

	//�ر����ݿ�����
	static void close();

private:
	RankDatabase();
	//���������а����ݿ������
	static bool init();

	//���ݿ��������
	static sql::Driver *driver;
	static sql::Connection *conn;
	static sql::Statement* stmt;
	static sql::ResultSet* res;
};

#endif // !RANKDATABASE_H

