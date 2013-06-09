/*THE NUMBER OF CALCULATIONS SCALES WITH N^2 SO IT CAN SLOW DOWN FAST*/

#define _PI  3.1415926535
#define _EPS_0 8.854187E-12
#define _G_NEWTON 6.67384E-11

#define _FOREVER -1

#include <iostream>
#include <sstream>

#include <cstring>
#include <cstdlib>
#include <cmath>
#include <thread>
#include <chrono>

#include <GL/gl.h>
#include <GL/freeglut.h>

using namespace std;

class vect3d
{
private:
    double array[3];
public:
    vect3d()
    {
        array[0] = 0;
        array[1] = 0;
        array[2] = 0;
    }
    vect3d(double d1,double d2,double d3)
    {
        array[0] = d1;
        array[1] = d2;
        array[2] = d3;
    }

    double operator[](int i)
    {
        if(i<3)
        {
            return array[i];
        }
        else
        {
            return 0;
        }
    }

    vect3d operator +(vect3d param)
    {
        return vect3d(array[0] + param[0],array[1] + param[1],array[2] + param[2]);
    }

    void operator +=(vect3d param)
    {
        (*this) = vect3d(array[0] + param[0],array[1] + param[1],array[2] + param[2]);
    }

    vect3d operator -(vect3d param)
    {
        return vect3d(array[0] - param[0],array[1] - param[1],array[2] - param[2]);
    }

    vect3d operator *(double param)
    {
        return vect3d(array[0] * param,array[1] * param,array[2] * param);
    }

    double dot(vect3d param)
    {
        return (array[0]*param[0]) + (array[1]*param[1]) + (array[2]*param[2]);
    }
    double mod()
    {
        return (array[0]*array[0]) + (array[1]*array[1]) + (array[2]*array[2]);
    }
};

class particle
{
public:
    vect3d location;
    vect3d velocity;
    double charge;
    double mass;
    float R,G,B;
    GLfloat scaledX, scaledY, scaledZ;
    particle(vect3d location, vect3d velocity,double mass, double charge,float R, float G, float B)
    {
        (*this).R = R;
        (*this).G = G;
        (*this).B = B;
        (*this).location = location;
        (*this).velocity = velocity;
        (*this).mass = mass;
        (*this).charge = charge;
    }

    particle(vect3d location)
    {
        *this = particle(location, vect3d(0.0, 0.0, 0.0), 1.0, 0.0, 0.0, 0.1, 1.0);

    }

    particle()
    {
        *this = particle(vect3d(0.0, 0.0, 0.0), vect3d(0.0, 0.0, 0.0), 1.0, 0.0, 0.0, 0.1, 1.0);

    }

    void draw(double xMin,double xMax,double yMin, double yMax,double zMin,double zMax)
    {
        glColor3f(R,G,B);
        scaledX = 2.0*((location[0] - xMin)/(xMax - xMin)) - 1.0;
        scaledY = 2.0*((location[1] - yMin)/(yMax - yMin)) - 1.0;
        scaledZ = 2.0*((location[2] - zMin)/(zMax - zMin)) - 1.0;
        glBegin(GL_POINTS);
        glVertex3f(scaledX,scaledY,scaledZ);
        glEnd();
    }

    particle differentiate(vect3d acceleration)
    {
        return particle(velocity, acceleration, 0.0, 0.0, 0.0, 0.0, 0.0);
    };

    particle operator *(double param)
    {
        return particle(location*param,velocity*param,mass*param,charge*param,R,G,B);
    }
    particle operator +(particle param)
    {
        return particle(location +param.location,velocity+param.velocity,mass+param.mass,charge+param.charge,R,G,B);
    }

};

class world
{
private:
    particle * particleArray;
    double xMin, xMax;
    double yMin, yMax;
    double zMin, zMax;
    int numParticles;
    vect3d * acceleration;
    particle * k;
    bool square;

    std::chrono::system_clock::time_point nowTime;
    std::chrono::system_clock::time_point prevTime;
    std::chrono::duration<int,std::milli> waitTime;

    void renderString(float x, float y, void *font, const char* string)
    {
        glColor3f(0.0, 0.0, 0.0);
        glRasterPos2f(x, y);
        glutBitmapString(font, (unsigned char *)string);
    }

    void drawAxis()
    {
        ostringstream lables[2][2];
        ostringstream origin;

        glColor3f(0.0,0.0,0.0);
        glLineWidth(3);

        glBegin(GL_LINES);
        glVertex2f(-1.00,0.00);
        glVertex2f( 1.00,0.00);

        glVertex2f( 0.00,-1.00);
        glVertex2f( 0.00, 1.00);

        glVertex2f(-1.00, 0.05);
        glVertex2f(-1.00,-0.05);

        glVertex2f( 1.00, 0.05);
        glVertex2f( 1.00,-0.05);

        glVertex2f(-0.05,-1.00);
        glVertex2f( 0.05,-1.00);

        glVertex2f(-0.05, 1.00);
        glVertex2f( 0.05, 1.00);
        glEnd();

        lables[0][0] << xMin;
        lables[0][1] << xMax;
        lables[1][0] << yMin;
        lables[1][1] << yMax;

        origin << '(' << 0.5*(xMax + xMin) << ',' << 0.5*(yMax + yMin) << ')';

        renderString(-1.0                , 0.05, GLUT_BITMAP_TIMES_ROMAN_24, lables[0][0].str().c_str());
        renderString(0.98-0.005*log(xMax), 0.05, GLUT_BITMAP_TIMES_ROMAN_24, lables[0][1].str().c_str());
        renderString(0.0                 , -1.0, GLUT_BITMAP_TIMES_ROMAN_24, lables[1][0].str().c_str());
        renderString(0.0                 , 0.95, GLUT_BITMAP_TIMES_ROMAN_24, lables[1][1].str().c_str());

        renderString(0.0                 , 0.05, GLUT_BITMAP_TIMES_ROMAN_24, origin.str().c_str());
    }

