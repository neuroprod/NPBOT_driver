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
    ticksLeft =0;
    

}
void Ticker::addAxis(Axis * axis )
{

    axises.push_back(axis);

}
void Ticker::setTicks(int numTicks )
{
    startTime =0;
    ticksLeft =numTicks;
}

void Ticker::update(double timeElapsed)
{
    
    if(ticksLeft ==0) return;
    
    
    
    startTime +=timeElapsed;
    if(startTime >500)
    {
    
        startTime -=500;
        
        
        if(pulsOn)
        {
            for(int i=0;i<axises.size();i++)
            {
             axises[i]->tickOn();
            }
       
            ticksLeft --;
            
            pulsOn =false;
            
        }else
        {
            
            for(int i=0;i<axises.size();i++)
            {
               axises[i]->tickOff();
            }
           
        
            pulsOn =true;
        
        }
    }
    

}