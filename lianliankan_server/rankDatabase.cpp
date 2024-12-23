/*
* Name: QinKuai
* Status: Finished
*/

#include "rankDatabase.h"

//��̬�����ĳ�ʼ��
sql::Driver* RankDatabase::driver = nullptr;
sql::Connection* RankDatabase::conn = nullptr;
sql::Statement* RankDatabase::stmt = nullptr;
sql::ResultSet* RankDatabase::res = nullptr;


RankDatabase::RankDatabase() {}

//�����ݿ��е����ݼ��ص�RankBase��
bool RankDatabase::databaseToRanking() {
	if (!init()) {
		LOG("���ݳ�ʼ��ʧ��")
		return DB_FAIL;
	}

	try {
		stmt = conn->createStatement();
		res = stmt->executeQuery("select * from ranking;");

		while (res->next()) {
			//��ȡgameLevel
			int gameLevel = res->getInt("gameLevel");
			//��ȡ���а��string
			std::string rank = res->getString("rankByID");

			//����ȡ�������а���Ϣд��RankBase
			//���δ���RankBase�Ļ������а���
			RankBase::getRankBase()->stringToScoreRank(gameLevel, rank);
		}

		delete res;
		delete stmt;
	} catch (sql::SQLException &e) {
		LOG(e.what());
		LOG(e.getErrorCode());
		LOG(e.getSQLState());
		return DB_FAIL;
	}
	return DB_SUCCESS;
}

//�������ݿ��е����а�����
//int��ʾ��Ӧ��gameLevel
//std::string��ʾ�µ�������Ϣ
//ʹ���û�ID��������
bool RankDatabase::updateToDatabase(int gameLevel, std::string rankMsg) {
	try {
		stmt = conn->createStatement();
		sql::SQLString str = "update ranking set rankByID='";
		str.append(rankMsg);
		str.append("' where gameLevel=");
		str.append(intToString(gameLevel).c_str());
		str.append(";");

		//ִ��SQL
		stmt->executeUpdate(str);

		delete stmt;
	}
	catch (sql::SQLException &e) {
		LOG(e.what());
		LOG(e.getErrorCode());
		LOG(e.getSQLState());
		delete stmt;
		return DB_FAIL;
	}
	return DB_SUCCESS;
}

//�ر����ݿ�����
void RankDatabase::close() {
	conn->close();
}

//���������а����ݿ������
bool RankDatabase::init() {
	try {
		//�������ݿ�����
		driver = get_driver_instance();
		conn = driver->connect("127.0.0.1:3306", "root", "ab123456");

		//����MySQL���ݿ�lianliankan
		conn->setSchema("lianliankan");
	} catch (sql::SQLException &e) {
		LOG(e.what())
		LOG(e.getErrorCode())
		LOG(e.getSQLState())
		return DB_FAIL;
	}
	return DB_SUCCESS;
}