#include<iostream>
using namespace std;
//����ṹ��
class task
{

};

//�ź����ṹ��
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
	//��Դ��1�����ֵС��0����������
	s.value--;
	if (s.value < 0)
	{
		block(s.queue);
	}
}

//s.valueС��0���������ֵ��ʾ�ȴ����еĽ�����

void v(sema& s)
{
	//��Դ��1�����ֵС�ڵ���0����������
	s.value++;
	if (s.value <= 0)
	{
		wakeup(s.queue);
	}
}

int main()
{
	//1.��value�ĳ�ʼֵ��1���ź������Ե��ɻ�����ʹ��

	//2.��value�ĳ�ֵ��0����������һ����v��һ����p�����г���ͬ��

	return 0;
}