#pragma once
#include<string>
#include<iostream>
#include<mysql.h>
#include<time.h>
using namespace std;

class myconnect
{
public:
	//初始数据库连接
	myconnect();
	//释放数据库连接资源
	~myconnect();
	//连接数据库
	bool connect_sql(string ip, short port, string user, string password, string dbname);
	//更新操作insert，delete，update
	bool myupdate(string sql);
	//查询操作
	MYSQL_RES* query(string sql);
	//刷新连接的起始空闲时间
	void start_freetime();
	//返回存活时间
	clock_t get_alivetime();
	//
	MYSQL_RES* myquery(string sql);
private:
	//mysql是一个数据库连接
	MYSQL* mysql;
	//起始空闲时间
	clock_t alivetime;
};

