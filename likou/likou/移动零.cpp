#include<iostream>
using namespace std;
#include<vector>

class Solution {
public:
	void moveZeroes(vector<int>& nums) {
		vector<int>::iterator it = nums.begin();
		while (it != nums.end())
		{
			if (*it == 0)
			{
				it=nums.erase(it);
				nums.push_back(0);
			}
			else
			{
				it++;
			}
		}
	}
};


