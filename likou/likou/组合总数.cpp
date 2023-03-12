#include<iostream>
#include<vector>
using namespace std;


class Solution {
public:
	//结果
	vector<vector<int>> result;
	//路径
	vector<int> path;
	void traceback(vector<int>& candidates, int target, int begin)
	{
		int n = candidates.size();
		//目标数减到最后，小于0，说明此条路径已经结束，且未找到满足条件的组合
		if (target < 0)
		{
			return;
		}
		//target为0，说明此条路径已经结束，且找到了数字和为原始target的组合
		if (target == 0)
		{
			result.push_back(path);
			return;
		}
		//循环遍历数组，并与target做减法
		for (int i = begin; i < n; i++)
		{
			target = target - candidates[i];
			path.push_back(candidates[i]);
			traceback(candidates, target, i);
			//此条路径结束，将相关变量恢复到调用前的状态，等待下一次调用
			target = target + candidates[i];
			path.pop_back();
		}

	}

	vector<vector<int>> combinationSum(vector<int>& candidates, int target)
	{
		int n = candidates.size();
		if (n == 0)
		{
			return result;
		}
		traceback(candidates, target, 0);
		return result;
	}
};


