#include<iostream>
using namespace std;
#include <iomanip>

int main1()
{
	//floatռ4���ֽ�
	float a = 1.0;
	//ȡ������a�ĵ�ַ��charռһ���ֽڣ����Կ���һ���ֽ�һ���ֽڵ�ȡ��float��ֵ
	char *p = (char*)&a;
	for (int i = 0; i < 4; i++)
	{
		//��ӡ��ǰ�ֽ�
		printf("% ", *p);
		//ָ����һ���ֽ�
		p++;
	}
	return 0;
}