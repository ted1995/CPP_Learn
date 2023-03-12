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
		//�ڲ�Խ�������£������Ŀ�ʼ��������չ
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
		//˫ָ��������չ������ͷ��ʼ�Ե����ĺ�˫�������ַ�ʽ�����߽�����չ��û��չһ�Σ������Ӵ��ĸ����ͼ�1��������ָ�벻��Խ��
		int n = s.length();
		int left = 0;
		int right = 0;

		for (int i = 0; i < n; i++)
		{
			//������
			expand(s, i, i);
			//˫����
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