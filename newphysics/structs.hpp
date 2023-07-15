#ifndef STRUCTS_HPP
#define STRUCTS_HPP




struct spring
{
    double k;
    double object1;
    double object2;
    double durability;
    double leng;
    double heat;
    double damp;
};
struct vector2
{
    double x;
    double y;
};

struct particle
{
    vector2 pos;
    vector2 ppos;
    double mass;//not for now
    double heat;//maybe not used
    double radius;
    int type;
    bool fixed;//not yet
    vector2 ac;
    int r;
    int g;
    int b;
};

#endif