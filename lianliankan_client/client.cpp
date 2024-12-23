/*
* Name: QinKuai
* Status: Unfinised
*/
#include "client.h"

//��̬������ʼ��
Client* Client::client = nullptr;

//���ص�Ĭ�Ϲ�����
Client::Client() {}

//��ȡ������ʵ����Ψһ����
Client* Client::getClientInstance() {
	if (Client::client == nullptr) {
		Client::client = new Client();
	}
	return Client::client;
}

//��ʼ���������
//�ڲ�����
bool Client::init() {
	//����Winsock
	//��дWSA��Ϣ
	WSADATA wsadata;
	int error = WSAStartup(0x0202, &wsadata);

	//�鿴�Ƿ����쳣����
	if (error) {
		return false;
	}

	//����Ƿ�����ȷ��WinSock�汾
	if (wsadata.wVersion != 0x0202) {
		WSACleanup();
		return false;
	}

	//��ʼ��Socket�������Ϣ
	//PF_INET == AF_INET
	this->addr.sin_family = PF_INET;
	this->addr.sin_port = htons(SERVER_PORT);
	inet_pton(PF_INET, SERVER_IP, &this->addr.sin_addr.s_addr);

	return true;
}

//�����������
bool Client::start() {
	//���������ʼ��
	if (!this->init()) {
		return false;
	}

	this->socket1 = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (this->socket1 == INVALID_SOCKET) {
		return false;
	}

	int result = connect(this->socket1, (SOCKADDR*)&this->addr, sizeof(this->addr));
	if (result == SOCKET_ERROR) {
		return false;
	}

	return true;
}

//�ر��������
bool Client::close() {
	if (this->socket1) {
		closesocket(this->socket1);
	}
	WSACleanup();
	return true;
}

//ͨ��ָ��command��ʵ��ͬһ������ͬʵ��
NetMsg* Client::request(NetMsg*& msg, int target, int level) {
	//������������������Ϣ
	msg->setCommand(target);

	switch (target) {
	case REGISTER:
		return this->send_register(msg);
	case LOGIN:
		return this->send_login(msg);
	case LOGOUT:
		return this->send_logout(msg);
	case USERDATA_UPDATE:
		return this->send_update(msg);
	case RANKING:
		return this->send_ranking(msg, level);
	default:
		return nullptr;
	}
}

//�û�ע��
NetMsg* Client::send_register(NetMsg*& msg) {
	NetMsg* client_recv = new NetMsg();
	
	if (!this->sendToServer(msg)) {
		return nullptr;
	}
	
	Sleep(100);

	if (!this->recvFromServer(client_recv)) {
		return nullptr;
	}
	return client_recv;
}

//�û���½
NetMsg* Client::send_login(NetMsg*& msg) {
	NetMsg* client_recv = new NetMsg();

	if (!this->sendToServer(msg)) {
		return nullptr;
	}

	Sleep(100);

	if (!this->recvFromServer(client_recv)) {
		return nullptr;
	}
	return client_recv;
}

//�û��ǳ�
NetMsg* Client::send_logout(NetMsg*& msg) {
	NetMsg* client_recv = new NetMsg();

	if (!this->sendToServer(msg)) {
		return nullptr;
	}

	Sleep(100);

	if (!this->recvFromServer(client_recv)) {
		return nullptr;
	}
	return client_recv;
}

//�û���������
NetMsg* Client::send_update(NetMsg*& msg) {
	NetMsg* client_recv = new NetMsg();

	if (!this->sendToServer(msg)) {
		return nullptr;
	}

	Sleep(100);

	if (!this->recvFromServer(client_recv)) {
		return nullptr;
	}
	return client_recv;
}

//��ȡ���а�
NetMsg* Client::send_ranking(NetMsg*& msg, int level) {
	NetMsg* client_recv = new NetMsg();

	char* send_server = new char[BUFFER_SIZE];
	memset(send_server, 0, BUFFER_SIZE);

	int counter = 0;
	//���л���Ϣ
	counter = msg->client_ranking_serialize(send_server, level);
	if (counter <= 0) {
		return nullptr;
	}

	//������Ϣ
	int result = send(this->socket1, send_server, BUFFER_SIZE, 0);
	if (result < 0) {
		return nullptr;
	}

	Sleep(100);

	//���շ������˵Ļ���
	char* recv_chars = new char[BUFFER_SIZE];
	memset(recv_chars, 0, BUFFER_SIZE);
	//������Ϣ
	result = recv(this->socket1, recv_chars, BUFFER_SIZE, 0);

	if (result < 0) {
		return nullptr;
	}
	//�����л���Ϣ
	int recvLevel = 0;
	counter = client_recv->client_ranking_deserialize(recv_chars, recvLevel);
	if (counter <= 0 || recvLevel != level) {
		return nullptr;
	}
	return client_recv;
}

bool Client::sendToServer(NetMsg*& msg) {
	char* send_server = new char[BUFFER_SIZE];
	memset(send_server, 0, BUFFER_SIZE);

	int counter = 0;
	//���л���Ϣ
	counter = msg->serialize(send_server, DEFAULT_MODE);
	if (counter <= 0) {
		return false;
	}

	//������Ϣ
	int result = send(this->socket1, send_server, BUFFER_SIZE, 0);
	if (result < 0) {
		return false;
	}
	delete[] send_server;
	return true;
}

bool Client::recvFromServer(NetMsg*& msg) {
	int result = 0;
	int counter = 0;
	char* recv_chars = new char[BUFFER_SIZE];
	memset(recv_chars, 0, BUFFER_SIZE);
	//������Ϣ
	result = recv(this->socket1, recv_chars, BUFFER_SIZE, 0);

	if (result < 0) {
		return false;
	}
	//�����л���Ϣ
	counter = msg->deserialize(recv_chars, SECRET_MODE);
	if (counter <= 0) {
		return false;
	}
	delete[] recv_chars;
	return true;
}
