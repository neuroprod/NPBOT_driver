//
//  NPBOTHand.h
//  NPBOT-driver
//
//  Created by Kris Temmerman on 23/09/14.
//
//

#ifndef __NPBOT_driver__NPBOTHand__
#define __NPBOT_driver__NPBOTHand__

#include <Arduino.h>
#include <Servo.h>
class  Hand
{

public:
    Hand(){};
    void update();
    void setup();

   char serialData[80];
    char serialEnd ;

    Servo servo1;
    Servo servo2;
    
    int servo1pos;
    int servo2pos;
    int gripTargetLow;
    int gripTargetHigh;
    int gripType ;
};

#endif /* defined(__NPBOT_driver__NPBOT_handdriver__) */
