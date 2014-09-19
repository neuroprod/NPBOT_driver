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
void Axis::setup(int _pullPin,int _dirPin, bool _inverseDir)
{
    
    inverseDir = _inverseDir;
    isHome =false;
    position =0;
    pullPin  =_pullPin;
    dirPin  =_dirPin;
    
    pinMode(pullPin, OUTPUT);
    pinMode(dirPin, OUTPUT);
    digitalWrite(dirPin, LOW);
    digitalWrite(pullPin, LOW);
}
int Axis::setTargetPos(int tarPosition)
{
   
    stepsTodo = tarPosition-position;
    
    if(stepsTodo <0)
    {
        dir =false;
        stepsTodo *=-1;
    }else
    {
    
        dir =true;
    }
    
    return stepsTodo;

}
void Axis::startStepping (int maxAxisSteps)
{
    
    
    if(inverseDir){
     digitalWrite(dirPin, !dir);
    }else
    {
    digitalWrite(dirPin, dir);
    }
    
    dx =maxAxisSteps;
    dy = stepsTodo;
    px=dy-dx;
    py=dx-dy;
    
    digitalWrite(pullPin, LOW);


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
    
       digitalWrite(pullPin, HIGH);
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
void Axis::setupHomingParams(bool _dir,int _stepDelay, int _homePin)
{
  
    homePin =_homePin;
    homeDir =_dir;
    homeStepDelay =_stepDelay;
    
    
    pinMode(homePin, INPUT);
    
   
  
}
void Axis::startHoming()
{
    if(digitalRead(homePin))
    {
        isHome =true;
        return;
    }
    
    homeTime =0;
    isHome =false;
    digitalWrite(dirPin, homeDir );
    homePullToggle =false;
   
}
void Axis::stepHoming(double timeElapsed)
{
    if(isHome) return;

    homeTime += timeElapsed;
    if(homeTime>homeStepDelay)
    {
        homeTime-=homeStepDelay;
        if(homePullToggle)
        {
            digitalWrite(pullPin, HIGH);
            
        
        }else
        {
            digitalWrite(pullPin, LOW);
            if(digitalRead(homePin))
            {
                isHome =true;
            
            }
        
        }
        homePullToggle =!homePullToggle;
    
    }
}

