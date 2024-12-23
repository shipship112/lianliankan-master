/*
* Name: QinKuai
* Status: Finished
*/
#include "server.h"

Server::Server() {}

Server::~Server() {}

/*
��ʼ����������������
*/
bool Server::init() {
	//����Winsock
	//��дWSA��Ϣ
	WSADATA wsadata;
	int error = WSAStartup(0x0202, &wsadata);

	//�鿴�Ƿ����쳣����
	if (error) {
		LOG("Winsock�����쳣")
		return false;
	}
	if (wsadata.wVersion != 0x0202) {
		//���Winsock
		WSACleanup();
		LOG("Winsock�汾�쳣")
		return false;
	}

	//��ʼ��TCP socket�Ľṹ
	//PF_INET == AF_INET
	this->addr.sin_family = PF_INET;
	this->addr.sin_port = htons(SERVER_PORT);
	inet_pton(PF_INET, SERVER_IP, &this->addr.sin_addr.s_addr);

	//����socket
	this->socket1 = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	//����socketʧ��
	if (socket1 == INVALID_SOCKET) {
		LOG("Socket����ʧ��")
		return false;
	}

	//��Socket
	if (bind(this->socket1, (LPSOCKADDR)&this->addr, sizeof(this->addr)) == SOCKET_ERROR) {
		LOG("Socket�޷���")
		return false;
	}	

	int ret = listen(this->socket1, 1);

	if (ret == SOCKET_ERROR) {
		LOG("Socket����ʧ��")
		return false;
	}

	return true;
}

/*
��������������֮��
���ø÷���
��ʼ�������������Ϣ
����ʼ�����ͻ�������
*/
void Server::start() {
	if (!this->init()){
		LOG("��������ʼ��ʧ��")
		return;
	}

	LOG("��������ʼ�����")

	//��ʽ��ʼ�����ͻ�����Ϣ
	//������
	char* recv_buf = new char[BUFFER_SIZE];
	//�����ͻ��˻�����
	char* send_buf = new char[BUFFER_SIZE];
	//���������а�
	//�����ؿ������Ϣ
	int level = 0;

	while (true) {
		//socekt�Ͽ�ֱ���˳�����������
		if (!this->socket1) {
			delete[] recv_buf;
			break;
		}
		//��������ʼ�����ǻ���������
		memset(recv_buf, 0, BUFFER_SIZE);
		memset(send_buf, 0, BUFFER_SIZE);

		SOCKADDR_IN client_addr;
		socklen_t client_length = sizeof(client_addr);
		LOG("������������")
		SOCKET client = accept(this->socket1, (struct sockaddr*)&client_addr, &client_length);
		if (client == SOCKET_ERROR) {
			LOG("����������Ͽ�")
			break;
		}
		char log[INET_ADDRSTRLEN];
		std::string str = inet_ntop(PF_INET, &client_addr.sin_addr, log, sizeof(log));
		str += "���������";
		LOG(str)
		int len = recv(client, recv_buf, BUFFER_SIZE, 0);
		
		//���������л�����
		//ȷ���ͻ�����������
		NetMsg *client_request = new NetMsg();
		//���ͻ���������Ϣ
		//���Ƚ���command�Ľ���
		//����ȷ����������
		int command = client_request->command_deserialize(recv_buf);
		if (command !=RANKING ) {
			//�����л����ص�������
			client_request->deserialize(recv_buf, DEFAULT_MODE);
		} else {
			//�����û����������а�����
			client_request->server_ranking_deserialize(recv_buf, level);
		}

		//�����ͻ���ʱ�����л�����ָ��
		NetMsg *send_back = nullptr;

		//��ʱ��client_request�Ѿ�ʱ�����õ�NetMsg������
		switch (command) {
		case REGISTER:
			//��������ʵ���û�ע��
			 send_back = userRegister(client_request);

			send_back->serialize(send_buf, SECRET_MODE);
			//��ͻ��˷���ע�����
			send(client, send_buf, BUFFER_SIZE, 0);
				
			delete client_request;
			delete send_back;
			continue;
		case LOGIN:
			//��������ʵ���û���½
			 send_back = userLogin(client_request);

			 send_back->serialize(send_buf, SECRET_MODE);
			 //��ͻ��˷�����½���
			 send(client, send_buf, BUFFER_SIZE, 0);
			 
			 delete client_request;
			 delete send_back;
			continue;
		case LOGOUT:
			//��������ʵ���û��ǳ�
			 send_back = userLogout(client_request);

			 send_back->serialize(send_buf, SECRET_MODE);
			 //��ͻ��˷����ǳ����
			 send(client, send_buf, BUFFER_SIZE, 0);

			 delete client_request;
			 delete send_back;
			continue;
		case USERDATA_UPDATE:
			//��������ʵ���û����ݸ���
			 send_back = userdataUpdate(client_request);

			 send_back->serialize(send_buf, SECRET_MODE);
			 //��ͻ��˷����û����ݸ������
			 send(client, send_buf, BUFFER_SIZE, 0);
			 
			 delete client_request;
			 delete send_back;
			continue;
		case RANKING:
			//��������ʵ����������
			send_back = userRanking(client_request, level);

			send_back->server_ranking_serialize(send_buf, level);
			//��ͻ��˷����������
			send(client, send_buf, BUFFER_SIZE, 0);

			delete client_request;
			delete send_back;
			continue;
		}
	}

	delete[] recv_buf;
	delete[] send_buf;
}

