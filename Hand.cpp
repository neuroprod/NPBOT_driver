//
//  NPBOT_handdriver.cpp
//  NPBOT-driver
//
//  Created by Kris Temmerman on 23/09/14.
//
//

#include "Hand.h"

void Hand::setup()
{

    Serial.begin(115200);
    servo1.attach(6);
    servo2.attach(7);
   
    servo1pos = 90;
    servo2pos =90;
    servo1.write(servo1pos);
    servo2.write(servo2pos);
    gripType =0;
}

void Hand::update()
{

    
    
    
    int numbytes =0;
    if(Serial.available()){
        numbytes  =Serial.readBytesUntil(0xff , serialData, 80);
    }
    
    if(numbytes>0)
    {
    
        if(serialData[0]==1){
            gripType =1;
            gripTargetLow =serialData[1];
             gripTargetHigh=serialData[2];
        }
        
        
       else if(serialData[0]==2){
        
            servo1pos = 45;
            servo2pos =145;
            servo1.write(servo1pos);
            servo2.write(servo2pos);
            gripType=0;
        }
        
       else if(serialData[0]==3){
            
            servo1pos = serialData[1];
            servo2pos =serialData[2];
            servo1.write(servo1pos);
            servo2.write(servo2pos);
            gripType=0;
        }
        
    }
    
    if(gripType==1){
    
        int sensorValue = 0;
        sensorValue = analogRead(4)/4;
    
        if(sensorValue>gripTargetHigh)
        {
            servo1pos--;
            servo2pos++;
            servo1.write(servo1pos);
            servo2.write(servo2pos);
       
        }else if(sensorValue<gripTargetLow)
        {
       
            servo1pos++;
            servo2pos--;
            servo1.write(servo1pos);
            servo2.write(servo2pos);
        }
        
        if(servo2pos<50)servo2pos=50;
        if(servo1pos<50 )servo1pos=50;
        if(servo2pos>135 )servo2pos=135;
        if(servo1pos>135 )servo1pos=135;
         Serial.write(111);
        Serial.write(servo1pos);
        Serial.write(servo2pos);
        Serial.write(sensorValue);
        delay(50);
        
        
    }

}