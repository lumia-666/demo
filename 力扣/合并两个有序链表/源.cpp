#define For(n) for(int index = 0;index < n;++index)
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include<vector>
using namespace std;
struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode() = default;
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};
struct ListNode
{
	int value = 0;
	ListNode* next = nullptr;
	ListNode() = default;
	ListNode(int val) :value(val) {};
	bool operator==(ListNode& node) {
		return (this->value == node.value && this->next == node.next);
	}
};
struct Edge {
	int weight;
	int aimNode;//ָ��Ľڵ�
	Edge* nextEdge;
};
typedef struct Node {
	char data; //���� 
	Edge* firstEdge; //�Ӹõ��ȥ�ĵ�һ���ߣ��õ��ȥ�������ıߴ��ں���
};
//����ͼ���ڽӱ�洢�ṹ 
typedef struct {
	Node nodeList[127]; //�ڵ����� 
	int n; //ͼ�Ķ�����
	int e; //ͼ�ı��� 
}Graph;

ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
	ListNode* res;
	while (list1)
	{

	}
}

bool check(TreeNode* p, TreeNode* q)
{
	if (!p && !q)
	{
		return true;
	}
	if (!p || !q)
	{
		return false;
	}
	return p == q && check(p->left, q->right) && check(p->right, q->left);
}

bool isSymmetric(TreeNode* root) {
	return check(root, root);
}


int main() {

	system("pause");
	return 0;
}