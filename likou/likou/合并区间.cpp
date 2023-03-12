#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

class Solution {
public:
	vector<vector<int>> merge(vector<vector<int>>& intervals)
	{

		//先将第一个区间放进result中
		vector<vector<int>> result;
		int n = intervals.size();
		if (n == 1)
		{
			result.push_back(intervals[0]);
			return result;
		}
		result.push_back(intervals[0]);
		bool flag = false;
		for (int i = 1; i < n; i++)
		{
			for (int j = 0; j < result.size(); j++)
			{
				if ((intervals[i][0] < result[j][0] && intervals[i][1] < result[j][0])
					|| (intervals[i][0] > result[j][1] && intervals[i][1] > result[j][1]))
				{
					flag = false;
				}
				else
				{
					result[j].front() = min(intervals[i][0], result[j][0]);
					result[j].back() = max(intervals[i][1], result[j][1]);
					flag = true;
				}
			}
			if (!flag)
			{
				result.push_back(intervals[i]);
			}
		}
		return result;
	}
};

