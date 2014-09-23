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

    Serial.begin(9600);
    servo1.attach(6);
    servo2.attach(7);
}

void Hand::update()
{

    int numbytes =0;
    if(Serial.available()){
        numbytes  =Serial.readBytesUntil(0xff , serialData, 80);
    }
    
    if(numbytes>0)
    {
      
        servo1.write(serialData[0]);
         servo2.write(serialData[1]);
        Serial.write(serialData[0]);
        Serial.write(serialData[1]);
    }


    


}