#include "solving.hpp"
#include "config.hpp"
#include "vectors.hpp"
#include "structs.hpp"
#include "cmath"
int unrealisticsolve(int i,int j,particle* particlelist){
        double radius=particlelist[i].radius+particlelist[j].radius;
        vector2 vi=getorigin(particlelist[j].pos,particlelist[i].pos);
        double leng = lengsqt(vi);
        vector2 vj=getorigin(particlelist[i].pos,particlelist[j].pos);
        double distance= sqrt(leng);
        vi=normal_raw(vi,distance);
        vj=normal_raw(vj,distance);
        double tomove = (radius-distance)/2.d;
        particlelist[i].pos.x=particlelist[i].pos.x+vi.x*tomove;
        particlelist[i].pos.y=particlelist[i].pos.y+vi.y*tomove;
        particlelist[j].pos.x=particlelist[j].pos.x+vj.x*tomove;
        particlelist[j].pos.y=particlelist[j].pos.y+vj.y*tomove;
    return 0;
}