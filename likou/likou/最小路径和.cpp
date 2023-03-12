#include<iostream>
using namespace std;
#include<vector>
#include<algorithm>

class Solution {
public:
	int minPathSum(vector<vector<int>>& grid) {
		//¶¯Ì¬¹æ»®
		int m = grid.size();
		int n = grid[0].size();
		vector<vector<int>> dp(m);
		int i = 0;
		int j = 0;
		for (int i = 0; i < m; i++)
		{
			dp[i].resize(n);
		}

		for (i = 0; i < m; i++)
		{
			for (j = 0; j < n; j++)
			{
				if (i == 0 && j == 0)
				{
					dp[i][j] = grid[i][j];
				}
				else if (i == 0)
				{
					dp[i][j] = dp[i][j - 1] + grid[i][j];
				}
				else if (j == 0)
				{
					dp[i][j] = grid[i - 1][j] + grid[i][j];
				}
				else
				{
					dp[i][j] = min(dp[i - 1][j], dp[i][j - 1]) + grid[i][j];
				}
			}
		}
		return dp[m - 1][n - 1];
	}
};
