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

#ifndef I_THREADCLASS_H
#define I_THREADCLASS_H

#include <thread>


class I_ThreadClass
{
public:
    I_ThreadClass() { }
    virtual ~I_ThreadClass() { }

    bool StartThread()
    {
        if (pthread_create(&thread_tracker, NULL, ThreadReference, this) == 0)
        {
            return true;
        }
        else 
        {
            return false;
        }
    }

    void WaitForThreadToExit()
    {
        pthread_join(thread_tracker, NULL);
    }



protected: 
    /** Anything inheriting this class must define this function */
    virtual void ThreadFunction() = 0; 
    
private:
    static void * ThreadReference(void * thread_id)
    {
        ((I_ThreadClass *)thread_id)->ThreadFunction();
        return NULL;
    }

    pthread_t thread_tracker;
};
#endif
