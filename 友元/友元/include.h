#pragma once
namespace car {
    class CCar;  //��ǰ����CCar�࣬�Ա�����CDriver��ʹ��
    class CDriver
    {
    public:
        void ModifyCar(CCar* pCar);  //��װ����
    };
    class CCar
    {
    private:
        int price;
        friend int MostExpensiveCar(CCar cars[], int total);  //������Ԫ
        friend void CDriver::ModifyCar(CCar* pCar);  //������Ԫ
    };
    void CDriver::ModifyCar(CCar* pCar)
    {
        pCar->price += 1000;  //������װ���ֵ����
    }
}