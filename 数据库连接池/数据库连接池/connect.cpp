#pragma once
#include<iostream>
#include"connect.h"
#include<string.h>

using namespace std;

myconnect::myconnect()
{
	//��ʼ�����ݿ�����
	//mysql_init����mysql�⺯������ʼ��һ��MYSQL���ӵ�ʵ������
	mysql = mysql_init(NULL);
}

myconnect::~myconnect()
{
	if (mysql != NULL)
	{
		mysql_close(mysql);
	}
}

bool myconnect::connect_sql(string ip, short port, string user, string password, string dbname)
{
	//mysql_real_connect����mysql�⺯�����������ݿ⣬������ӳɹ�������MYSQL*���Ӿ�����������ʧ�ܣ�����NULL�����ڳɹ������ӣ�����ֵ���1��������ֵ��ͬ��
	MYSQL* temp = mysql_real_connect(mysql, ip.c_str(), user.c_str(), password.c_str(), dbname.c_str(), port, NULL, 0);
	const char* a = mysql_error(mysql);
	cout << a << endl;
	return temp != NULL;
}


bool myconnect::myupdate(string sql)
{
	if (mysql_query(mysql, sql.c_str()))
	{
		cout << "����ʧ�ܣ�" << sql << endl;
		return false;
	}
	return true;
}

void myconnect::start_freetime() 
{
	alivetime = clock();
}


clock_t myconnect::get_alivetime()
{
	return clock() - alivetime;
}




MYSQL_RES* myconnect::myquery(string sql)
{
	if (mysql_query(mysql, sql.c_str()))
	{
		cout << "��ѯʧ�ܣ�" << sql << endl;
		return NULL;
	}
	return mysql_use_result(mysql);
}

