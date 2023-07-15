#include "vectors.hpp"
#include "structs.hpp"
#include<cstdio>
#include<cstdlib>
#include<iostream>
int main(){
    vector2 c= getorigin({6,2},{8,2});
    std::cout<<c.x<<" " << c.y <<"\n";
    vector2 d= normal({4,3});
    std::cout<<d.x<<" " << d.y <<"\n";
    double e= lengsqt({4,3});
    std::cout<<e;
}