#include<iostream>
using namespace std;
#include<vector>
#include<algorithm>

class Solution {
public:
	vector<vector<int>> threeSum(vector<int>& nums) {
		//������
		sort(nums.begin(), nums.end());
		//ȷ��һ������ʹ��˫ָ�룬������������
		int l = 0;
		int r = 0;
		vector<vector<int>> res;
		if (nums.empty())
		{
			return res;
		}
		//����ѡ��һ������
		for (int i = 0; i < nums.size(); i++)
		{
			//�������С�Ĵ���0����Ͳ�����Ϊ0
			if (nums[i] > 0)
			{
				return res;
			}
			//�����ȥ�أ��µı�������;ɵ�һ������ô���պ�Ϊ0,������������Ҳһ��
			if (i > 0 && nums[i] == nums[i - 1])
			{
				continue;
			}
			//ȷ��˫ָ���λ��
			l = i + 1;
			r = nums.size() - 1;
			//˫ָ��ѭ��
			while (l < r)
			{
				if (nums[l] + nums[r] + nums[i] == 0)
				{
					//�ҵ��˺�Ϊ0����Ԫ��
					res.push_back(vector<int>{nums[i], nums[l], nums[r]});
					//��С��Χ������
					l++;
					r--;
					//С��Ԫ��ȥ�أ�����µ������ָ���ԭ������ͬ���򹹳ɵ���Ԫ������ͬ
					while(l<r && nums[l] == nums[l - 1])
						l++;
					while(l<r && nums[r] == nums[r + 1])
						r--;
				}
				//̫����ָ������
				else if (nums[l] + nums[r] + nums[i] > 0)
				{
					r--;
				}
				//̫С����ָ������
				else
				{
					l++;
				}
			}
		}
		return res;
	}
};


