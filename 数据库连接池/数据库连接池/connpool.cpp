#pragma once
#include"connpool.h"
#include<functional>


connpool* connpool::get_connpool()
{
	//返回静态连接池类实例对象
	static connpool pool;
	return &pool;
}

shared_ptr<myconnect> connpool::get_connect()
{
	unique_lock<mutex> lock(queue_mutex);

	//连接池为空，条件等待可用连接，超过一定时间就不再等待，直接返回
	while (conn_queue.empty())
	{
		//条件等待或者超时，返回值为cv_status::timeout说明等待超时
		if (cv.wait_for(lock, chrono::milliseconds(max_overtime)) == cv_status::timeout)
		{
			if (conn_queue.empty())
			{
				cout << "获得连接超时" << endl;
				return NULL;
			}
		}
	}

	//对于shared_ptr而言，出作用域后自动析构是将连接直接销毁，而我们要达到的目的是
	//要将连接归还，所以要自定义删除器,使用lamboda表达式来定义删除器
	shared_ptr<myconnect> sp(conn_queue.front(),
		[&](myconnect *pcon) {
		//这里是服务器应用线程调用的，所以一定要注意线程安全问题
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
		//取一行内容
		char line[1024] = { 0 };
		fgets(line, 1024, filefd);
		string str = line;
		//定位到=位置
		int index = str.find('=', 0);
		if (index == -1)
		{
			continue;
		}
		//定位到此行的结尾
		int end_index = str.find('\n', index);
		//将等号前面的值和后面的值分别存到key和value中
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
		//unique_lock是c++11新特性，类模板，类似于lock_guard
		unique_lock<mutex> lock(queue_mutex);
		//sql连接队列不为空,就一直阻塞，只有条件变量收到通知且再次判断while条件成立才继续向下，避免假唤醒，所以一定要用while而不是if
		while (!conn_queue.empty())
		{
			//等待条件变量，阻塞
			cv.wait(lock);
		}

		//如果队列为空，就创建新连接,且创建的连接不能超过限制
		if (conn_count < maxsize)
		{
			//创建连接
			myconnect* conn = new myconnect();
			conn->connect_sql(ip, port, user, password, dbname);
			//开始计时空闲时间
			conn->start_freetime();
			//新连接入队
			conn_queue.push(conn);
			conn_count++;
		}

		//通知消费者取连接
		cv.notify_all();
	}
}


void connpool::scanner_conn_thread()
{
	for (;;)
	{
		//c++11，this_thread引用当前线程，sleep_for睡眠给定的时间，作为定时器，定期
		this_thread::sleep_for(chrono::seconds(max_freetime));
		//扫描连接队列，释放多余的空闲连接
		unique_lock<mutex> lock(queue_mutex);
		while (conn_count > initsize && !conn_queue.empty())
		{
			myconnect* p = conn_queue.front();

			//如果超出了最大空闲时间，就将连接出队
			if (p->get_alivetime() > (1000 * max_freetime))
			{
				conn_queue.pop();
				conn_count--;
				delete p;
			}
			else
			{
				//队头未超时，则其他元素也未超时。
				break;
			}
		}

	}
}


connpool::connpool()
{
	cout << "构造函数初始化" << endl;
	conn_count = 0;
	//读取配置文件失败
	if (!load_config())
	{
		return;
	}

	//读取成功，创建初始的连接
	for (int i = 0; i < initsize; i++)
	{
		//创建一个连接类实例对象
		myconnect* c = new myconnect();
		//将相关参数传到连接类中，进行数据库连接
		c->connect_sql(ip, port, user, password, dbname);
		//将连接对象加入队列，形成连接池
		conn_queue.push(c);
		//开始计时空闲时间
		c->start_freetime();
		//连接计数
		conn_count++;
	}

	//创建一个新线程生产超出initsize数量的连接
	//使用std::bind绑定，返回一个已经提前绑定了调用参数的函数对象
	//调用此函数对象就是调用使用绑定参数的函数
	auto f1 = std::bind(&connpool::prod_conn_thread, this);
	thread producer(f1);
	producer.detach();

	//创建一个新线程，回收超出空闲时间的连接
	//不使用std::bind也可以
	//thread绑定普通函数，直接使用函数名即可,绑定成员函数，需要使用成员函数的函数地址以及成员函数所属的对象
	thread scanner(&connpool::scanner_conn_thread,this);
	scanner.detach();
}