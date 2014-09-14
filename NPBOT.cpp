//
//  NPBOT.cpp
//  NPBOT-driver
//
//  Created by Kris Temmerman on 13/09/14.
//
//

#include "NPBOT.h"
#include <Arduino.h>


NPBOT::NPBOT(){}

void NPBOT::setup()
{



    Serial.begin(115200);
    isHomeing =false;
    previousMicros =0;
    // pull - dir
    axis1.setup(30,53);
    axis1.setupHomingParams(true,400, 7);
    axis2.setup(32,51);
    axis2.setupHomingParams(true,200, 6);
   

    
    
    ticker.addAxis(&axis1);
    ticker.addAxis(&axis2);
    ticker.setup();
}


void NPBOT::update()
{
    if(Serial.available()){
        while(Serial.available())
        {
            Serial.read();
            //int numbytes  =Serial.readBytesUntil(serialEnd, serialData, bufferSize);
        }
        Serial.println("got it");
       
        
        ///// homing
        
        axis1.startHoming();
        isHomeing =true;
        
        
        /////  normal steps
        
        
        //axis1.setSteps(1000,false,1000);
        //axis2.setSteps(500,true,1000);
        //ticker.setTicks(1000 );
        
    }
    
    
    
    unsigned long currentMicros = micros();
    unsigned long timeStep = currentMicros- previousMicros;
    previousMicros =currentMicros;
    if(isHomeing)
    {
        if(!axis1.isHome){
            axis1.stepHoming(timeStep);
        }else
        {
            axis2.stepHoming(timeStep);

        
        }
    }
    else
    {
        ticker.update(timeStep);
    }
}