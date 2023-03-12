#include<iostream>
using namespace std;

struct ListNode {
      int val;
      ListNode *next;
      ListNode() : val(0), next(nullptr) {}
      ListNode(int x) : val(x), next(nullptr) {}
      ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
	ListNode* sortList(ListNode* head) {
		ListNode dummyHead(0);
		dummyHead.next = head;
		auto p = head;
		int length = 0;
		while (p != nullptr)
		{
			++length;
			p = p->next;
		}

		for (int size = 1; size < length; size <<= 1)
		{
			auto cur = head;
			auto tail = &dummyHead;
			while (cur)
			{
				auto left = cur;
				auto right = cut(left, size);
				cur = cut(right, size);
				tail = merge(left, tail, right);//传入上一个tail，返回新tail
			}
		}
		return dummyHead.next;
	}
	ListNode* cut(ListNode* head, int n)
	{
		auto p = head;
		while (p != nullptr&&--n)
		{
			p = p->next;
		}
		if (!p) return nullptr;
		auto next = p->next;
		p->next = nullptr;
		return next;
	}
	ListNode* merge(ListNode* left, ListNode* head, ListNode* right)
	{
		auto p = head;
		while (left&&right)
		{
			if (left->val <= right->val)
			{
				p->next = left;
				left = left->next;
				p = p->next;
			}
			else
			{
				p->next = right;
				right = right->next;
				p = p->next;
			}
		}
		p->next = right ? right : left;
		while (p->next != nullptr)
		{
			p = p->next;
		}
		return p;
	}
};


