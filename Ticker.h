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
    int ticksLeft;
    bool pulsOn ;
    double startTime;
};

#endif /* defined(__NPBOT_driver__Ticker__) */
