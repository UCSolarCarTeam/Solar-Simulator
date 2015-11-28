/**
 *  Schulich Delta OnBoard Media Control
 *  Copyright (C) 2015 University of Calgary Solar Car Team
 *
 *  This file is part of the Schulich Delta OnBoard Media Control
 *
 *  The Schulich Delta OnBoard Media Control is free software: 
 *  you can redistribute it and/or modify it under the terms 
 *  of the GNU Affero General Public License as published by 
 *  the Free Software Foundation, either version 3 of the
 *  License, or (at your option) any later version.
 *
 *  The Schulich Delta OnBoard Media Control is distributed 
 *  in the hope that it will be useful, but WITHOUT ANY WARRANTY; 
 *  without even the implied warranty of MERCHANTABILITY or 
 *  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Affero 
 *  General Public License for more details.
 *
 *  You should have received a copy of the GNU Affero General 
 *  Public License along with the Schulich Delta OnBoard Media 
 *  Control.  If not, see <http://www.gnu.org/licenses/>.
 *
 *  For further contact, email <software@calgarysolarcar.ca>
 */

#include "WiringPiButtons.hpp"
// Pin number declarations using WiringPi numbering scheme 
// 1 or UP is default -Not Pressed-, if button is pressed, the signal should go 0.
// Will only accept calls 10 times a second, this is a simple way to debounce


WiringPiButtons::WiringPiButtons()
{
    wiringPiSetup(); // Initialize wiringPi
    initButton(SPACE);
    initButton(VOLUMEDOWN);
    initButton(VOLUMEUP);
    initButton(NEXT);
    initButton(PREVIOUS);
    initButton(TOGGLEPLAY);
    state = RELEASED;
    period_start = std::chrono::high_resolution_clock::now();
    returnButton = RELEASED;
}

void WiringPiButtons::initButton(int buttonNumber)
{
    pinMode(buttonNumber, INPUT);      // Set button as INPUT
    pullUpDnControl(buttonNumber, PUD_UP); //Default Pulled UP
}

WiringPiButtons::Button WiringPiButtons::getEvents()
{

    deltaTime = std::chrono::duration_cast<std::chrono::duration<double>>(std::chrono::high_resolution_clock::now() - period_start);
    if (deltaTime.count() < 0.04)
    {
        return RELEASED;
    }
    period_start = std::chrono::high_resolution_clock::now(); 

    switch(state)
    {
        case RELEASED:
            if (returnButton != 0)
            {
                Button tempValue = returnButton;
                returnButton = RELEASED;
                return tempValue; 
            }

            if (!digitalRead(VOLUMEDOWN))      
                state = VOLUMEDOWN; 

            if (!digitalRead(VOLUMEUP))    
                state = VOLUMEUP; 

            if (!digitalRead(NEXT))
                state = NEXT;

            if (!digitalRead(PREVIOUS))  
                state = PREVIOUS; 
            
            if (!digitalRead(TOGGLEPLAY))  
                state = TOGGLEPLAY; 
            break;
        case VOLUMEDOWN:
            if (digitalRead(VOLUMEDOWN))
            {
                returnButton = VOLUMEDOWN;
                state = RELEASED; 
            }
            break;
        case VOLUMEUP:
            if (digitalRead(VOLUMEUP)) 
            {
                returnButton = VOLUMEUP;
                state = RELEASED; 
            }
            break;
        case NEXT:
            if (digitalRead(NEXT))
            {
                returnButton = NEXT;
                state = RELEASED; 
            }
            break;
        case PREVIOUS:
            if (digitalRead(PREVIOUS)) 
            {
                returnButton = PREVIOUS;
                state = RELEASED; 
            }
            break;
        case TOGGLEPLAY:
            if (digitalRead(TOGGLEPLAY)) 
            {
                returnButton = TOGGLEPLAY;
                state = RELEASED; 
            }
            break;
    }
}
