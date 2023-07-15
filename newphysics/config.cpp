 #include "config.hpp"
 int horl=1900;
 int vleng=1000;
 double grav=20;
 double substep=1.d/360.d;
 bool Heatcol=false;//HEAT transfer in colisons
 bool Heatexp=false;//HEAT EXPANSION
 bool Realcolisions=false;
 bool ConsBounce=true;
 double heatloss=0;
 double heatbounce=0;//particle
 double heatcons=-0.001;//constrain
int constype=0;