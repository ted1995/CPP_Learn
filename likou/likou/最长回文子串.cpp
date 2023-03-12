#include<iostream>
using namespace std;
#include<string>
#include<algorithm>

int expandFromCentern(string s, int left, int right);

string longestPalindrome(string s)
{
	if (s.length() < 1)
	{
		return "";
	}
	int start = 0, end = 0;
	int maxlen = 0, maxi = 0, maxrecord1 = 0, maxrecord2 = 0;
	for (int i = 0; i < s.length(); i++)
	{
		//单双中心扩展次数不一样，单中心第一次比较必相等，所以真正的扩展要减一
		//单中心找回文串
		int return1=expandFromCentern(s, i, i);
		int record1 = return1 - 1;
		int len1 = record1 * 2 + 1;
		//双中心扩展，相当于从0扩展，第一次比较相等则相当于扩展了一次
		//双中心找回文串
		int return2=expandFromCentern(s, i, i + 1);
		int record2 = return2;
		int len2 = record2 * 2;
		int len = max(len1, len2);
		if (maxlen < len)
		{
			maxi = i;
			maxlen = len;
			maxrecord1 = record1;
			maxrecord2 = record2;
		}
	}
	if (maxlen%2)
	{

		start = maxi - maxrecord1;
		end = maxi + maxrecord1;
	}
	else
	{
		start = maxi - maxrecord2-1;
		end = maxi  + maxrecord2;
	}
	return s.substr(start, end - start + 1);
}

//从序列头开始，每一个元素都作为中心元素，向两边扩展，
//每向两边扩展一次，就比较对称位置的元素是否相等，
//相等继续扩展比较，不相等停止比较，记录下扩展次数
int expandFromCentern(string s, int left, int right)
{
	int l = left, r = right;
	int record = 0;
	//不出界
	while (l >= 0 && r <= s.length() && s[l] == s[r])
	{
		l--;
		r++;
		record++;
	}
	return record;
}




