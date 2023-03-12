#include<iostream>
using namespace std;
//任务结构体
class task
{

};

//信号量结构体
class sema
{
public:
	int value;
	task* queue;
};

void block(task*t)
{

}

void wakeup(task*t)
{

}

void p(sema& s)
{
	//资源减1，如果值小于0，阻塞任务
	s.value--;
	if (s.value < 0)
	{
		block(s.queue);
	}
}

//s.value小于0，则其绝对值表示等待队列的进程数

void v(sema& s)
{
	//资源加1，如果值小于等于0，唤醒任务
	s.value++;
	if (s.value <= 0)
	{
		wakeup(s.queue);
	}
}

int main()
{
	//1.当value的初始值是1，信号量可以当成互斥量使用

	//2.当value的初值是0，两个程序一个用v，一个用p，进行程序同步

	return 0;
}