    void updateMaxima()
    {
        if(square)
        {
            for(int i = 0; i<numParticles; ++i)
            {
                for(int j = 0; j<3; ++j)
                {
                    if(fabs(particleArray[i].location[j]) > xMax)
                    {
                        xMax = 1.2*fabs(particleArray[i].location[j]);
                    }
                }
            }

            xMin = -xMax;
            yMin = xMin;
            yMax = xMax;
            zMin = xMin;
            zMax = xMax;
        }
        else
        {
            for(int i = 0; i<numParticles; ++i)
            {

                if(particleArray[i].location[0] <= xMin)
                {
                    xMin = 1.2*particleArray[i].location[0] ;
                }
                else if(particleArray[i].location[0]  >= xMax)
                {
                    xMax = 1.2*particleArray[i].location[0] ;
                }

                if(particleArray[i].location[1]  <= yMin)
                {
                    yMin = 1.2*particleArray[i].location[1];
                }
                else if(particleArray[i].location[1]  >= yMax)
                {
                    yMax = 1.2*particleArray[i].location[1];
                }

                if(particleArray[i].location[2]  <= zMin)
                {
                    zMin = 1.2*particleArray[i].location[2];
                }
                else if(particleArray[i].location[2]  >= zMax)
                {
                    zMax = 1.2*particleArray[i].location[2];
                }
            }
        }
    }

public:

    world()
    {
        *this = *new world(800,800,true);
    }

    world(int xSize,int ySize,bool isSquare)
    {
        square = isSquare;
        char *myargv [1];
        int myargc=1;
        myargv [0]=strdup ("Graph");
        glutInit(&myargc, myargv);

        glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
        glutInitWindowSize(xSize,ySize);
        if(square)
        {
            glutCreateWindow("Distances are to scale sizes are not - everything is a particle");
        }
        else
        {
            glutCreateWindow("Distances are to scale sizes are not - everything is a particle (and the x and y scales are probably different)");
        }

        glMatrixMode ( GL_PROJECTION );
        glClearColor ( 1, 1, 1, 0.0 );
        glClear(GL_COLOR_BUFFER_BIT);
        glPointSize(6.0);

        (*this).xMin = 0;
        (*this).xMax = 0;
        (*this).yMin = 0;
        (*this).yMax = 0;
        (*this).zMin = -0.1;
        (*this).zMax = 0.1;
        numParticles = 0;

        particleArray = (particle *)malloc(0);
        k = (particle *)malloc(4*sizeof(particle));
        for(int i = 0; i<4; ++i)
        {
            k[i] =  particle();
        }
        waitTime = std::chrono::duration<int,std::milli>(20);
    }

    void addParticle(particle point)
    {
        ++numParticles;
        particleArray = (particle *)realloc(particleArray,numParticles * sizeof(particle));
        particleArray[numParticles - 1] = point;
        acceleration = (vect3d *)realloc(acceleration,numParticles * sizeof(vect3d));
        acceleration[numParticles -1] = vect3d(0,0,0);
        updateMaxima();
    }

    void display()
    {
        glClear(GL_COLOR_BUFFER_BIT);
        updateMaxima();
        drawAxis();
        for(int i = 0; i<numParticles; ++i)
        {
            particleArray[i].draw(xMin,xMax,yMin,yMax,zMin,zMax);
        }
        glFlush();
        glutSwapBuffers();
    }

    void updateParticles(double h) //I think this is massively inefficient
    {
        for(int i = 0; i<numParticles; ++i)
        {
            acceleration[i] = vect3d(0,0,0);
            for(int j = 0; j < numParticles; ++j)
            {
                if(i != j)
                {
                    acceleration[i] +=  (particleArray[j].location - particleArray[i].location ) * ( ((1/particleArray[i].mass) * (1/(4*_PI*_EPS_0)) *  particleArray[i].charge * particleArray[j].charge)/pow((particleArray[i].location - particleArray[j].location ).mod(),1.5));
                    acceleration[i] +=  (particleArray[j].location - particleArray[i].location ) * ((_G_NEWTON)*particleArray[j].mass/pow((particleArray[i].location - particleArray[j].location ).mod() ,1.5));
                }
            }
        }

        for(int i = 0; i<numParticles; ++i)
        {
            k[0] = particleArray[i].differentiate(acceleration[i]);
            k[1] = (particleArray[i] + k[0]*(h/2)).differentiate(acceleration[i]);
            k[2] = (particleArray[i] + k[1]*(h/2)).differentiate(acceleration[i]);
            k[3] = (particleArray[i] + k[2]*h).differentiate(acceleration[i]);
            particleArray[i] = particleArray[i] + (k[0] + k[1]*2 + k[2]*2 + k[3])*(h/6);
        }
    }

    void animate(double h,double t_max)
    {
        /*The chrono shit makes this loads faster! It looks like drawing is slooooooooow*/
        nowTime = std::chrono::system_clock::now();
        prevTime = nowTime;
        if(t_max == _FOREVER)
        {
            while(1)
            {
                nowTime = std::chrono::system_clock::now();
                if(nowTime - prevTime > waitTime)
                {
                    prevTime = nowTime;
                    display();
                }
                updateParticles(h);
            }
        }
        else
        {
            for(double t = 0; t<t_max; t += h)
            {
                nowTime = std::chrono::system_clock::now();
                if(nowTime - prevTime > waitTime)
                {
                    prevTime = nowTime;
                    display();
                }
                updateParticles(h);
            }
        }
    }

    void setSquare(bool val)
    {
        square = val;
    }
};


