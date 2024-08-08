#include <iostream>
#include <string>
#include <type_traits>

// ����ģ�庯�������ڻ�ȡ��Ա����������
template <typename T>
struct member_traits {};

// ģ���ػ������ڻ�ȡ��Ա����������
template <typename ClassType, typename MemberType>
struct member_traits<MemberType ClassType::*>
{
    using type = MemberType;
};

// get����ģ��
template <typename ClassType, typename MemberType>
typename member_traits<MemberType ClassType::*>::type getMember(ClassType& obj, MemberType ClassType::* member)
{
    return obj.*member;
}

// set����ģ��
template <typename ClassType, typename MemberType>
void setMember(ClassType& obj, MemberType ClassType::* member, const MemberType& value)
{
    obj.*member = value;
}

// ʾ����
struct MyClass
{
    int value;
    std::string name;
};

int main()
{
    MyClass obj;
    obj.value = 42;
    obj.name = "John Doe";

    // ʹ��get������ȡ��Ա������ֵ
    int value = getMember(obj, &MyClass::value);
    std::string name = getMember(obj, &MyClass::name);

    // ������
    std::cout << "Value: " << value << std::endl;
    std::cout << "Name: " << name << std::endl;

    // ʹ��set�������ó�Ա������ֵ
    setMember(obj, &MyClass::value, 100);
    auto n = &MyClass::name;
    setMember(obj, &MyClass::name, std::string("Jane Smith"));

    // ����޸ĺ�Ľ��
    std::cout << "Modified Value: " << obj.value << std::endl;
    std::cout << "Modified Name: " << obj.name << std::endl;

    return 0;
}
