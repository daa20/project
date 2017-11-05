#!/bin/bash

set -e

clear

# This descript display the date and who's logged on

echo -n "Current Date: "
date

echo

echo "Let's see who's logged into the system:"
who

echo 

echo USER: $USER

echo 

echo UID: $UID

echo HOME: $HOME

echo

a1=1
a2=$a1
date_string=$(date)
a3=$a1+$a2

echo The date_string: $date_string
echo 
echo "a1 + a2 = $a3"

today=$(date +%y%m%d)
echo "This is a test! --log.$today" > log.$today