/*
������ͣ�÷���
*/
void Server::close() {
	if (this->socket1) {
		closesocket(this->socket1);
	}
	WSACleanup();
	Sleep(100);
	//�ر����ݿ�����
	UserDatabase::close();
	RankDatabase::close();
	LOG("���ݿ����������ر�")
	//������ߴ洢����Ϣ
	delete UserBase::getUserBase();
	delete RankBase::getRankBase();
	LOG("�����������˳�")
}

/*
�����ע�᷽��
*/
NetMsg* Server::userRegister(NetMsg* msg) {
	User *user = &msg->getUsers().front();
	//�������˵ı���LOG��Ϣ
	std::string log = user->getUserName();
	LOG(log + " ����ע��")

	NetMsg* send_back = new NetMsg();

	//��ѯUserBase���Ƿ�����ͬ�û������û�
	if (UserBase::getUserBase()->findUser(user->getUserName()) != nullptr) {
		send_back->setCommand(REGISTER_FAIL);
		log.append(" �û����Ѵ��ڣ�ע��ʧ��");
		LOG(log)
		return send_back;
	}

	//ȷ����ע���õ�ID
	user->setID(UserBase::getUserBase()->getUsersLength() + 1);

	//д�����ݿ���
	bool result = UserDatabase::addToDatabase(*user);
	if (!result) {
		send_back->setCommand(REGISTER_FAIL);
		log.append(" д���û����ݿ�ʧ�ܣ�ע��ʧ��");
		LOG(log)
		return send_back;
	}

	//��ӵ�UserBase��
	UserBase::getUserBase()->addUser(*user);

	//��ӵ�RankBase��
	RankBase::getRankBase()->insertToRankBase(user->getID());

	//д�����а����ݿ�
	std::string str("");
	//i��ʾgameLevel
	for (int i = 0; i <= GAMEAMOUNT; i++) {
		str = RankBase::getRankBase()->scoreRankToString(i);
		result = RankDatabase::updateToDatabase(i, str);
		if (!result) {
			send_back->setCommand(REGISTER_FAIL);
			log.append(" д�����а����ݿ�ʧ�ܣ�ע��ʧ��");
			LOG(log)
			return send_back;
		}
	}
	
	send_back->setCommand(REGISTER_SUCCESS);
	log.append(" ע��ɹ�");
	LOG(log)
	return send_back;
}

/*
����˵�½����
*/
NetMsg* Server::userLogin(NetMsg* msg) {
	User* user = &msg->getUsers().front();
	//�������˵ı���LOG��Ϣ
	std::string log = user->getUserName();
	LOG(log + " �����½")

	NetMsg* send_back = new NetMsg();

	//��UserBase��ά����list�в�ѯ�û��Ƿ����
	User* user_send_back = UserBase::getUserBase()->findUser(user->getUserName(), user->getPassword());
	if (user_send_back == nullptr) {
		send_back->setCommand(LOGIN_FAIL);
		log.append(" �û��������������󣬵�½ʧ��");
		LOG(log)
		return send_back;
	}

	//���ҳɹ���������˺�֮��ȷ���û���½
	user_send_back->setLoginStatus(true);

	//�������ҵ����û��෵���ͻ���
	send_back->setCommand(LOGIN_SUCCESS);
	send_back->addUserToList(*user_send_back);

	log.append(" ��½�ɹ�");
	LOG(log)

	return send_back;
}

