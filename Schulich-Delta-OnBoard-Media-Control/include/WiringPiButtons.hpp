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

#ifndef WIRINGPIBUTTONS_HPP
#define WIRINGPIBUTTONS_HPP

#include <stdio.h> 
#include <wiringPi.h>
#include <chrono>

//using namespace std::chrono;

class WiringPiButtons
{
    public:
      enum Button { SPACE = 29, VOLUMEDOWN = 25, VOLUMEUP = 24, NEXT  = 23, PREVIOUS = 22, TOGGLEPLAY = 21, RELEASED = 0};
      WiringPiButtons();
      Button getEvents();  
      //run `gpio readall` on the pi to see the wiringPi numbering 

    private:
      void initButton(int buttonNumber);
      Button state;
      std::chrono::high_resolution_clock::time_point period_start;
      std::chrono::duration<double> deltaTime;
      Button returnButton;
};

#endif
