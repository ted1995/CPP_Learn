#include<iostream>
#include<map>
#include<string>
#include<vector>
using namespace std;



class Solution {
private:
	map<char, string> letterMap = {
		{'0',""},
		{'1',""},
		{'*',""},
		{'#',""},
		{'2',"abc"},
		{'3',"def"},
		{'4',"ghi"},
		{'5',"jkl"},
		{'6',"mno"},
		{'7',"pqrs"},
		{'8',"tuv"},
		{'9',"wxyz"}
	};
public:
	//�����Ͻ��
	vector<string> result;
	//��ŵ������
	string s;
	//�����㷨
	void backtrace(const string& digit, int index)
	{
		//���в������ֶ������ˣ��ݹ���ֹ����
		if (index == digit.size())
		{
			//������ĸ��Ϸŵ�����У�������������Ϊÿһ�ֵݹ����������
			result.push_back(s);
			return;
		}
		//ͨ������ȡ����Ӧ����ĸ��
		string temp = letterMap[digit[index]];
		//����ĸ�����б���
		for (int i = 0; i < temp.size(); i++)
		{
			//��һ����ĸ�Ž������
			s.push_back(temp[i]);
			//����ת����һ����������
			index++;
			//�õݹ齫��һ���������ֶ�Ӧ����ĸ���е���ĸҲ�Ž������
			backtrace(digit, index);
			//���Ž�s�������ĸ��ɾ��������һ��ʹ��
			s.pop_back();
			index--;
		}
	}

	vector<string> letterCombinations(string digits)
	{
		if (digits.size() == 0)
		{
			return result;
		}
		int index = 0;
		backtrace(digits, index);
		return result;
	}
};

