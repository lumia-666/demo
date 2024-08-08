#include <iostream>
#include <memory>
//��Man���ڲ�������һ��Woman��Woman���ڲ�Ҳ����һ��Man����һ��man��һ��woman�Ƿ��޵�ʱ��
//����ֱ�Ӿʹ������໥�������⡣man�ڲ��и����ڹ���wife�����ڵ�shared_ptr������
//Ҳ����˵wife�ض�����husbandȥ��֮�����ȥ����ͬ���ģ�woman�ڲ�Ҳ��һ������husband�����ڵ�shared_ptr������
//Ҳ����˵husband������wifeȥ��֮�����ȥ���������ѭ�����ô��ڵ����⣺husband����������wife�������ھ�����
//wife����������husband�������ھ�����������˶���������Υ������Ȼ���ɣ��������ڴ�й©��


//���std::shared_ptrѭ�����������Կ����weak_ptr���ϡ�weak_ptr����������Դʱ�����������ü�����
//�������ܹ�ͨ��lock()�������ж������������Դ�Ƿ��ͷš��������Ȼ��һ�������ǣ���Ȼweak_ptr��������Դ�����ü�����
//��ô��ʹ��weak_ptr�����ʱ����Դ��ͻȻ�ͷ�����ô���أ��Ǻǣ��������������ֱ��ͨ��weak_ptr��������Դ��
//��ô���ͨ��weak_ptr����ӷ�����Դ�أ����ǣ�����Ҫ������Դ��ʱ��weak_ptrΪ������һ��shared_ptr��
//shared_ptr�ܹ���֤��shared_ptrû�б��ͷ�֮ǰ�������������Դ�ǲ��ᱻ�ͷŵġ�����shared_ptr�ķ�������lock()������

//ϸ�ڣ�shared_ptrʵ����operator bool() const�������ж�һ���������Դ�Ƿ��ͷš�
class Woman;
class Man {
private:
	std::weak_ptr<Woman> _wife;
	//std::shared_ptr<Woman> _wife;
public:
	void setWife(std::shared_ptr<Woman> woman) {
		_wife = woman;
	}

	void doSomthing() {
		//����һ��shared_ptr
		if (_wife.lock()) {

		}
	}

	~Man() {
		std::cout << "kill man\n";
	}
};

class Woman {
private:
	std::weak_ptr<Man> _husband;
	//std::shared_ptr<Man> _husband;
public:
	void setHusband(std::shared_ptr<Man> man) {
		_husband = man;
	}
	~Woman() {
		std::cout << "kill woman\n";
	}
};


int main(int argc, char** argv) {
	std::shared_ptr<Man> m(new Man());
	std::shared_ptr<Woman> w(new Woman());
	if (m && w) {
		m->setWife(w);
		w->setHusband(m);
	}
	return 0;
}