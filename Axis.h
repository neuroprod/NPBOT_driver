//
//  Axis.h
//  NPBOT-driver
//
//  Created by Kris Temmerman on 13/09/14.
//
//

#ifndef __NPBOT_driver__Axis__
#define __NPBOT_driver__Axis__
class Axis
{

public:
    Axis();

    void setup(int _pullPin,int _dirPin);
    
    
    void setSteps (int steps,bool dir,int maxAxisSteps);
    int setTargetPos(int tarPosition);
    void startStepping (int maxAxisSteps);
    
    
    void tickOn();

    
    void tickOff();
    
    
    bool dir;
    int pullPin;
    int dirPin;
    
    int position;
    int stepsTodo;
    int dx;
    int dy;
    int px;
    int py;
    
    
    ////homeing
    void setupHomingParams(bool dir,int stepDelay,int homePin);
    void startHoming();
    void stepHoming(double timeElapsed);
    
    bool isHome;

    double homeTime;
    bool homePullToggle;
    int homePin;
    bool homeDir;
    int homeStepDelay;





};

#endif /* defined(__NPBOT_driver__Axis__) */
