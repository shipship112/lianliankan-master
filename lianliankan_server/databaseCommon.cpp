/*
* Name: QinKuai
* Status: Finished
*/
#include "databaseCommon.h"

//ʵ��int��string��ת��
//���㷭��Ϊsql���
std::string intToString(const int number) {
	std::stringstream ss;
	ss << number;
	return ss.str();
}