#include <iostream>
#include  <string>
#include <vector>
#include "mySwap.h"
using namespace std;

int main()
{
    vector<int> ivec;
    ivec.push_back(10);
    std::cout<<ivec.front();
    ivec.push_back(11);
    std::cout << "hello world"<<std::endl;
    int a = 10,b= 20;
    mySwap(a,b);
    cout<<a<< endl;
    std::cout<<"hello"<<std::endl;
    cout<<"a+b:"<<myAdd(a,b)<<endl;
    return 0;
}