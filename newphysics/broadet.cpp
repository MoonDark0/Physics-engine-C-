#include "config.hpp"
#include "structs.hpp"
#include "broadet.hpp"
#include "vectors.hpp"
#include "solving.hpp"
#include<cstdio>
#include<cstdlib>
#include<vector>

int sort(particle* particlelist,int* sorted,int lengparticlelist){
    for(int i=1;i<lengparticlelist;i++){
        int ar=i-1;
        int currentpos=sorted[i];
        double current=particlelist[sorted[i]].pos.x-particlelist[sorted[i]].radius;
        while(ar>-1 && (particlelist[sorted[ar]].pos.x-particlelist[sorted[ar]].radius)>(current)){
            sorted[ar+1]=sorted[ar];
            ar--;
        }
        sorted[ar+1]=currentpos;
    }
    return 0;
}

int sweepandprune(particle* particlelist,int* sorted,int lengparticlelist){
    std::vector<int> posiblecol;//set up
    int *activelist = new int[lengparticlelist];
    double *maxlist = new double[lengparticlelist];
    for(int i=0;i<lengparticlelist;i++){//ad to the active list sorted by the min radius
        int current=sorted[i];
        activelist[i]=current;
        int k=i-1;
        double min=particlelist[current].pos.x - particlelist[current].radius;
        double max=particlelist[current].pos.x + particlelist[current].radius;
        maxlist[i]=max;
        while((k>-1) && (maxlist[k])>=(min)){

                posiblecol.push_back(activelist[k]);//colision detected
                posiblecol.push_back(current);

                if((maxlist[k])>max){//shift lists
                    activelist[k+1]=activelist[k];
                    maxlist[k+1]=maxlist[k];
                    activelist[k]=current;
                    maxlist[k]=max;
                }
                k--;
            
        }
    }
        delete[] activelist;//clean
        delete[] maxlist;
        for(int o=0;o<posiblecol.size();o+=2){//solve the colisions
            int i=posiblecol[o];
            int j=posiblecol[o+1];
            double radius=particlelist[i].radius+particlelist[j].radius;
            vector2 vi=getorigin(particlelist[i].pos,particlelist[j].pos);
            double leng = lengsqt(vi);
            if(radius*radius>leng){
                unrealisticsolve(i,j,particlelist);
            }

            
        }
    return 0;
}