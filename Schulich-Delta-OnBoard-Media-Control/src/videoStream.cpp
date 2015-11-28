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

#include "videoStream.hpp"


VideoStream::VideoStream()
{
    m_bufferNumber = 1; 
    m_updateImage = false;

}

void VideoStream::signalToQuit()
{
    m_quit = true;
}


void VideoStream::ThreadFunction()
{
    VideoCapture cap(0);
    while (!m_quit)
    {
        cap >> m_frame;
        switch(m_bufferNumber)
        {
            case 1:
                m_threadImage2 = m_frame;
                m_bufferNumber = 2;
                break;
            case 2:
                m_threadImage3 = m_frame;
                m_bufferNumber = 3;
                break;
            case 3:
                m_threadImage1 = m_frame;
                m_bufferNumber = 1;
                break;
        }
        m_updateImage = true;
    }
}

bool VideoStream::imageReady()
{
    return m_updateImage;
}

IplImage *VideoStream::getFrame()
{
    m_updateImage = false;
    switch(m_bufferNumber)
    {
        case 1:
            return &m_threadImage1;
        case 2:
            return &m_threadImage2;
        case 3:
            return &m_threadImage3;
    }
}
