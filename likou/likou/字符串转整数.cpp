
#include<iostream>
using namespace std;
#include<string>
#include<limits>

class Solution {
public:
	int myAtoi(string s) {
		int len = s.size();
		int index = 0;
		//先去除空格
		while (index < len)
		{
			if (s[index] != ' ')
			{
				break;
			}
			index++;
		}
		//只有空格
		if (index == len)
		{
			return 0;
		}
		//处理正负符号
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
		//获取数字字符串
		while (index < len)
		{
			//遇到字母就直接结束循环
			if (s[index]<'0' || s[index]>'9')
			{
				break;
			}
			ms += s[index];
			index++;
		}
		int res = 0;
		int mlen = ms.size();
		//将数字字符串转化为整数
		for (int i = 0; i < mlen; i++)
		{
			//判断越界，需要将大的转化内小的，在进行判别，否则会直接越界，等不到判别
			//res要是大于INT_MAX/10，那么再进行乘10运算，一定会越界
			//res要是等于INT_MAX/10，那么只要新的位的数不大于最大值取余10之后的数值
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


