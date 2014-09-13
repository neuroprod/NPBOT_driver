//
//  Axis.cpp
//  NPBOT-driver
//
//  Created by Kris Temmerman on 13/09/14.
//
//

#include "Axis.h"
#include <Arduino.h>
Axis::Axis(){}
void Axis::setup(int _pullPin,int _dirPin)
{
    pullPin  =_pullPin;
    dirPin  =_dirPin;
    
    pinMode(pullPin, OUTPUT);
    pinMode(dirPin, OUTPUT);
}


void Axis::setSteps (int steps, bool _dir, int maxAxisSteps)
{
    dir =_dir;
    digitalWrite(dirPin, dir);
    
    
    
    //Bresenham's Line Algorithm simple: dx>dy  and all positive 
    dx =maxAxisSteps;
    dy = steps;
    px=dy-dx;
    py=dx-dy;

    digitalWrite(pullPin, LOW);
    
}

void Axis::tickOn()
{

   
    //Bresenham's Line Algorithm simple
   
    
    
    
    if(px<0)
    {
        px=px+2*dy;
    }
    else
    {
    
        pinMode(pullPin, HIGH);
        if(dir )
        {
            position++;
        }
        else
        {
            position--;
        }
        px=px+2*(dy-dx);

    }
}

void Axis::tickOff()
{
    

    digitalWrite(pullPin, LOW);
}

////homeing
void Axis::setupHomingParams(bool dir,int stepDelay)
{


}
void Axis::goHome()
{

    position =0;
}
