#include<iostream>
using namespace std;
#include<vector>
#include<string>

class Solution {
public:
	vector<int> findAnagrams(string s, string p) {
		//滑动窗口，计算每个字母出现的次数
		vector<int> ans;
		//p长度大于s，或者s长度等于0
		if (p.size() > s.size() || s.size() == 0)
		{
			return ans;
		}

		vector<int> pcnt(26, 0);
		vector<int> windows(26, 0);
		//计算p中所有元素的计数
		for (auto c : p)
		{
			pcnt[c - 'a']++;
		}
		//初始窗口边界，大小正好等于p的大小[l,r]=[0,2]
		int l = 0, r = p.size() - 1;
		//计算当前窗口内[0,r-1]元素的计数
		for (int i = 0; i < r; i++)
		{
			windows[s[i] - 'a']++;
		}
		//
		while (r < s.size())
		{
			//计算当前窗口r位置元素的计数
			windows[s[r] - 'a']++;
			//此时窗口大小等于p的大小，且都已经计数，可以进行比较
			if (pcnt == windows)
			{
				ans.push_back(l);
			}
			//先将l位置的计数清除，以便于后面的比较，再滑动窗口至[l+1,r+1],开始比较新窗口内元素的计数
			windows[s[l] - 'a']--;
			l++;
			r++;
		}
		return ans;
	}
};


int main3()
{
	string s1 = "cbaebabacd";
	string p = "abc";
	Solution s;
	s.findAnagrams(s1, p);
	return 0;
}