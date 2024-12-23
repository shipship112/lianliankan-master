/*
* Name: QinKuai
* Status: Unfinished
*/
#include "server.h"
#include "netMsg.h"
#include "userDatabase.h"
#include "rankDatabase.h"

using namespace std;

DWORD WINAPI start(LPVOID para) {
	static_cast<Server*>(para)->start();
	//_CrtDumpMemoryLeaks();
	return 0L;
}

//���������
int main(void) {
	//�ȼ����û����ݿ��е���Ϣ
	if (!UserDatabase::databaseToUsers()) {
		LOG("�û����ݳ�ʼ��ʧ��")
		system("pause");
		return -1;
	}
	LOG("�û����ݿ��ʼ���ɹ�")

	//�ȼ������а����ݿ��е���Ϣ
	if (!RankDatabase::databaseToRanking()) {
		LOG("���а����ݿ��ʼ��ʧ��")
		system("pause");
		return -1;
	}
	LOG("���а����ݿ��ʼ���ɹ�")

	Server* server = new Server();

	//�����������û�������߳�
	HANDLE newThread = CreateThread(NULL, 0, start, server, 0, NULL);
	CloseHandle(newThread);

	//���̼߳����������Ӧ�Ĳ���
	string cmd = "";
	while (true) {
		//�ȴ��û�����ָ��
		cin >> cmd;
		if (!strcmp(cmd.c_str(), HELP)) {
			HELPMSG
		} else if (!strcmp(cmd.c_str(), EXIT)) {
			server->close();
			delete server;
			//_CrtDumpMemoryLeaks();
			system("pause");
			return 0;
		} else {
			CMDERROR
		}
	}
}