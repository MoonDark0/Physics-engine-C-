#include <SFML/Graphics.hpp>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include <vector>
#include<iostream>
//g++ -c Physicsengine.cpp -lsfml-window -lsfml-graphics -lsfml-system -DSFML_STATIC
//
//setup
//config
int horl=1900;
int vleng=1000;
double grav=5;
double substep=1.d/360.d;
bool Heatcol=false;//HEAT transfer in colisons
bool Heatexp=false;//HEAT EXPANSION
bool Realcolisions=false;
bool ConsBounce=true;
double heatloss=0;
double heatbounce=0;//particle
double heatcons=0.1;//constrain
int constype=1;

struct edge
{
    double x;
    int object;
    bool maxormin;
};


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
    double bradius;
    int type;
    bool fixed;//not yet
    vector2 ac;
    int r;
    int g;
    int b;
};


//utility functions
vector2 getvec2(vector2 v1, vector2 v2){//returns vector
    vector2 c={v2.x-v1.x,v2.y-v1.y};
    return c;
}

vector2 normalize(vector2 b){
    double leng=sqrt(b.x*b.x+b.y*b.y);
    double x=b.x/leng;
    double y=b.y/leng;
    vector2 c ={x,y};
    return c;
}

double lengtsq(vector2 p){
    return p.x*p.x+p.y*p.y;
}
//global
//plist is array of particles
particle *plist= new particle[1];
int *sortbyx= new int[1];
//spring
int lenplist=0;
int lenslist=0;

//main functions

int sort(){
    for(int i=1;i<lenplist;i++){
        int ar=i-1;
        int currentpos=sortbyx[i];
        double current=plist[sortbyx[i]].pos.x-plist[sortbyx[i]].radius;
        while(ar>-1 && (plist[sortbyx[ar]].pos.x-plist[sortbyx[ar]].radius)>(current)){
            sortbyx[ar+1]=sortbyx[ar];
            ar--;
        }
        sortbyx[ar+1]=currentpos;
    }
    return 0;
}


int quicksort(int leng,int *array){
    if(leng<2){
        return 0;
    }
    int alen=0;
    int blen=0;
    int *a = new int[leng];
    int *b = new int[leng];
    int pivot=array[leng/2];
    for(int i=0;i<leng;i++){
        if(leng/2==i){

        }
        else{
        if ((plist[array[i]].pos.x-plist[array[i]].radius)<(plist[pivot].pos.x-plist[pivot].radius)){
            a[alen]=array[i];
            alen++;
        }
        else{
            b[blen]=array[i];
            blen++;
        }
        }
    }
    quicksort(alen,a);
    quicksort(blen,b);
    
    for(int i=0;i<blen;i++){
        array[i]=b[i];
    }
    array[blen]=pivot;
    for(int i=0;i<alen;i++){
        array[blen+1+i]=a[i];
    }
    delete[] a;
    delete[] b;
    return 0;
}



//addparticle WIP
int addobj(double px,double py,double spx,double spy,double radius,int r,int g,int b){
    particle p ={{px,py},{px-spx*substep,py-spy*substep},1,0,radius,radius,0,false,{0,0},r,g,b};
    particle *nplist= new particle[lenplist+1];
    int *nsortbyx= new int[lenplist+1];
    for(int i=0;i<lenplist;i++){
        nplist[i]=plist[i];
        nsortbyx[i]=sortbyx[i];
    }
    delete[] plist;
    delete[] sortbyx;
    plist=nplist;
    sortbyx=nsortbyx;

    plist[lenplist]=p;
    sortbyx[lenplist]=lenplist;
    lenplist++;
    
    
    
return 0;
}
//done cleans aceleration
int cleanacc(){
    for(int i=0;i<lenplist;i++){
        plist[i].ac={0,0};
    }
    return 0;
};
//moves
int move(){
    for(int i=0;i<lenplist;i++){
        vector2 temp= plist[i].pos;
        plist[i].pos.x=2*plist[i].pos.x-plist[i].ppos.x + plist[i].ac.x*substep*substep;
        plist[i].pos.y=2*plist[i].pos.y-plist[i].ppos.y+(grav+plist[i].ac.y)*substep*substep;
        plist[i].ppos=temp;
    }

    return 0;
};
int constrains(){
if(constype==0){
    for(int i=0;i<lenplist;i++){
        vector2 vec=plist[i].pos;
        double maxd=(450.d-plist[i].radius);
        double dist=vec.x*vec.x+vec.y*vec.y;
        if(dist>maxd*maxd){
            vector2 s=normalize(vec);
            if(ConsBounce){
                vector2 ef=getvec2(plist[i].ppos,plist[i].pos);
                double dot=ef.x*(-s.x)+ef.y*(-s.y);
                vector2 tef={0,0};
                tef.x=(-s.x)*dot*2.d;
                tef.y=(-s.y)*dot*2.d;
                ef.x=ef.x-tef.x;
                ef.y=ef.y-tef.y;
                double pxt=s.x*maxd;
                double pyt=s.y*maxd;
                plist[i].ppos.x=pxt-ef.x*(1-heatcons);
                plist[i].ppos.y=pyt-ef.y*(1-heatcons);
            }
            plist[i].pos.x=s.x*maxd;
            plist[i].pos.y=s.y*maxd;
        }
    }
}
if(constype==1){
    for(int i=0;i<lenplist;i++){
        if(plist[i].pos.y-plist[i].radius<-vleng/2){
            plist[i].pos.y=-vleng/2.d+plist[i].radius;
        }
        if(plist[i].pos.y+plist[i].radius>vleng/2){
            plist[i].pos.y=vleng/2.d-plist[i].radius;
        }
        if(plist[i].pos.x-plist[i].radius<-horl/2){
            plist[i].pos.x=-horl/2.d+plist[i].radius;
        }
        if(plist[i].pos.x+plist[i].radius>horl/2){
            plist[i].pos.x=horl/2.d-plist[i].radius;
        }
    }
}
return 0;
}
//basiccolisions

