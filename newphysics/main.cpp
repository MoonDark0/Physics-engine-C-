#include <SFML/Graphics.hpp>
#include "render.hpp"
#include "mainphysics.hpp"
#include"structs.hpp"
#include "config.hpp"
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include <vector>
#include<iostream>





struct returning
{
    int lenght;
    particle* plist;
    int* sorted;
};

returning addobj(particle* plist, int lenght,int* sortbyx,vector2 pos,vector2 speed, double size, int r, int g, int b){
    particle p ={pos,{pos.x-speed.x*substep,pos.y-speed.y*substep},1,0,size,1,false,{0,0},r,g,b};
    particle *nplist= new particle[lenght+1];
    int *nsortbyx= new int[lenght+1];
    for(int i=0;i<lenght;i++){
        nplist[i]=plist[i];
        nsortbyx[i]=sortbyx[i];
    }
    delete[] plist;
    delete[] sortbyx;
    plist=nplist;
    sortbyx=nsortbyx;

    plist[lenght]=p;
    sortbyx[lenght]=lenght;
    lenght++;
    
    
    
return {lenght,plist,sortbyx};
}


returning generate(int o,particle *plist, int* sortbyx, int lenght){
    returning a={lenght,plist,sortbyx};
    if(o>10000){
        return a;
    }
    if(((o+20)%40)==0){
    a=addobj(plist,lenght,sortbyx,{0,100},{0,30},10,255,255,255); 
    }
    if(((o)%40)==0){
    a=addobj(plist,lenght,sortbyx,{100,100},{0,30},10,255,20,255); 
    }
    return a;
}

//config

int main(){
    //array setup
    particle *plist= new particle[1];
    int *sortbyx= new int[1];
    int lenplist=0;

    int o=-500;
    sf::RenderWindow window(sf::VideoMode(horl, vleng), "Physics");
    window.setFramerateLimit(144);
    
    //addobj(0,100,0,0,10,100,255,100);
    //addobj(100,100,0,0,10,100,0,100);
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        };
        
        
        render(window,plist,lenplist);

        for(int p=0;p<7;p++){
            physicsiteration(plist,sortbyx,lenplist);  
        }
        returning a=generate(o,plist,sortbyx,lenplist);
        plist=a.plist;
        lenplist=a.lenght;
        sortbyx=a.sorted;
        o++;
    }

    return 0;
}