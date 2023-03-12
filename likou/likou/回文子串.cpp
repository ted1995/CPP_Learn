#include<iostream>
#include<vector>
using namespace std;

class Solution {
private:
	int count = 0;
public:

	void expand(string s, int left, int right)
	{
		int l = left;
		int r = right;
		//在不越界的情况下，从中心开始向两边扩展
		while (l >= 0 && r < s.length())
		{
			if (s[l] == s[r])
			{
				count++;
 				l--;
				r++;
			}
			else
			{
				break;
			}
		}
	}
	int countSubstrings(string s) {
		//双指针中心扩展法，从头开始以单中心和双中心两种方式向两边进行扩展，没扩展一次，回文子串的个数就加1，且左右指针不能越界
		int n = s.length();
		int left = 0;
		int right = 0;

		for (int i = 0; i < n; i++)
		{
			//单中心
			expand(s, i, i);
			//双中心
			expand(s, i, i + 1);
		}

		return count;
	}
};


int main()
{
	string s1 = "abc";
	Solution s;
	s.countSubstrings(s1);
}