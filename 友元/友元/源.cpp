#include<iostream>
#include"include.h"
using namespace std;
namespace car {
    int MostExpensiveCar(CCar cars[], int total)  //����������ļ۸�
    {
        int tmpMax = -1;
        for (int i = 0; i < total; ++i)
            if (cars[i].price > tmpMax)
                tmpMax = cars[i].price;
        return tmpMax;
    }
}

int main()
{
    
    return 0;
}