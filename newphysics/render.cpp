#include "config.hpp"
#include "render.hpp"
#include <SFML/Graphics.hpp>
#include<cstdio>
#include<cstdlib>

int render(sf::RenderWindow& window,particle* plist, int lenplist){
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
        c1.setPointCount(40);
        for(int i=0;i<lenplist;i++){
        c1.setRadius(plist[i].radius);
        c1.setFillColor(sf::Color(plist[i].r,plist[i].g,plist[i].b));
        c1.setPosition(plist[i].pos.x+(horl>>1)-plist[i].radius,plist[i].pos.y+(vleng>>1)-plist[i].radius);
        window.draw(c1);
        };
        // end the current frame
        window.display();
        return 0;
}