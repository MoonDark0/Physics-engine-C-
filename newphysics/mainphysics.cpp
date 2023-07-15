#include "structs.hpp"
#include "config.hpp"
#include "broadet.hpp"
#include "constraints.hpp"
#include "mainphysics.hpp"
#include <cstdio>
#include <cstdlib>

int move(particle* plist, int lenplist){
    for(int i=0;i<lenplist;i++){
        vector2 temp= plist[i].pos;
        plist[i].pos.x=2*plist[i].pos.x-plist[i].ppos.x + plist[i].ac.x*substep*substep;
        plist[i].pos.y=2*plist[i].pos.y-plist[i].ppos.y+(grav+plist[i].ac.y)*substep*substep;
        plist[i].ppos=temp;
        vector2 a={0,0};
        plist[i].ac=a;
    }

    return 0;
}

int physicsiteration(particle*plist,int* sorted,int lenght){
    if(constype==0){
        if (ConsBounce){
            realcircularconstraint(plist,lenght);
        }
        else{
            circularconstraint(plist,lenght);
        }
    }
    if (constype==1){
        screenconstraint(plist,lenght);
    }
    sort(plist,sorted,lenght);
    sweepandprune(plist,sorted,lenght);
    move(plist,lenght);
    return 0;
}

