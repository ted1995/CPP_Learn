#pragma once
#include<iostream>
#include"connect.h"
#include<string>
#include<queue>
#include<atomic>	//c++11��ԭ�ӱ���
#include<mutex>		//c++11��������
#include<thread>	//c++11�����߳�
#include<memory>	//
#include<functional>
#include<condition_variable>
using namespace std;


//���ݿ����ӳ�ʵ��
class connpool
{
public:
	//����ģʽ����ȡ���ӳض���
	static connpool* get_connpool();

	//�û����connect���Ӷ���Ľӿ�
	//shared_ptr����ָ�룬���Խ�new�����Ķ����Զ��ͷŵ�
	shared_ptr<myconnect> get_connect();

	

private:

	//���캯��˽�л�������ģʽ
	connpool();

	//���������ļ�
	bool load_config();

	//��������һ���̣߳�������������
	void prod_conn_thread();

	//
	void scanner_conn_thread();

	//ɾ�����ӳ��п���ʱ����õ����ӵ��߳�
	void del_conn_thread();

	//
	string ip;
	short port;
	string user;
	string password;
	string dbname;
	int initsize;	//��ʼ������
	int maxsize;	//���������
	int max_freetime;	//������ʱ��
	int max_overtime;	//���ӳ�ʱʱ��

	//�洢mysql���ӵĶ���
	queue<myconnect*> conn_queue;
	//���л�����
	mutex queue_mutex;
	//atomic_int�������ԭ�ӱ������Դ˱����Ĳ�������ԭ�Ӳ���
	atomic_int conn_count;
	//��������-���������ߺ��������̼߳��ͨ��
	condition_variable cv;


};