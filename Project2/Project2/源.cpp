#include<iostream>
using namespace std;

int main()
{
	//�˽������
	//allocator��ϵͳ��������ģ���࣬allocator<int>()��һ����ʱ���󣬵���allocate��Ա����
	//����һ�����512���������ڴ�ռ䣬������ָ��
	int* p = allocator<int>().allocate(512, 0);


	return 0;
}