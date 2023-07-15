#ifndef VECTORS_HPP
#define VECTORS_HPP
#include "structs.hpp"

vector2 getorigin(vector2 origin,vector2 other);
vector2 normal_raw(vector2 a,double leng);
vector2 normal(vector2 a);
double lengsqt(vector2 a);
double dotprod(vector2 a, vector2 b);
#endif