#include<iostream>
using namespace std;
#include<vector>
class Solution {
public:
	bool isPalindrome(vector<int> v) {
		//先将数据放到数组中，再用双指针判断
		int i = 0;
		int j = v.size() - 1;
		while (i < j)
		{
			if (v[i] == v[j])
			{
				i++;
				j--;
			}
			else
			{
				return false;
			}
		}
		return true;
	}
};


