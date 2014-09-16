//
//  Ticker.cpp
//  NPBOT-driver
//
//  Created by Kris Temmerman on 13/09/14.
//
//

#include "Ticker.h"


Ticker::Ticker()
{


}
void Ticker::setup()
{

    pulsOn =false;
  
    maxInterval  = 100;//micro
    float maxInterValSec =(float )maxInterval/1000000.0f; //micro to sec
    
    float maxSpeed =1.0f/maxInterValSec;  //steps/sec
  
    
    
    accTime =0.5f;
    
    
    acceleration = (float)maxSpeed /accTime;  //speed/sec
    ticksTillMaxSpeed = acceleration *accTime*accTime/2 ;  //d= a* (t*t)  /2

   
}
void Ticker::addAxis(Axis * axis )
{

    axises.push_back(axis);

}
void Ticker::setTicks(int numTicks )
{
    startTime =0;
    ticksDone =0;
    totalTicks  =numTicks;
    
    if(totalTicks< 2* ticksTillMaxSpeed)
    {
        fullSpeedTick = slowDownTick = numTicks/2;
    
    }else
    {
        fullSpeedTick =ticksTillMaxSpeed;
        slowDownTick =totalTicks-ticksTillMaxSpeed;
    }
    
    
    
    setIntervalForNextTick();
}

void Ticker::update(double timeElapsed)
{
    
    if(ticksDone ==totalTicks) return;
    
    
    
    startTime +=timeElapsed;
    
    totalTime += timeElapsed;
    
    
    
   
    if(startTime >tickInterval)
    {
    
        startTime -=tickInterval;
        
        
        if(pulsOn)
        {
            for(int i=0;i<axises.size();i++)
            {
             axises[i]->tickOn();
            }
       //Serial.write(1);
             ticksDone ++;
            
            pulsOn =false;
            
        }else
        {
            
            for(int i=0;i<axises.size();i++)
            {
               axises[i]->tickOff();
            }
            setIntervalForNextTick();
        
            pulsOn =true;
        
        }
    }
    

}

void Ticker::setIntervalForNextTick()
{

    if(ticksDone>fullSpeedTick &&  ticksDone<slowDownTick )
    {
        tickInterval = maxInterval;
        
        
    }else if (ticksDone<=fullSpeedTick)
    {
    
        tickInterval =getIntervalForAccTick(ticksDone+1);
    
    }else
    {
        tickInterval =getIntervalForAccTick(totalTicks -ticksDone);

    
    }
   
}

int Ticker::getIntervalForAccTick(int tick )
{
  
    float timesqr =(float)tick / (0.5f *acceleration) ;
    float time  = sqrt (timesqr); //time for tick
    float speed  =acceleration*time;
    
    return 1000000/speed ;// ticks/sec->micro delay

}

