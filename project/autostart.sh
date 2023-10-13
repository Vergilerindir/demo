#! /bin/bash

#checking if numpy is installed

check=numpy
value=$(pip show $check 2>&1 | grep -o 'not found')
if [ "$value" = "not found" ]; then
	echo "[$check] is not found"
	echo "starting install process"
	pip install $check
else
	echo "$check: Mevcut"
fi



#checking if matplotlib is installed

check=matplotlib
value=$(pip show $check 2>&1 | grep -o 'not found')
if [ "$value" = "not found" ]; then
	echo "[$check] is not found"
	echo "starting install process"
	pip install $check
else
	echo "$check: Mevcut"
fi

#checking if PySerial is installed

check=pyserial
value=$(pip show $check 2>&1 | grep -o 'not found')
if [ "$value" = "not found" ]; then
	echo "[$check] is not found"
	echo "starting install process"
	pip install $check
else
	echo "$check: Mevcut"
fi

#checking if PyQt is installed

check=pyqt5
value=$(pip show $check 2>&1 | grep -o 'not found')
if [ "$value" = "not found" ]; then
	echo "[$check] is not found"
	echo "starting install process"
	pip install $check
else
	echo "$check: Mevcut"
fi



#checking if PySide is installed

check=PySide2
value=$(pip show $check 2>&1 | grep -o 'not found')
if [ "$value" = "not found" ]; then
	echo "[$check] is not found"
	echo "starting install process"
	pip install $check
else
	echo "$check: Mevcut"
fi

#checking if libxcb-xinerama0 is installed

check=libxcb-xinerama0
value=$(dpkg -l | grep -o 'libxcb-xinerama0')
if [ "$value" = "$check" ]; then
	echo "$check: Mevcut"
else
	echo "[$check] is not found"
	echo "starting install process"
	sudo apt-get install $check
fi

python $(pwd)/gui/gui.py
