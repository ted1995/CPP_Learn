#pragma once
#include<iostream>
#include"connect.h"
#include<string.h>

using namespace std;

myconnect::myconnect()
{
	//初始化数据库连接
	//mysql_init属于mysql库函数，初始化一个MYSQL连接的实例对象
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
	//mysql_real_connect属于mysql库函数，连接数据库，如果连接成功，返回MYSQL*连接句柄。如果连接失败，返回NULL。对于成功的连接，返回值与第1个参数的值相同。
	MYSQL* temp = mysql_real_connect(mysql, ip.c_str(), user.c_str(), password.c_str(), dbname.c_str(), port, NULL, 0);
	const char* a = mysql_error(mysql);
	cout << a << endl;
	return temp != NULL;
}


bool myconnect::myupdate(string sql)
{
	if (mysql_query(mysql, sql.c_str()))
	{
		cout << "更新失败：" << sql << endl;
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
		cout << "查询失败：" << sql << endl;
		return NULL;
	}
	return mysql_use_result(mysql);
}

