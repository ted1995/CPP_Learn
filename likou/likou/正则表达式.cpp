#include<iostream>
using namespace std;
#include<string>


class Solution {
public:
	bool isMatch(string s, string p)
	{
		//pΪ�գ�sΪ����ƥ��ɹ���s��Ϊ����ƥ��ʧ��
		if (p.empty())
		{
			return s.empty();
		}
		//p��Ϊ��
		//s��Ϊ�գ��ҵ�һ��Ԫ��ƥ�䣬��¼����
		bool first_match = !s.empty() && (s[0] == p[0] || p[0] == '.');
		//���p�ж�������Ԫ�أ��ҵڶ���Ԫ��Ϊ*����ʱ�����ֲ�������
		if (p.size() >= 2 && p[1] == '*')
		{
			//��һ�֣����ܵ�һ��Ԫ���Ƿ�ƥ�䣬�����Խ�p��ǰ����Ԫ��ȥ������p[0]*ƥ����0����������s����ƥ��
			bool result = isMatch(s, p.substr(2));
			if (result)
			{
				return result;
			}
			else if(first_match)
			{
				//�ڶ��֣��ڵ�һ��Ԫ��ƥ�������£���s�ĵ�һ��Ԫ��ȥ����������p����ƥ��
				return isMatch(s.substr(1), p);
			}
			//return isMatch(s, p.substr(2)) || (first_match&&isMatch(s.substr(1), p));
		}
		//p�ĵڶ���Ԫ�ز�Ϊ*,�ҵ�һ��Ԫ��ƥ��
		else if(first_match)
		{
			//�ӵڶ���Ԫ�ؿ�ʼ����ƥ��
			return isMatch(s.substr(1), p.substr(1));
		}
	}
};


