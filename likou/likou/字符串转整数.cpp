
#include<iostream>
using namespace std;
#include<string>
#include<limits>

class Solution {
public:
	int myAtoi(string s) {
		int len = s.size();
		int index = 0;
		//��ȥ���ո�
		while (index < len)
		{
			if (s[index] != ' ')
			{
				break;
			}
			index++;
		}
		//ֻ�пո�
		if (index == len)
		{
			return 0;
		}
		//������������
		int sign = 1;
		if (s[index] == '+')
		{
			sign = 1;
			index++;
		}
		else if (s[index] == '-')
		{
			sign = -1;
			index++;
		}
		string ms;
		//��ȡ�����ַ���
		while (index < len)
		{
			//������ĸ��ֱ�ӽ���ѭ��
			if (s[index]<'0' || s[index]>'9')
			{
				break;
			}
			ms += s[index];
			index++;
		}
		int res = 0;
		int mlen = ms.size();
		//�������ַ���ת��Ϊ����
		for (int i = 0; i < mlen; i++)
		{
			//�ж�Խ�磬��Ҫ�����ת����С�ģ��ڽ����б𣬷����ֱ��Խ�磬�Ȳ����б�
			//resҪ�Ǵ���INT_MAX/10����ô�ٽ��г�10���㣬һ����Խ��
			//resҪ�ǵ���INT_MAX/10����ôֻҪ�µ�λ�������������ֵȡ��10֮�����ֵ
			if (res > INT_MAX/10||(res==INT_MAX/10&&(ms[i]-'0')>INT_MAX%10))
			{
				return INT_MAX;
			}
			else if (res < INT_MIN/10 || res==INT_MIN/10 && (ms[i]-'0')>-(INT_MIN%10))
			{
				return INT_MIN;
			}
			res = res * 10 + (ms[i] - '0')*sign;
		}
		return res;
	}
};


