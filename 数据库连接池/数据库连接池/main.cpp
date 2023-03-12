#pragma once
#include<iostream>
#include<ctime>
#include<thread>
#include"connect.h"
#include"connpool.h"

int main()
{
	clock_t begin = clock();

	thread t1([]()
	{
		connpool* p = connpool::get_connpool();
		for (int i = 0; i < 250; i++)
		{
			//通过数据库连接池进行连接
			/*shared_ptr<myconnect> conn = p->get_connect();
			char sql[1024] = { 0 };
			sprintf(sql, "insert into users(name,sex,age) values('%s','%s',%d)",
				"lisi", "w", 20);
			conn->myupdate(sql);*/
		
			//普通连接
			myconnect conn;
			char sql[1024] = { 0 };
			sprintf(sql, "insert into users(name,sex,age) values('%s','%s',%d)",
				"lisi", "w", 20);
			conn.connect_sql("127.0.0.1", 3306, "root", "123456", "chat");
			conn.myupdate(sql);
		}

	});

	thread t2([]()
	{
		connpool* p = connpool::get_connpool();
		for (int i = 0; i < 250; i++)
		{
			//通过数据库连接池进行连接
			/*shared_ptr<myconnect> conn = p->get_connect();
			char sql[1024] = { 0 };
			sprintf(sql, "insert into users(name,sex,age) values('%s','%s',%d)",
				"lisi", "w", 20);
			conn->myupdate(sql);*/


			//普通连接
			myconnect conn;
			char sql[1024] = { 0 };
			sprintf(sql, "insert into users(name,sex,age) values('%s','%s',%d)",
				"lisi", "w", 20);
			conn.connect_sql("127.0.0.1", 3306, "root", "123456", "chat");
			conn.myupdate(sql);
		}
	});

	thread t3([]()
	{
		connpool* p = connpool::get_connpool();
		for (int i = 0; i < 250; i++)
		{
			//通过数据库连接池进行连接
			/*shared_ptr<myconnect> conn = p->get_connect();
			char sql[1024] = { 0 };
			sprintf(sql, "insert into users(name,sex,age) values('%s','%s',%d)",
				"lisi", "w", 20);
			conn->myupdate(sql);*/


			//普通连接
			myconnect conn;
			char sql[1024] = { 0 };
			sprintf(sql, "insert into users(name,sex,age) values('%s','%s',%d)",
				"lisi", "w", 20);
			conn.connect_sql("127.0.0.1", 3306, "root", "123456", "chat");
			conn.myupdate(sql);
		}
	});


	thread t4([]()
	{
		connpool* p = connpool::get_connpool();
		for (int i = 0; i < 250; i++)
		{
			//通过数据库连接池进行连接
			/*shared_ptr<myconnect> conn = p->get_connect();
			char sql[1024] = { 0 };
			sprintf(sql, "insert into users(name,sex,age) values('%s','%s',%d)",
				"lisi", "w", 20);
			conn->myupdate(sql);*/


			//普通连接
			myconnect conn;
			char sql[1024] = { 0 };
			sprintf(sql, "insert into users(name,sex,age) values('%s','%s',%d)",
				"lisi", "w", 20);
			conn.connect_sql("127.0.0.1", 3306, "root", "123456", "chat");
			conn.myupdate(sql);
		}
	});

	t1.join();
	t2.join();
	t3.join();
	t4.join();
	clock_t end = clock();

	cout << end - begin << "ms" << endl;


	return 0;
}