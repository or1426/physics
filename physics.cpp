#include <iostream>
#include <cstdio>
#include "physics.h"

using namespace std;

double RAND()
{
    srand(rand());
    return (2*(rand()/(double)RAND_MAX)-1);
}
int main()
{
    /*SUN EARTH MOON SYSTEM*/ //cool
    /*
    #include "planets.h"
    world w;
    w.addParticle(particle(vect3d(R_O_SUN,0.0,0.0), vect3d(V_O_SUN,0.0,0.0), MASS_SUN,0 ,1,0.2,0.0));
    w.addParticle(particle(vect3d(R_O_SUN+R_O_EARTH,0.0,0.0), vect3d(0.0,V_O_SUN+V_O_EARTH,0.0), MASS_EARTH,0 ,0,0,1));
    w.addParticle(particle(vect3d(R_O_SUN+R_O_EARTH+R_O_MOON,0.0,0.0), vect3d(0,V_O_SUN+V_O_EARTH+V_O_MOON,0), MASS_MOON,0 ,0.5,0.5,0.5));
    double h = 5;
    double t_max = 3600*24*28*12*20;
    w.animate(h,t_max);
    */

    /*Satalite around the earth*/
    #include "planets.h"
    world w;
    w.addParticle(particle(vect3d(0,0.0,0.0), vect3d(0.0,0,0.0), MASS_EARTH,0 ,0,0,1));
    w.addParticle(particle(vect3d(5E6,0,0),vect3d(0,12E3,0),1000,0,1,0,0));
    w.addParticle(particle(vect3d(-5E6,0,0),vect3d(0,-12E3,0),1000,0,1,0,0));
    w.addParticle(particle(vect3d(0,-5E6,0),vect3d(12E3,0,0),1000,0,1,0,0));
    w.addParticle(particle(vect3d(0,5E6,0),vect3d(-12E3,0,0),1000,0,1,0,0));
    w.animate(0.05,_FOREVER);
    /*SOLAR SYSTEM*/
    /*
    very cool but bad 'cos inner planets move much faster than outer ones
    (also it takes into account influences that are negligable like the pull of pluto on mercury)
    all planets start lined up at perihelion (which must have happened at *somepoint*)
    */
    /*
    #include "planets.h"
    world w;
    w.addParticle(particle(vect3d(R_O_SUN,0.0,0.0), vect3d(V_O_SUN,0.0,0.0), MASS_SUN,0 ,0.8,0.8,0.1));
    w.addParticle(particle(vect3d(R_O_SUN+R_O_MERCURY,0.0,0.0), vect3d(0.0,V_O_SUN+V_O_MERCURY,0.0), MASS_MERCURY,0 ,1,0,1));
    w.addParticle(particle(vect3d(R_O_SUN+R_O_VENUS,0.0,0.0), vect3d(0.0,V_O_SUN+V_O_VENUS,0.0), MASS_VENUS,0 ,1,0.82,0.2));
    w.addParticle(particle(vect3d(R_O_SUN+R_O_EARTH,0.0,0.0), vect3d(0.0,V_O_SUN+V_O_EARTH,0.0), MASS_EARTH,0 ,0,0,1));
    w.addParticle(particle(vect3d(R_O_SUN+R_O_MARS,0.0,0.0), vect3d(0.0,V_O_SUN+V_O_MARS,0.0), MASS_MARS,0 ,1,0,0));
    w.addParticle(particle(vect3d(R_O_SUN+R_O_JUPITER,0.0,0.0),vect3d(0,V_O_SUN+V_O_JUPITER,0.0),MASS_JUPITER,0.0,1,0.6,0.2));
    w.addParticle(particle(vect3d(R_O_SUN+R_O_SATURN,0.0,0.0), vect3d(0.0,V_O_SUN+V_O_SATURN,0.0), MASS_SATURN,0 ,1,0.4,0.1));
    w.addParticle(particle(vect3d(R_O_SUN+R_O_URANUS,0.0,0.0), vect3d(0.0,V_O_SUN+V_O_URANUS,0.0), MASS_URANUS,0 ,0,0,1));
    w.addParticle(particle(vect3d(R_O_SUN+R_O_NEPTUNE,0.0,0.0), vect3d(0.0,V_O_SUN+V_O_NEPTUNE,0.0), MASS_NEPTUNE,0 ,0,1,0));
    w.addParticle(particle(vect3d(0.0,R_O_SUN+R_O_PLUTO,0.0), vect3d(-V_O_SUN-V_O_PLUTO,0.0,0.0), MASS_PLUTO,0, 0.5,0.5,0.5));
    w.addParticle(particle(vect3d(R_O_SUN+R_O_HAL,0.0,0.0), vect3d(0.0,V_O_SUN+V_O_HAL,0.0), MASS_HAL,0 ,0.5,0.5,0.5));
    double h = 1000;
    double t_max = _FOREVER;
    w.animate(h,t_max);
    */


    /*RUTHERFORD SCATTERING*/ //A bit shit untill I get zooming in to work as well as out!
    /*
    #include "subatomic.h"
    world w;
    w.addParticle(particle(vect3d(0,0.5,0.0), vect3d(0,0.0,0.0), MASS_GOLD_NUCLEUS,CHARGE_GOLD_NUCLEUS ,0.0,0.0,0.0));
    w.addParticle(particle(vect3d(5E-14,0.5,0.0), vect3d(-V_RUTHERFORD_ALPHA,0.5,0.0), MASS_ALPHA,CHARGE_ALPHA ,1.0,0.0,0.0));
    double h = 0.000000000000000000000003;
    double t_max = 1;
    w.animate(h,t_max);
    */

    return 0;
}
