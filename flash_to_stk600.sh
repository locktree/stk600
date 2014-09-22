#!/bin/bash          

echo "Make clean..."
make clean

echo "make all"
make all

echo "flashing.............."
sudo avrdude -p atmega2560 -c stk600 -P usb -U flash:w:$PWD/stk600.hex
