/*
* Name: QinKuai
* Status: Finished
*/

#pragma once
#ifndef USERDATABASE_H
#define USERDATABASE_H

#include "databaseCommon.h"
//#include <jdbc/mysql_connection.h>
#include <jdbc/cppconn/driver.h>
#include <jdbc/cppconn/exception.h>
#include <jdbc/cppconn/resultset.h>
#include <jdbc/cppconn/statement.h>

#include "user.h"
#include "userBase.h"
#include "log.h"

class UserDatabase {
public:
	//�����ݿ��е���������UserBase��
	//ʵ���û����ݹ�����list��
	static bool databaseToUsers();
	//����û���Ϣ
	static bool addToDatabase(User &user);
	//ɾȥ�û���Ϣ
	static bool deleteToDatabase(User &user);
	//�����û���Ϣ
	static bool updateToDatabase(User &user);
	//�ر����ݿ�����
	static void close();
private:
	UserDatabase();
	//�����û����ݿ����ʱ��ʼ�������ݿ������
	static bool init();

	//���ݿ��������
	static sql::Driver *driver;
	static sql::Connection *conn;
	static sql::Statement *stmt;
	static sql::ResultSet *res;
};

#endif // !USERDATABASE_H
