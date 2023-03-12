#include<iostream>
using namespace std;
#include<vector>
#include<string>

class Solution {
public:
	vector<int> findAnagrams(string s, string p) {
		//�������ڣ�����ÿ����ĸ���ֵĴ���
		vector<int> ans;
		//p���ȴ���s������s���ȵ���0
		if (p.size() > s.size() || s.size() == 0)
		{
			return ans;
		}

		vector<int> pcnt(26, 0);
		vector<int> windows(26, 0);
		//����p������Ԫ�صļ���
		for (auto c : p)
		{
			pcnt[c - 'a']++;
		}
		//��ʼ���ڱ߽磬��С���õ���p�Ĵ�С[l,r]=[0,2]
		int l = 0, r = p.size() - 1;
		//���㵱ǰ������[0,r-1]Ԫ�صļ���
		for (int i = 0; i < r; i++)
		{
			windows[s[i] - 'a']++;
		}
		//
		while (r < s.size())
		{
			//���㵱ǰ����rλ��Ԫ�صļ���
			windows[s[r] - 'a']++;
			//��ʱ���ڴ�С����p�Ĵ�С���Ҷ��Ѿ����������Խ��бȽ�
			if (pcnt == windows)
			{
				ans.push_back(l);
			}
			//�Ƚ�lλ�õļ���������Ա��ں���ıȽϣ��ٻ���������[l+1,r+1],��ʼ�Ƚ��´�����Ԫ�صļ���
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