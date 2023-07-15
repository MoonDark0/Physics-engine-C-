#include "constraints.hpp"
#include "structs.hpp"
#include "vectors.hpp"
#include "config.hpp"

int circularconstraint(particle* particlelist, int particlelistlenght){
    for(int i=0;i<particlelistlenght;i++){
        double maxdist=450.d-particlelist[i].radius;
        double leng= lengsqt(particlelist[i].pos);
        if (maxdist*maxdist<leng){
            vector2 v2=normal(particlelist[i].pos);
            particlelist[i].pos={v2.x*maxdist,v2.y*maxdist};
        }
    }
    return 0;
}

int realcircularconstraint(particle* particlelist, int particlelistlenght){
    for(int i=0;i<particlelistlenght;i++){
        double maxdist=450.d-particlelist[i].radius;
        double leng= lengsqt(particlelist[i].pos);
        if (maxdist*maxdist<leng){
            vector2 v2=normal(particlelist[i].pos);
            vector2 v3={-v2.x,-v2.y};
            vector2 speed=getorigin(particlelist[i].ppos,particlelist[i].pos);
            double dotp=dotprod(speed,v3);
            vector2 vel={speed.x+2.d*(v2.x*dotp),speed.y+2.d*(v2.y*dotp)};
            vector2 pos={v2.x*maxdist,v2.y*maxdist};
            particlelist[i].pos=pos;
            particlelist[i].ppos={pos.x-vel.x*(1-heatcons),pos.y-vel.y*(1-heatcons)};
        }
    }
    return 0;
}

int screenconstraint(particle* particlelist, int particlelistlenght){
    for(int i=0;i<particlelistlenght;i++){
        double lv=vleng>>1;
        double lh=horl>>1;
        if(particlelist[i].pos.y-particlelist[i].radius<-lv){
            particlelist[i].pos.y=-lv+particlelist[i].radius;
        }
        if(particlelist[i].pos.y+particlelist[i].radius>lv){
            particlelist[i].pos.y=lv-particlelist[i].radius;
        }
        if(particlelist[i].pos.x-particlelist[i].radius<-lh){
            particlelist[i].pos.x=-lh+particlelist[i].radius;
        }
        if(particlelist[i].pos.x+particlelist[i].radius>lh){
            particlelist[i].pos.x=lh-particlelist[i].radius;
        }
    }
    return 0;
}