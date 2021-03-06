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

    sendCount=0;

    Serial.begin(115200);
    isHomeing =false;
    isFullHome =false;
    previousMicros =0;
    sendTime =0;
    // pull - dir
    axis1.setup(48,49,true);
    axis1.setupHomingParams(false,1000, 7);
    
    axis2.setup(47,46,false);
    axis2.setupHomingParams(true,2500, 6);
    
    axis3.setup(50,51,false);
    axis3.setupHomingParams(false,2500, 5);
    
    axis4.setup(53,52,false);
    axis4.setupHomingParams(false,5000, 4);

    axis5.setup(45,44,false);
    axis5.setupHomingParams(false,5000, 2);
    
    axis6.setup(43,42,false);
    axis6.setupHomingParams(false,1000, 3);
    
    
    axises.push_back(&axis1);
    axises.push_back(&axis2);
    axises.push_back(&axis3);
   axises.push_back(&axis4);
   axises.push_back(&axis5);
    axises.push_back(&axis6);
    
    
    ticker.addAxis(&axis1);
    ticker.addAxis(&axis2);
    ticker.addAxis(&axis3);
    ticker.addAxis(&axis4);
    ticker.addAxis(&axis5);
    ticker.addAxis(&axis6);
    
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
            
            axis1.startHoming();
            axis2.startHoming();
            axis3.startHoming();
            axis4.startHoming();
            axis5.startHoming();
            axis6.startHoming();
            isHomeing =true;
        
        }else if(command==1 && isFullHome)
        {
            
            int maxSteps =0;
            for (int i=0;i <axises.size();i++)
            {
                
                int pos =i*3 +1;
                int target = serialData[pos]*10000 +serialData[pos+1]*100+serialData[pos+2];
           
                int maxStepsTemp = axises[i]->setTargetPos(target);
                if(maxStepsTemp>maxSteps)maxSteps =maxStepsTemp;
                
            }
            axis1.startStepping(maxSteps);
            axis2.startStepping(maxSteps);
            axis3.startStepping(maxSteps);
             axis4.startStepping(maxSteps);
             axis5.startStepping(maxSteps);
             axis6.startStepping(maxSteps);
            ticker.setTicks(maxSteps );
            
        
        }else if(command==2) //setPositions
        {
            
            for (int i=0;i <axises.size();i++)
            {
                
                int pos =i*3 +1;
                int target = serialData[pos]*10000 +serialData[pos+1]*100+serialData[pos+2];
                
               axises[i]->position =target;
               
                
            }
            Serial.write(6);
            Serial.write(0xFF);
            isFullHome =true;
        }
    }
}
void NPBOT::sendData()
{

    
    if(axises[sendCount]->changed)
    {
        axises[sendCount]->changed =false;
        int position = axises[sendCount]->position;
        Serial.write(10);
        float workVal = (float) position;
        int val1 = floor(workVal/10000);
        workVal -= val1*10000;
        int val2 = floor(workVal/100);
        workVal -= val2*100;
        
        int val3 = workVal;
        Serial.write((uint8_t)sendCount);
        Serial.write((uint8_t)val1);
        Serial.write((uint8_t)val2);
        Serial.write((uint8_t)val3);
        Serial.write(0xFF);
        
    
    
    }
    sendCount++;
    
    if(sendCount>5)sendCount=0;
    sendTime =0;

}
void NPBOT::update()
{
   
    unsigned long currentMicros = micros();
    unsigned long timeStep = currentMicros- previousMicros;
    previousMicros =currentMicros;
    
    
    checkSerial();
    sendTime+=timeStep;
    if(sendTime>5000)sendData();
    
    
    
   
    if(isHomeing)
    {
      
       if(!axis1.isHome)axis1.stepHoming(timeStep);
        
        
         if(!axis4.isHome || !axis5.isHome || !axis6.isHome)
        {
             if(!axis6.isHome)axis6.stepHoming(timeStep);
            if(!axis4.isHome)axis4.stepHoming(timeStep);
             if(!axis5.isHome)axis5.stepHoming(timeStep);
            
        }
        else if(!axis2.isHome || !axis3.isHome || !axis1.isHome)
        {
            if(!axis2.isHome)axis2.stepHoming(timeStep);
            if(!axis3.isHome)axis3.stepHoming(timeStep);
            
        }else
        {
            isHomeing =false;
           
            
            Serial.write(5);
            Serial.write(0xFF);
        
        }
    }
    else
    {
        
        ticker.update(timeStep);
    }
}