//https://zh.cppreference.com/w/cpp/language/default_comparisons
#include <compare>
struct Point {
    int x;
    int y;
    auto operator<=>(const Point&p) const {
        return x <=> p.x;
    }
    bool operator==(const Point&p) const {
        return x == p.x;
    }
    // ... �ǱȽϺ��� ...
};
// ����������ȫ�������Ƚ������
// < <= > >=�������� <=>��ʾ

#include <iostream>
#include <set>
int main() {
    Point pt1{ 1, 1 }, pt2{ 1, 2 };
    std::set<Point> s; // ok
    s.insert(pt1);     // ok
    std::cout << std::boolalpha
        << (pt1 == pt2) << ' ' // false��operator== ��ʽ�ز���Ĭ�ϰ汾
        << (pt1 != pt2) << ' ' // true
        << (pt1 < pt2) << ' ' // true
        << (pt1 <= pt2) << ' ' // true
        << (pt1 > pt2) << ' ' // false
        << (pt1 >= pt2) << ' ';// false
}