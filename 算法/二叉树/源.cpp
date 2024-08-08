#define _CRT_SECURE_NO_WARNINGS
#define For(n) for(int index = 0;index < n;++index)
//#include "vld.h"
//#include "output_Container.h"
#include <iostream>
#include "TreeNode.h"
#include <string>
#include <vector>
using namespace std;
//�ڶ������ĵݹ��У��ϲ�Ľڵ�����²�Ľڵ㣬���һ���ڵ㲻����һ�������ȣ����ǲ�����һ��������
//����һ���ṹ����Ϊ״̬����ÿ�εݹ��з�����Ϣ����һ��ʹ��
TreeNode *ancestor = nullptr;
struct ResType {
	bool panc = false;
	bool qanc = false;
	ResType(bool lan, bool ran) :panc(lan), qanc(ran) {}
};
ResType dfs(TreeNode* node, TreeNode* p, TreeNode* q) {
	if (node == nullptr || ancestor) {
		return ResType(false, false);
	}
	if (node == p) {
		return ResType(true, false);
	}
	if (node == q) {
		return ResType(false, true);
	}
	ResType lres = dfs(node->left, p, q);
	ResType rres = dfs(node->right, p, q);

	if ((lres.panc && rres.qanc) || (lres.qanc && rres.panc)) {
		ancestor = node;
		return ResType(true, true);
	}
	if (lres.panc || rres.panc) {
		return ResType(true, false);
	}
	if (lres.qanc || rres.qanc) {
		return ResType(false, true);
	}
	return ResType(false, false);
}

TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
	dfs(root, p, q);
	return ancestor;
}

int main()
{
	//std::vector<int> v{ 1,2,3,-1,4,5,-1,6,7,-1,8,9,-1,10,-1,11,12,14,15 };
	std::vector<int> v{ 4,2,7,1,3,6,9 };
	TreeNode *root = new TreeNode(4);
	int index = 0;
	root = CreateTree(root, v);
	PrintTree(root);
	//TreeNode *p = root->left->left->left->left;
	//TreeNode *q = root->left->right->left->left;
	//lowestCommonAncestor(root, p, q);
	//PrintTree(root);
	system("pause");
	return 0;
}

