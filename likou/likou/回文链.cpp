#include<iostream>
using namespace std;
#include<vector>
class Solution {
public:
	bool isPalindrome(vector<int> v) {
		//�Ƚ����ݷŵ������У�����˫ָ���ж�
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


