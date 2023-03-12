#include<iostream>
using namespace std;
#include<string>


class Solution {
public:
	bool isMatch(string s, string p)
	{
		//p为空，s为空则匹配成功，s不为空则匹配失败
		if (p.empty())
		{
			return s.empty();
		}
		//p不为空
		//s不为空，且第一个元素匹配，记录下来
		bool first_match = !s.empty() && (s[0] == p[0] || p[0] == '.');
		//如果p有多于两个元素，且第二个元素为*，此时有两种操作方法
		if (p.size() >= 2 && p[1] == '*')
		{
			//第一种：不管第一个元素是否匹配，都可以将p的前两个元素去掉，即p[0]*匹配了0个，继续与s进行匹配
			bool result = isMatch(s, p.substr(2));
			if (result)
			{
				return result;
			}
			else if(first_match)
			{
				//第二种：在第一个元素匹配的情况下，将s的第一个元素去掉，继续与p进行匹配
				return isMatch(s.substr(1), p);
			}
			//return isMatch(s, p.substr(2)) || (first_match&&isMatch(s.substr(1), p));
		}
		//p的第二个元素不为*,且第一个元素匹配
		else if(first_match)
		{
			//从第二个元素开始继续匹配
			return isMatch(s.substr(1), p.substr(1));
		}
	}
};


