#  Schulich Delta OnBoard Media Control
#  Copyright (C) 2015 University of Calgary Solar Car Team
#
#  This file is part of the Schulich Delta OnBoard Media Control
#
#  The Schulich Delta OnBoard Media Control is free software: 
#  you can redistribute it and/or modify it under the terms 
#  of the GNU Affero General Public License as published by 
#  the Free Software Foundation, either version 3 of the
#  License, or (at your option) any later version.
#
#  The Schulich Delta OnBoard Media Control is distributed 
#  in the hope that it will be useful, but WITHOUT ANY WARRANTY; 
#  without even the implied warranty of MERCHANTABILITY or 
#  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Affero 
#  General Public License for more details.
#
#  You should have received a copy of the GNU Affero General 
#  Public License along with the Schulich Delta OnBoard Media 
#  Control.  If not, see <http://www.gnu.org/licenses/>.
#
#  For further contact, email <software@calgarysolarcar.ca>

#!/bin/bash

USER=`whoami`
if [ $USER = "root" ]
        then
        echo "Running as ROOT"
else
        echo "***********YOU ARE NOT ROOT************" 
        exit 0
fi

if [ -d "/home/Music" ]
then 
    echo "/home/Music exists!"
else 
    echo "Creating ~/Music Directory"
    mkdir /home/Music
fi

if [ -d `pwd`/../assets ]
then
    cp `pwd`/../assets/*.ttf /usr/share/fonts
    echo "Copied fonts from ../assets/ to /usr/share/fonts directory"
fi

if [ -d `pwd`/../SongLibrary ]
then
    cp `pwd`/../SongLibrary/*.mp3 /home/Music
    echo "Copied Music from ../SongLibrary to ~/Music directory"
fi

#echo "You are running on the pi, we will set up Auto Launch"
cd ..


ARCHITECTURE=`uname -m`
if [ ${ARCHITECTURE} = "armv7l" ]
then
    echo "You are running on armv7l. Assuming you are a Raspberry Pi"

    #Sets up Fastboot
    apt-get install systemd
    FASTBOOT=`cat /boot/cmdline.txt`
    SYSTEMSET=`echo $FASTBOOT | grep -o "systemd"`
    if [ -z $SYSTEMSET ]
    then
        sudo sh -c 'FASTBOOT=`cat /boot/cmdline.txt`; echo -n "$FASTBOOT init=/bin/systemd" > /boot/cmdline.txt'
    fi 
    
    #Sets up Autoboot
    FILECONTENTS=`grep -Eo "BackupCamera" /etc/rc.local`
    echo filecontents = ${FILECONTENTS[0]}
    if [ -z "${FILECONTENTS[0]}" ]
    then
            echo "Setting up AutoLaunch"
            sed -i '$ d' /etc/rc.local
            sudo sh -c 'CAMERAPATH=`pwd`; echo "$CAMERAPATH/BackupCamera" >> /etc/rc.local'
            echo "exit 0" >> /etc/rc.local
    else
            echo "Autolaunch already set up!"
    fi

else
    echo "Not on armv7l. Assuming you are not a Raspberry Pi"
fi


