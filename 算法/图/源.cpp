#define _CRT_SECURE_NO_WARNINGS
#define For(n) for(int index = 0;index < n;++index)
//#include "vld.h"
//#include "output_Container.h"
#include <iostream>
#include <string>
#include "Gragh.hpp"
using namespace std;
int visited[127];
void DFSTraverse(Graph G, int v) {
	Edge *p; //������� 
	cout << "(" << v << "," << G.nodeList[v].data << ")" << ' '; //���������Ϣ 
	visited[v] = 1;
	p = G.nodeList[v].firstEdge; //���ʵ�v������
	while (p != NULL) {
		if (visited[p->aimNode] == 0) {
			DFSTraverse(G, p->aimNode);
		}
		p = p->nextEdge;
	}
}

//������ȱ���
void BFSTraverse(Graph G, int v) {
	int i, j, visited[MAX]; //������������־���� 
	Edge *p; //������� 
	int queue[MAX], front = 0, rear = 0; //����ѭ������  
	for (i = 0; i < G.n; i++) {
		visited[i] = 0; //��־������Ϣ��ʼ�� 
	}
	cout << "(" << v << "," << G.nodeList[v].data << ")" << ' '; //���������Ϣ 
	visited[v] = 1; //��Ӧ����ı�־��Ϊ1 
	rear = (rear + 1) % MAX; //��βָ����� 
	queue[rear] = v; //���ҵĶ����Ӧ�������� 
	//ѭ������ 
	while (front != rear) {
		front = (front + 1) % MAX; //��ͷָ�����
		j = queue[front]; //�Ӷ�����ȡ�������Ӧ��� 
		p = G.nodeList[j].firstEdge; //ȡ��Ӧ��ŵĶ�����Ϣ 
		while (p != NULL) {
			if (visited[p->aimNode] == 0) {
				visited[p->aimNode] = 1;
				cout << "(" << p->aimNode << "," << G.nodeList[p->aimNode].data << ")" << ' '; //���������Ϣ 
				rear = (rear + 1) % MAX; //��βָ����� 
				queue[rear] = p->aimNode; //���ҵĶ����Ӧ��������
			}
			p = p->nextEdge;
		}
	}
}

//������ 
int main() {
	Graph G; //����ͼ�ṹ���� 
	int v1, v2, choose;
	cout << "��ѡ��0-�˳���1-��������ͼ�������ڽӱ�洢�ṹ����2-������ȱ�����3-������ȱ���" << endl;
	cin >> choose;
	while (choose != 0) {
		switch (choose) {
		case 1: {
			createGraph(G); //��������ͼ 
			printGraph(G); //��� 
			break;
		}
		case 2: {
			cout << "������ĸ����㿪ʼ����(��Ŵ�0��ʼ)��";
			cin >> v1;
			DFSTraverse(G, v1);
			for (int i = 0; i < G.n; i++) {
				visited[i] = 0; //��־������Ϣ��ʼ��
			}
			cout << endl;
			break;
		}
		//case 3: {
		//	cout << "������ĸ����㿪ʼ����(��Ŵ�0��ʼ)��";
		//	cin >> v2;
		//	BFSTraverse(G, v2);
		//	cout << endl;
		//	break;
		//}
		default:cout << "�������������ѡ��" << endl;
		}
		cout << "��ѡ��0-�˳���1-��������ͼ�������ڽӱ�洢�ṹ����2-������ȱ�����3-������ȱ���" << endl;
		cin >> choose;
	}
}