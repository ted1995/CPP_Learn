#include<iostream>
#include<vector>
using namespace std;


class Solution {
public:
	//���
	vector<vector<int>> result;
	//·��
	vector<int> path;
	void traceback(vector<int>& candidates, int target, int begin)
	{
		int n = candidates.size();
		//Ŀ�����������С��0��˵������·���Ѿ���������δ�ҵ��������������
		if (target < 0)
		{
			return;
		}
		//targetΪ0��˵������·���Ѿ����������ҵ������ֺ�Ϊԭʼtarget�����
		if (target == 0)
		{
			result.push_back(path);
			return;
		}
		//ѭ���������飬����target������
		for (int i = begin; i < n; i++)
		{
			target = target - candidates[i];
			path.push_back(candidates[i]);
			traceback(candidates, target, i);
			//����·������������ر����ָ�������ǰ��״̬���ȴ���һ�ε���
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


