#pragma once
#include<string>
#include<iostream>
#include<mysql.h>
#include<time.h>
using namespace std;

class myconnect
{
public:
	//��ʼ���ݿ�����
	myconnect();
	//�ͷ����ݿ�������Դ
	~myconnect();
	//�������ݿ�
	bool connect_sql(string ip, short port, string user, string password, string dbname);
	//���²���insert��delete��update
	bool myupdate(string sql);
	//��ѯ����
	MYSQL_RES* query(string sql);
	//ˢ�����ӵ���ʼ����ʱ��
	void start_freetime();
	//���ش��ʱ��
	clock_t get_alivetime();
	//
	MYSQL_RES* myquery(string sql);
private:
	//mysql��һ�����ݿ�����
	MYSQL* mysql;
	//��ʼ����ʱ��
	clock_t alivetime;
};

