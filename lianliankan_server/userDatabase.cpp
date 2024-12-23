/*
* Name: QinKuai
* Status: Finished
*/

#include "userDatabase.h"

//��̬������ʼ��
sql::Driver* UserDatabase::driver = nullptr;
sql::Connection* UserDatabase::conn = nullptr;
sql::Statement* UserDatabase::stmt = nullptr;
sql::ResultSet* UserDatabase::res = nullptr;


UserDatabase::UserDatabase() {}

//�����ݿ��е���������UserBase��
//ʵ���û����ݹ�����list��
bool UserDatabase::databaseToUsers() {
	if (!init()) {
		LOG("���ݿ��ʼ��ʧ��")
		return DB_FAIL;
	}
	try {
		stmt =  conn->createStatement();
		res =  stmt->executeQuery("select * from users;");
		while (res->next()) {
			//�û���������
			std::string username = res->getString("username");
			std::string passwd = res->getString("password");
			User *user = new User(username, passwd);

			//�û�ID
			user->setID(res->getInt("ID"));

			//�û�����
			user->setScore(res->getInt("score"));
			user->setClearGameNumber(res->getInt("clearLevel"));
			user->charsToScoreArray(res->getString("gameScore"));

			//�û�����
			user->setCoins(res->getInt("coins"));
			user->setReconstructItemAmount(res->getInt("RecItems"));
			user->setTimeDelayItemAmount(res->getInt("TDItems"));
			user->setPropmtItemAmount(res->getInt("PTItems"));

			UserBase::getUserBase()->addUser(*user);

			//for test
			//UserBase::getUserBase()->showAll();
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

//����û���Ϣ
bool UserDatabase::addToDatabase(User& user) {
	try {
		stmt = conn->createStatement();
		sql::SQLString str = "insert into users values('";
		//�û���
		str.append(user.getUserName());
		str.append("', '");
		//�û�����
		str.append(user.getPassword());
		str.append("', ");
		//�ܷ���
		str.append(intToString(user.getScore()));
		str.append(", ");
		//�����
		str.append(intToString(user.getCoins()));
		str.append(", ");
		//��������
		str.append(intToString(user.getReconstructItemAmount()));
		str.append(", ");
		//��������
		str.append(intToString(user.getTimeDelayItemAmount()));
		str.append(", ");
		//��ͨ�صĹؿ���Ŀ
		str.append(intToString(user.getClearGameNumber()));
		str.append(", '");
		//ÿ�ַ�����ɵ��ַ���
		char temp[100];
		memset(temp, 0, 100);
		char* tempChar = temp;
		user.scoreArrayTochars(tempChar);
		str.append(tempChar);
		str.append("',");
		//�û��ڷ�������ע���ID
		str.append(intToString(user.getID()));
		str.append(", ");
		//��������
		str.append(intToString(user.getPropmtItemAmount()));
		str.append(");");

		//for check
		//std::cout << str << std::endl;
		bool result = stmt->execute(str);
		if (result) {
			delete stmt;
			return DB_FAIL;
		}
		delete stmt;
	} catch (sql::SQLException &e) {
		LOG(e.what());
		LOG(e.getErrorCode());
		LOG(e.getSQLState());
		return DB_FAIL;
	}
	return DB_SUCCESS;
}

//ɾȥ�û���Ϣ
bool UserDatabase::deleteToDatabase(User& user) {
	try {
		stmt = conn->createStatement();
		sql::SQLString str = "delete from users where username='";
		str.append(user.getUserName());
		str.append("';");

		//for check
		//std::cout << str << std::endl;
		bool result = stmt->execute(str);

		if (result) {
			delete stmt;
			return DB_FAIL;
		}
		delete stmt;
	}
	catch (sql::SQLException &e) {
		LOG(e.what());
		LOG(e.getErrorCode());
		LOG(e.getSQLState());
		return DB_FAIL;
	}
	return DB_SUCCESS;
}

//�����û���Ϣ
bool UserDatabase::updateToDatabase(User& user) {
	try {
		stmt = conn->createStatement();
		sql::SQLString str = "update users set score=";
		str.append(intToString(user.getScore()));
		str.append(", coins=");
		str.append(intToString(user.getCoins()));
		str.append(", RecItems=");
		str.append(intToString(user.getReconstructItemAmount()));
		str.append(", TDItems=");
		str.append(intToString(user.getTimeDelayItemAmount()));
		str.append(", PTItems=");
		str.append(intToString(user.getPropmtItemAmount()));
		str.append(", clearLevel=");
		str.append(intToString(user.getClearGameNumber()));
		str.append(", gameScore=");
		char temp[100];
		memset(temp, 0, 100);
		char* tempChar = temp;
		user.scoreArrayTochars(tempChar);
		str.append("'");
		str.append(tempChar);
		str.append("'");
		str.append(" where username='");
		str.append(user.getUserName());
		str.append("';");

		//for check
		//std::cout << str << std::endl;
		int result = stmt->executeUpdate(str);
		if (!result) {
			return DB_FAIL;
		}
		delete stmt;
	}
	catch (sql::SQLException &e) {
		LOG(e.what());
		LOG(e.getErrorCode());
		LOG(e.getSQLState());
		return DB_FAIL;
	}
	return DB_SUCCESS;
}

//�˷������ر����ݿ�����
void UserDatabase::close() {
	conn->close();
}

//�����û����ݿ����ʱ��ʼ�������ݿ������
bool UserDatabase::init() {
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
