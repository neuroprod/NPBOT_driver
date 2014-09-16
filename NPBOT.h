//
//  NPBOT.h
//  NPBOT-driver
//
//  Created by Kris Temmerman on 13/09/14.
//
//

#ifndef __NPBOT_driver__NPBOT__
#define __NPBOT_driver__NPBOT__
#include <Arduino.h>
#include "Ticker.h"
#include "Axis.h"
class NPBOT
{

public:
    NPBOT();
    
    void setup();
    void update();
    void checkSerial();

    
    Ticker ticker;
    Axis axis1;
    Axis axis2;
    Axis axis3;
    Axis axis4;
    Axis axis5;
    Axis axis6;
  
    unsigned long previousMicros ;
    bool isHomeing;
    Vector<Axis *> axises;
    
    
    char serialData[80];
     char serialEnd ;
};

#endif /* defined(__NPBOT_driver__NPBOT__) */
