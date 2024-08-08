#pragma once
#include "common.hpp"

ListNode* ReverseList(ListNode *root)
{
	auto ptr = root;
	ListNode* pre = NULL; //������һ���ڵ�
	while (ptr)
	{
		ListNode* next = ptr->next; //���浱ǰ�ڵ��next
		ptr->next = pre;
		pre = ptr;
		ptr = next;
	}
	return pre;
}