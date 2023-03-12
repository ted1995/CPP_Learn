#include<iostream>
using namespace std;
#include<vector>

class Solution {
public:
	vector<int> findDisappearedNumbers(vector<int>& nums) {
		int n = nums.size();
		vector<int> ans;
		for (int i = 0; i < n; i++)
		{
			//遍历元素nums[i]，在第nums[i]元素出做一个标记
			nums[abs(nums[i]) - 1] *= -1;
		}
		for (int i = 0; i < n; i++)
		{
			if (nums[i] > 0)
			{
				ans.push_back(i + 1);
			}
		}
		return ans;
	}
};

int main2()
{
	vector<int> nums = { 4,3,2,7,8,2,3,1 };
	Solution s;
	s.findDisappearedNumbers(nums);
	return 0;
}