/*
����˵ǳ�����
*/
NetMsg* Server::userLogout(NetMsg* msg) {
	User* user = &msg->getUsers().front();
	//�������˵ı���LOG��Ϣ
	std::string log = user->getUserName();
	LOG(log + " ����ǳ�")

	NetMsg* send_back = new NetMsg();

	//���û��ĵ�½״̬����Ϊ�ǳ�
	User* user_in_server = UserBase::getUserBase()->findUser(user->getUserName(), user->getPassword());
	if (user_in_server == nullptr) {
		send_back->setCommand(LOGOUT_FAIL);
		log.append("�û�����������󣬵ǳ�ʧ��");
		LOG(log)
		return send_back;
	}
	user_in_server->setLoginStatus(false);

	//���õǳ��ɹ�
	send_back->setCommand(LOGOUT_SUCCESS);

	log.append(" �ǳ��ɹ�");
	LOG(log)
	return send_back;
}


/*
��������ݸ��·���
*/
NetMsg* Server::userdataUpdate(NetMsg* msg) {
	User* user = &msg->getUsers().front();
	//�������˵ı���LOG��Ϣ
	std::string log = user->getUserName();
	LOG(log + " �������ݸ���")

	NetMsg* send_back = new NetMsg();

	//����ָ����û���ָ��
	//ͬʱ����check�Ƿ��и��û�
	User* user_in_server = UserBase::getUserBase()->findUser(user->getUserName(), user->getPassword());

	if (user_in_server == nullptr) {
		send_back->setCommand(USERDATA_UPDATE_FAIL);
		log.append(" �û���������������ݸ���ʧ��");
		LOG(log)
		return send_back;
	}
	
	//�������ݿ��е��û�����
	bool result = UserDatabase::updateToDatabase(*user);

	if (!result) {
		log.append(" �û����ݿ��쳣�����ݸ���ʧ��");
		LOG(log)
		send_back->setCommand(USERDATA_UPDATE_FAIL);
		return send_back;
	}

	//�����û���Ϣ
	//���������Ϣ
	user_in_server->setCoins(user->getCoins());
	user_in_server->setReconstructItemAmount(user->getReconstructItemAmount());
	user_in_server->setTimeDelayItemAmount(user->getTimeDelayItemAmount());
	//���·��������Ϣ
	user_in_server->setScore(user->getScore());
	user_in_server->setClearGameNumber(user->getClearGameNumber());
	for (int i = 1; i <= GAMEAMOUNT; i++) {
		user_in_server->setGameScore(user->getGameScore(i), i);
	}

	//��ӵ�RankBase��
	RankBase::getRankBase()->updateToRankBase(user_in_server->getID());

	//д��RankDatabase��
	//д�����а����ݿ�
	std::string str("");
	//i��ʾgameLevel
	for (int i = 0; i <= GAMEAMOUNT; i++) {
		str = RankBase::getRankBase()->scoreRankToString(i);
		result = RankDatabase::updateToDatabase(i, str);
		if (!result) {
			send_back->setCommand(USERDATA_UPDATE_FAIL);
			log.append(" д�����а����ݿ�ʧ�ܣ����ݸ���ʧ��");
			LOG(log)
			return send_back;
		}
	}

	//�������ݸ��³ɹ�
	send_back->setCommand(USEREDATA_UPDATE_SUCCESS);

	log.append(" ���ݸ��³ɹ�");
	LOG(log)
	return send_back;
}


/*
���������а�����
*/
NetMsg* Server::userRanking(NetMsg* msg, int level) {
	User* user = &msg->getUsers().front();
	NetMsg *send_back = new NetMsg();
	
	std::string log = user->getUserName();
	LOG(log + " �����û����а�")

	//����ָ����û���ָ��
	//ͬʱ����check�Ƿ��и��û�
	User* user_in_server = UserBase::getUserBase()->findUser(user->getUserName());

	if (user_in_server == nullptr) {
		send_back->setCommand(RANKING_FAIL);
		log.append(" �û�����������󣬻�ȡ���а�ʧ��");
		LOG(log)
		return send_back;
	}

	std::vector<int> ranking = RankBase::getRankBase()->getRankByLevel(level);
	for (std::vector<int>::iterator it =ranking.begin(); it < ranking.end(); it++) {
		User* newUser = new User("", "");
		int id = *it;
		//���а��ڴ˴�û�ж�Ӧ�û�
		//���ؿ��ַ�����0
		if (id == 0) {
			newUser->setUserName("NULL");
			newUser->setRankScore(0, level);
		} else {
			User* user_in_server = UserBase::getUserBase()->findUser(id);
			newUser->setID(id);
			newUser->setRankScore(user_in_server->getRankScore(level), level);
			newUser->setUserName(user_in_server->getUserName());
		}

		send_back->addUserToList(*newUser);
	}

	
	send_back->setCommand(RANKING_SUCCESS);
	log.append(" �������а����ݳɹ�");
	LOG(log)
	return send_back;
}