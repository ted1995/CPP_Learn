#include<iostream>
using namespace std;
#include<vector>

class Solution {
public:
	string convert(string s, int numRows) 
	{
		//������С��������������Ϊ1����ֱ�ӷ����ַ���
		if (s.size() <= numRows || numRows == 1)
		{
			return s;
		}
		int curRow = 0;
		bool down = false;
		//ÿһ�ж�����һ���ַ���������˳���ÿһ�е��ַ�����ֵ
		//������һ�к����һ�е��б�ʱ���͸ı䷽��
		//���ÿһ�е��ַ��������һ��
		vector<string> vecs(numRows);
		for (char c : s)
		{
			vecs[curRow] += c;
			if (curRow == 0 )
			{
				down = true;
			}
			else if (curRow == numRows - 1)
			{
				down = false;
			}
			if (down)
			{
				curRow++;
			}
			else
			{
				curRow--;
			}
		}
		string ret;
		for (string vec : vecs)
		{
			ret += vec;
		}
		return ret;
	}
};


