#!/bin/bash
if [ "$EUID" -ne 0 ]
  then echo "Please run as root"
  exit
fi
# apt update;
# apt upgrade -y;
if [ "$(lsb_release -is)" = "Ubuntu" ]
    then
    apt install build-essential -y
	apt install freeglut3-dev -y
	echo
    echo "Installed GLUT for Ubuntu."
	echo
elif [ "$(lsb_release -is)" = "Fedora" ]
    then 
	dnf install freeglut-devel
    echo
    echo "Installed GLUT for Ferdora. If not working you can also try running: yum install freeglut-devel"
    echo
exit
fi
