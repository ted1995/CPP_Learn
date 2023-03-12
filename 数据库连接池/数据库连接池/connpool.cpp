#pragma once
#include"connpool.h"
#include<functional>


connpool* connpool::get_connpool()
{
	//���ؾ�̬���ӳ���ʵ������
	static connpool pool;
	return &pool;
}

shared_ptr<myconnect> connpool::get_connect()
{
	unique_lock<mutex> lock(queue_mutex);

	//���ӳ�Ϊ�գ������ȴ��������ӣ�����һ��ʱ��Ͳ��ٵȴ���ֱ�ӷ���
	while (conn_queue.empty())
	{
		//�����ȴ����߳�ʱ������ֵΪcv_status::timeout˵���ȴ���ʱ
		if (cv.wait_for(lock, chrono::milliseconds(max_overtime)) == cv_status::timeout)
		{
			if (conn_queue.empty())
			{
				cout << "������ӳ�ʱ" << endl;
				return NULL;
			}
		}
	}

	//����shared_ptr���ԣ�����������Զ������ǽ�����ֱ�����٣�������Ҫ�ﵽ��Ŀ����
	//Ҫ�����ӹ黹������Ҫ�Զ���ɾ����,ʹ��lamboda���ʽ������ɾ����
	shared_ptr<myconnect> sp(conn_queue.front(),
		[&](myconnect *pcon) {
		//�����Ƿ�����Ӧ���̵߳��õģ�����һ��Ҫע���̰߳�ȫ����
		unique_lock<mutex> lock(queue_mutex);
		pcon->start_freetime();
		conn_queue.push(pcon);
	});

	conn_queue.pop();
	cv.notify_all();
	return sp;

}


bool connpool::load_config()
{
	FILE* filefd = fopen("mysql.ini", "r");
	if (filefd == NULL)
	{
		return false;
	}

	while (!feof(filefd))
	{
		//ȡһ������
		char line[1024] = { 0 };
		fgets(line, 1024, filefd);
		string str = line;
		//��λ��=λ��
		int index = str.find('=', 0);
		if (index == -1)
		{
			continue;
		}
		//��λ�����еĽ�β
		int end_index = str.find('\n', index);
		//���Ⱥ�ǰ���ֵ�ͺ����ֵ�ֱ�浽key��value��
		string key = str.substr(0, index);
		string value = str.substr(index + 1, end_index - index - 1);
		if (key == "ip")
		{
			ip = value;
		}
		else if (key == "port")
		{
			port = atoi(value.c_str());
		}
		else if (key == "username")
		{
			user = value;
		}
		else if (key == "password")
		{
			password = value;
		}
		else if (key == "dbname")
		{
			dbname = value;
		}
		else if (key == "initsize")
		{
			initsize = atoi(value.c_str());
		}
		else if (key == "maxsize")
		{
			maxsize = atoi(value.c_str());
		}
		else if (key == "max_freetime")
		{
			max_freetime = atoi(value.c_str());
		}
		else if (key == "max_overtime")
		{
			max_overtime = atoi(value.c_str());
		};
	}
	return true;
}


void connpool::prod_conn_thread()
{
	for (;;)
	{
		//unique_lock��c++11�����ԣ���ģ�壬������lock_guard
		unique_lock<mutex> lock(queue_mutex);
		//sql���Ӷ��в�Ϊ��,��һֱ������ֻ�����������յ�֪ͨ���ٴ��ж�while���������ż������£�����ٻ��ѣ�����һ��Ҫ��while������if
		while (!conn_queue.empty())
		{
			//�ȴ���������������
			cv.wait(lock);
		}

		//�������Ϊ�գ��ʹ���������,�Ҵ��������Ӳ��ܳ�������
		if (conn_count < maxsize)
		{
			//��������
			myconnect* conn = new myconnect();
			conn->connect_sql(ip, port, user, password, dbname);
			//��ʼ��ʱ����ʱ��
			conn->start_freetime();
			//���������
			conn_queue.push(conn);
			conn_count++;
		}

		//֪ͨ������ȡ����
		cv.notify_all();
	}
}


void connpool::scanner_conn_thread()
{
	for (;;)
	{
		//c++11��this_thread���õ�ǰ�̣߳�sleep_for˯�߸�����ʱ�䣬��Ϊ��ʱ��������
		this_thread::sleep_for(chrono::seconds(max_freetime));
		//ɨ�����Ӷ��У��ͷŶ���Ŀ�������
		unique_lock<mutex> lock(queue_mutex);
		while (conn_count > initsize && !conn_queue.empty())
		{
			myconnect* p = conn_queue.front();

			//���������������ʱ�䣬�ͽ����ӳ���
			if (p->get_alivetime() > (1000 * max_freetime))
			{
				conn_queue.pop();
				conn_count--;
				delete p;
			}
			else
			{
				//��ͷδ��ʱ��������Ԫ��Ҳδ��ʱ��
				break;
			}
		}

	}
}


connpool::connpool()
{
	cout << "���캯����ʼ��" << endl;
	conn_count = 0;
	//��ȡ�����ļ�ʧ��
	if (!load_config())
	{
		return;
	}

	//��ȡ�ɹ���������ʼ������
	for (int i = 0; i < initsize; i++)
	{
		//����һ��������ʵ������
		myconnect* c = new myconnect();
		//����ز��������������У��������ݿ�����
		c->connect_sql(ip, port, user, password, dbname);
		//�����Ӷ��������У��γ����ӳ�
		conn_queue.push(c);
		//��ʼ��ʱ����ʱ��
		c->start_freetime();
		//���Ӽ���
		conn_count++;
	}

	//����һ�����߳���������initsize����������
	//ʹ��std::bind�󶨣�����һ���Ѿ���ǰ���˵��ò����ĺ�������
	//���ô˺���������ǵ���ʹ�ð󶨲����ĺ���
	auto f1 = std::bind(&connpool::prod_conn_thread, this);
	thread producer(f1);
	producer.detach();

	//����һ�����̣߳����ճ�������ʱ�������
	//��ʹ��std::bindҲ����
	//thread����ͨ������ֱ��ʹ�ú���������,�󶨳�Ա��������Ҫʹ�ó�Ա�����ĺ�����ַ�Լ���Ա���������Ķ���
	thread scanner(&connpool::scanner_conn_thread,this);
	scanner.detach();
}