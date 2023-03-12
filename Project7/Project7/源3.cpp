#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

class Solution {
public:
	vector<vector<int>> merge(vector<vector<int>>& intervals)
	{

		//�ȶ�vector��������
		sort(intervals.begin(), intervals.end(), [](vector<int> u, vector<int> v) {
			return u[0] < v[0];
		});
		//������󣬼��ɱ���intervals,���кϲ�����
		vector<vector<int>> ans;
		ans.push_back(intervals[0]);
		for (int i = 1; i < intervals.size(); i++)
		{
			vector<int> tmp = ans.back();
			if (tmp[1] < intervals[i][0])
			{
				//���ཻ����ֱ�ӷ���ans
				ans.push_back(intervals[i]);
			}
			else
			{
				//�ཻ��ȡ�������޸�tmp�ķ�Χ
				tmp[0] = min(tmp[0], intervals[i][0]);
				tmp[1] = max(tmp[1], intervals[i][1]);
			}
		}
		return ans;
	}
};

void split(string& s, vector<string>& v)
{
	int start = 0;
	int cnt = 0;
	string tmp = "";
	for (int i = 0; i < s.size(); i++)
	{
		
		if (s[i] == '[')
		{
			start = i + 1;
		}
		else if (s[i] == ',')
		{
			//���˴˴εĽ�β
			tmp = s.substr(start, cnt);
			v.push_back(tmp);
			tmp = "";
			//�´εĿ�ͷ
			start = i + 1;
			cnt = 0;
		}
		else if (s[i] == ']')
		{
			//�������һ�εĽ�β
			tmp = s.substr(start, cnt);
			v.push_back(tmp);
		}
		else
		{
			cnt++;
		}
	}
}

int main7()
{

	string s= "[1,2,34,5,-6]";
	vector<string> v;
	split(s, v);

	return 0;
}