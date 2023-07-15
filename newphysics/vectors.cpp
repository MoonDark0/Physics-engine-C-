#include "structs.hpp"
#include "vectors.hpp"
#include <cmath>

vector2 getorigin(vector2 origin,vector2 other){
    vector2 c={other.x-origin.x,other.y-origin.y};
    return c;
}

vector2 normal_raw(vector2 a,double leng){
    vector2 b={a.x/leng,a.y/leng};
    return b;
}

vector2 normal(vector2 a){
    double leng=sqrt(a.x*a.x+a.y*a.y);
    vector2 b={a.x/leng,a.y/leng};
    return b;
}

double lengsqt(vector2 a){
    return a.x*a.x+a.y*a.y;
}

double dotprod(vector2 a,vector2 b){
    return a.x*b.x+a.y*b.y;
}