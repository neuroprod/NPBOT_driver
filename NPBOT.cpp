//
//  NPBOT.cpp
//  NPBOT-driver
//
//  Created by Kris Temmerman on 13/09/14.
//
//

#include "NPBOT.h"
#include <Arduino.h>


NPBOT::NPBOT() : serialEnd(  0xff ){}

void NPBOT::setup()
{



    Serial.begin(115200);
    isHomeing =false;
    previousMicros =0;
    // pull - dir
    axis1.setup(36,37);
    axis1.setupHomingParams(false,1000, 7);
    
    axis2.setup(47,46);
    axis2.setupHomingParams(true,1000, 6);
    
    axis3.setup(50,51);
    axis3.setupHomingParams(true,1000, 5);
    
    axis4.setup(53,52);
    axis4.setupHomingParams(true,1000, 4);

    axis5.setup(45,44);
    axis5.setupHomingParams(true,1000, 3);
    
    axis6.setup(43,42);
    axis6.setupHomingParams(true,1000, 2);
    
    
    axises.push_back(&axis1);
    axises.push_back(&axis2);
    axises.push_back(&axis3);
    axises.push_back(&axis4);
    axises.push_back(&axis5);
    axises.push_back(&axis6);
    
    
    ticker.addAxis(&axis1);
    //ticker.addAxis(&axis2);
     //ticker.addAxis(&axis3);
     //ticker.addAxis(&axis4);
     //ticker.addAxis(&axis5);
     //ticker.addAxis(&axis6);
    
    ticker.setup();
}
void NPBOT::checkSerial()
{
    int numbytes =0;
    if(Serial.available()){
        numbytes  =Serial.readBytesUntil(0xff , serialData, 80);
    }
    
    if(numbytes>0)
    {
        int command = serialData[0];
        if(command==0)
        {
            Serial.println("homing");
            axis1.startHoming();
           // axis2.startHoming();
            isHomeing =true;
        
        }else if(command==1)
        {
            int maxSteps =0;
            
            int target = serialData[2]*10000 +serialData[3]*100+serialData[4];
           
                       maxSteps = axis1.setTargetPos(target);
           
            axis1.startStepping(maxSteps);
            ticker.setTicks(maxSteps );
            
        
        }
    }
}

void NPBOT::update()
{
   
    
    checkSerial();
    
  
    
    
    
    unsigned long currentMicros = micros();
    unsigned long timeStep = currentMicros- previousMicros;
    previousMicros =currentMicros;
    if(isHomeing)
    {
        if(!axis1.isHome){
            axis1.stepHoming(timeStep);
        }else
        {
            isHomeing =false;
Serial.println("homing done");
        
        }
    }
    else
    {
        
        ticker.update(timeStep);
    }
}