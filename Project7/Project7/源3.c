#include<stdio.h>

int add(int a, int b)
{
	//λ����ʵ����ӵı��ʾ��ǽ���λ�𽥼ӵ������ǽ�λ���������
	//�����ǽ�λ���
	int pureadd = a ^ b;
	//��λ��־
	int carry = a & b;
	//��λ��־��Ϊ0����������
	while (carry != 0)
	{
		//�н�λ����Ҫ���¼���pureadd��carry<<1�ĺ�
		int p = pureadd;
		int c = carry << 1;
		//�ظ��ӷ�����
		pureadd = p ^ c;
		carry = p & c;
	}
	return pureadd;
}


int main4()
{
	//
	int ans=add(15, 5);
	return 0;
}