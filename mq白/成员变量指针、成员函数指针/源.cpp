#include<iostream>
#include<string>
#include<functional>

void* (*g_read)(void*);

struct X {
	static void* f(void *p) 
	{ 
		char* c = (char*)p;
		std::cout << c << std::endl;
		return nullptr;
	}
};

void f2() {
	std::cout << "7";
}

struct Test_bind {
	void t(int n) {
		for (; n; n--)
			std::cout << "t\n";
	}
	void t() {
		std::cout << "���ص�t\n";
	}
};

std::string& f()
{
	std::string s = "Example";
	return s; // �˳� s ��������:
	// �����������������������洢
}

void *ff(void* (*read)(void*))
{
	g_read = read;
	return nullptr;
}

int main() {
	//void(X:: * p)() = &X::f;
	//X x;
	//(x.*p)();//6
	//void(*p2)() = f2;
	//(*p2)();//�ȼ���p2()
	//std::string& r = f(); // ��������
	////std::cout << r;       // δ������Ϊ�����������ö�ȡ
	//std::string s = f();  // δ������Ϊ�����������ø��Ƴ�ʼ��
	//std::string str("123");
	//std::string& s1 = str;
	//str.~basic_string();
	//std::cout << str << std::endl;
	//std::cout << s1 << std::endl;
	std::function<void()> f;

	Test_bind t_b;
	f = std::bind(static_cast<void(Test_bind::*)(int)>(&Test_bind::t), &t_b, 3);
	f();
	//n();
	ff(&X::f);
	g_read((void *)"123");
}