#pragma once
#include<iostream>
#include"connect.h"
#include<string>
#include<queue>
#include<atomic>	//c++11，原子变量
#include<mutex>		//c++11，互斥量
#include<thread>	//c++11，多线程
#include<memory>	//
#include<functional>
#include<condition_variable>
using namespace std;


//数据库连接池实现
class connpool
{
public:
	//单例模式，获取连接池对象
	static connpool* get_connpool();

	//用户获得connect连接对象的接口
	//shared_ptr智能指针，可以将new出来的对象自动释放掉
	shared_ptr<myconnect> get_connect();

	

private:

	//构造函数私有化，单例模式
	connpool();

	//加载配置文件
	bool load_config();

	//单独运行一个线程，用于生产连接
	void prod_conn_thread();

	//
	void scanner_conn_thread();

	//删除连接池中空闲时间过久的连接的线程
	void del_conn_thread();

	//
	string ip;
	short port;
	string user;
	string password;
	string dbname;
	int initsize;	//初始连接量
	int maxsize;	//最大连接量
	int max_freetime;	//最大空闲时间
	int max_overtime;	//连接超时时间

	//存储mysql连接的队列
	queue<myconnect*> conn_queue;
	//队列互斥量
	mutex queue_mutex;
	//atomic_int定义的是原子变量，对此变量的操作都是原子操作
	atomic_int conn_count;
	//条件变量-用于生产者和消费者线程间的通信
	condition_variable cv;


};