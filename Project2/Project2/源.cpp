#include<iostream>
using namespace std;

int main()
{
	//了解分配器
	//allocator是系统分配器的模板类，allocator<int>()是一个临时对象，调用allocate成员函数
	//分配一个存放512个整数的内存空间，返回其指针
	int* p = allocator<int>().allocate(512, 0);


	return 0;
}