#define For(n) for(int index = 0;index < n;++index)
#define _CRT_SECURE_NO_WARNINGS
#include <vector>
#include <iostream>
#include <iomanip>
#include <queue>
#include <stack>
#include <string>
#include <math.h>
#include <unordered_map>
using namespace std;
int RES = 0;
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

TreeNode* CreateTree(TreeNode* root, std::vector<int>& v)
{
	if (!root) {
		return nullptr;
	}
	queue<TreeNode*> que;
	que.push(root);
	TreeNode* tmpNode = nullptr;
	int size = v.size();
	int floorNum = 0;
	int num = 0;

	while (num < size - 1)
	{
		tmpNode = que.front();
		que.pop();
		if (v[++num] >= 0) {
			tmpNode->left = new TreeNode(v[num]);
			que.push(tmpNode->left);
		}
		if (num >= size - 1) {
			break;
		}
		if (v[++num] >= 0) {
			tmpNode->right = new TreeNode(v[num]);
			que.push(tmpNode->right);
		}
	}
	return root;
}
std::vector<TreeNode*> inorderTraversal(TreeNode* root) {
	std::vector<TreeNode*> res;
	std::stack<TreeNode*> stk;
	while (root != nullptr || !stk.empty()) {
		while (root != nullptr) {
			stk.push(root);
			root = root->left;
		}
		root = stk.top();
		stk.pop();
		res.push_back(root);
		root = root->right;
	}
	return res;
}
/**
 * �����»��ߺ�����б�ܴ�ӡ�����۵Ķ�������û���ƻ��������ṹ���������root���б仯
 * @param root  ���������ڵ�
 */
void PrintTree(TreeNode* root) {
	if (!root)return;
	auto tmp = root;
	std::vector<TreeNode*> intv = inorderTraversal(tmp);//��������ڵ�����
	std::string template_str;//ģ��string����ʾÿ�д�ӡstring�ĳ���
	int location = 0;
	std::unordered_map<TreeNode*, int> first_locations;//�洢�ڵ��Ӧ�ڱ���string�е���λ��
	for (auto& i : intv) {
		location = template_str.size();
		template_str += std::to_string(i->val) + " ";
		first_locations[i] = location;
	}
	for (auto& i : template_str)i = ' ';//��ģ��ȫ����Ϊ�ո񷽱����ʹ��
	//�������
	std::queue<TreeNode*> q;
	q.push(root);
	while (!q.empty()) {
		int currentLevelSize = q.size();
		int cur_loc = 0;
		std::string tmp_str1 = template_str, tmp_str2 = template_str;//1Ϊ�ڵ������У�2Ϊ����һ��
		for (int i = 1; i <= currentLevelSize; ++i) {
			auto node = q.front();
			q.pop();
			cur_loc = first_locations[node];
			std::string num_str = std::to_string(node->val);
			//��ߣ�����������ӣ���ô�ڵڶ��ж�Ӧλ�ô�ӡ'/'���ڵ�һ�в���'_'
			if (node->left) {
				q.push(node->left);
				int first_loc = first_locations[node->left] + 1;
				tmp_str2[first_loc++] = '/';
				while (first_loc < cur_loc)tmp_str1[first_loc++] = '_';

			}
			//�м�,��Ӧλ�ô�ӡ�ڵ�ֵ���п���Ϊ��λ����
			for (int j = 0; j < num_str.length(); ++j, ++cur_loc) {
				tmp_str1[cur_loc] = num_str[j];
			}
			//�ұߣ���������Һ��ӣ���ô�ڵڶ��ж�Ӧλ�ô�ӡ'\'���ڵ�һ�в���'_'
			if (node->right) {
				q.push(node->right);
				int last_loc = first_locations[node->right] - 1;
				tmp_str2[last_loc] = '\\';
				while (cur_loc < last_loc) {
					tmp_str1[cur_loc++] = '_';
				}
			}
		}
		//��ӡ����
		std::cout << tmp_str1 << std::endl;
		std::cout << tmp_str2 << std::endl;
	}
}

TreeNode* mergeTrees(TreeNode* t1, TreeNode* t2) {
	if (t1 == nullptr) {
		return t2;
	}
	if (t2 == nullptr) {
		return t1;
	}
	auto merged = new TreeNode(t1->val + t2->val);
	merged->left = mergeTrees(t1->left, t2->left);
	merged->right = mergeTrees(t1->right, t2->right);
	return merged;
}

int main() {
	vector<int> v1 = { 1,3,2,5 };
	vector<int> v2 = { 2,1,3,3,4,-1,7 };
	TreeNode* root1 = new TreeNode{ 1 };
	TreeNode* root2 = new TreeNode{ 2 };
	auto head1 = CreateTree(root1, v1);
	auto head2 = CreateTree(root2, v2);
	auto res = mergeTrees(head1,head2);
	PrintTree(res);
	system("pause");
	return 0;
}