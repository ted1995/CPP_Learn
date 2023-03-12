#include<iostream>
using namespace std;
#include<vector>

class Solution {
public:
	string convert(string s, int numRows) 
	{
		//串长度小于行数或者行数为1，则直接返回字符串
		if (s.size() <= numRows || numRows == 1)
		{
			return s;
		}
		int curRow = 0;
		bool down = false;
		//每一行都配置一个字符串，按照顺序给每一行的字符串加值
		//遇到第一行和最后一行的行标时，就改变方向，
		//最后将每一行的字符串组合在一起
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


