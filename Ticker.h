//
//  Ticker.h
//  NPBOT-driver
//
//  Created by Kris Temmerman on 13/09/14.
//
//

#ifndef __NPBOT_driver__Ticker__
#define __NPBOT_driver__Ticker__

#include <Arduino.h>
#include "Axis.h"
#include "Vector.h"

class Ticker
{


public:
    Ticker();
    void setup();
    void addAxis(Axis * axis );
    void setTicks(int numTicks );
    
    void update(double timeElapsed);

    Vector<Axis *> axises;
   
    bool pulsOn ;
    double startTime;
    
   void setIntervalForNextTick();
    
    int  ticksDone;
    int totalTicks;
    int  totalTime;
    
    float maxSpeed ;
    float accTime ;
    float acceleration ;
    int ticksTillMaxSpeed;
    
    int tickInterval;
    int maxInterval;
    int fullSpeedTick;
    int slowDownTick;
    int getIntervalForAccTick(int tick );
};

#endif /* defined(__NPBOT_driver__Ticker__) */
