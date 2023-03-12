#include<iostream>
#include<vector>
#include<string>
#include<set>
using namespace std;

class Solution {
public:
	bool wordBreak(string s, vector<string>& wordDict) {
		
		//先转换到set中
		set<string> dictset;
		for (auto word : wordDict) 
		{
			dictset.insert(word);
		}

		int n = wordDict.size();
		vector<bool> dp(n + 1);
		dp[0] = true;
		for (int i = 0; i < n; ++i)
		{
			for (int j = 0; j <= n-i; ++j)
			{
				if (dp[i] == true && (dictset.find(s.substr(i, j)) != dictset.end()))
				{
					dp[i + j] = true;
				}
			}
		}

	}
};

