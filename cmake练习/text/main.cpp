#include<iostream>
#include "head.h"

using namespace std;

int main()
{
    int a = 20;
    int b = 30;
    cout<<"a+b="<<add(a,b)<<endl;
    cout<<"a-b"<<sub(a,b)<<endl;
    cout<<"a*b="<<mult(a,b)<<endl;
    cout<<"a/b="<<divide(a,b)<<endl;
    return 0;
}
