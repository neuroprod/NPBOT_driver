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
    Serial.println("test");


}
void NPBOT::update(){}