int solve(int i,int j){
        double radius=plist[i].radius+plist[j].radius;
        vector2 vi=getvec2(plist[j].pos,plist[i].pos);
        double leng = lengtsq(vi);
        vector2 vj=getvec2(plist[i].pos,plist[j].pos);
        double distance= sqrt(leng);
        vi=normalize(vi);
        vj=normalize(vj);
        double tomove = (radius-distance)/2.d;
        plist[i].pos.x=plist[i].pos.x+vi.x*tomove;
        plist[i].pos.y=plist[i].pos.y+vi.y*tomove;
        plist[j].pos.x=plist[j].pos.x+vj.x*tomove;
        plist[j].pos.y=plist[j].pos.y+vj.y*tomove;
    return 0;
}

int sweepandprune(){
    std::vector<int> posiblecol;//set up
    int *activelist = new int[lenplist];
    double *maxlist = new double[lenplist];
    for(int i=0;i<lenplist;i++){//ad to the active list sorted by the min radius
        int current=sortbyx[i];
        activelist[i]=current;
        int k=i-1;
        double min=plist[current].pos.x - plist[current].radius;
        double max=plist[current].pos.x + plist[current].radius;
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
            double radius=plist[i].radius+plist[j].radius;
            vector2 vi=getvec2(plist[i].pos,plist[j].pos);
            
            double leng = lengtsq(vi);
            if(radius*radius>leng){
                solve(i,j);
            }

            
        }
    return 0;
}



int colision(){
    for(int i=0;i<lenplist;i++){
        for(int j=i+1;j<lenplist;j++){
            double radius=plist[i].radius+plist[j].radius;
            vector2 vi=getvec2(plist[i].pos,plist[j].pos);
            
            double leng = lengtsq(vi);
            if(radius*radius>leng){
                solve(i,j);
            }

        }
    }
    return 0;
}

int issorted(int* list,int leng){
    for(int i=1;i<leng;i++){
        if(plist[list[i-1]].pos.x-plist[list[i-1]].radius>plist[list[i]].pos.x-plist[list[i]].radius){
        }
    }
    return 0;
}

//main
int physics(){
cleanacc();
sort();
//quicksort(lenplist,sortbyx);
sweepandprune();
//colision();
constrains();
move(); 

return 0;
}

int generate(int o){
    

}

int main()
{   
    int o=-500;
    sf::RenderWindow window(sf::VideoMode(horl, vleng), "SFML window");
    window.setFramerateLimit(60);
    
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
        
        for(int p=0;p<6;p++){
         physics();  
        }
        sf::CircleShape c1(20.f);
        if(constype==0){
            window.clear(sf::Color(100,100,100));
            c1.setRadius(450);
            c1.setPosition(horl/2-450,vleng/2-450);
            c1.setFillColor(sf::Color::Black);
            c1.setPointCount(100);
            window.draw(c1);
        }
        if(constype==1){
            window.clear(sf::Color(0,0,0));
        }
        o=generate(o);
        c1.setPointCount(40);
        for(int i=0;i<lenplist;i++){
        c1.setRadius(plist[i].radius);
        c1.setFillColor(sf::Color(plist[i].r,plist[i].g,plist[i].b));
        c1.setPosition(plist[i].pos.x+(horl>>1)-plist[i].radius,plist[i].pos.y+(vleng>>1)-plist[i].radius);
        window.draw(c1);
        };
        // end the current frame
        window.display();
    }

    return 0;
}

