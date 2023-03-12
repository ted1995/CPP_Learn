#include<iostream>
#include<string>
#include<vector>
using namespace std;

class Solution {
public:
	vector<string> res;
	string s;
	vector<string> generateParenthesis(int n)
	{
		int lc = 0, rc = 0;
		dfs( n, lc, rc);
		return res;
	}
	void dfs(int n, int lc, int rc) 
	{
		if (rc > lc || lc > n || rc > n)
		{
			return;
		}
			
		if (lc == rc && lc == n) 
		{
			res.push_back(s);
			return;
		}
		s.push_back('(');
		lc++;
		dfs( n, lc, rc);
		s.pop_back();
		lc--;
		s.push_back(')');
		rc++;
		dfs( n, lc, rc);
		s.pop_back();
		rc--;
	}
};

