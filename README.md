# Receptionist-Drone-with-CV
In the world we have seen many applications for drones; races, shows, but we have never seen a more social drone application. That is why we will make, perhaps the first receptionist drone in the world.

<img src="https://i.ibb.co/nb2X5vB/rep.png" width="1000">

Always use technology to improve the world, if you are a black hat or gray hat hacker please abstain at this point ......... or at least leave your star to make me feel less guilty XP.

# Table of contents

* [Introduction](#introduction)
* [Materials](#materials)
* [Spresense Hardware](#spresense-hardware)
* [Spresense Software](#spresense-software)
* [Tello Important Features](#tello-important-features)
* [Tello Software](#tello-software)
* [System Connection Diagram](#system-connection-diagram)
* [The Final Product](#the-final-product)
* [Comments](#comments)
* [References](#references)

## Introduction:

We will use the Spresense development board which will be able to interact with hotel users via Computer Vision. We know that there are robots receptionists and even robots with dinosaur forms that take orders in restaurants, but a drone that performs such work has been seldom seen. 

<img src="https://i.ibb.co/164hWN4/Drone-Botones.png" width="1000">

Through an Spresense development board and one ultrasonic distance sensor will detect customers and the drone accompanies the client to the reception, to make his check in or booking.

## Materials:

Hardware: 

- Spresense development board. 
- LV-MaxSonar-EZ4(MB1040)
- Potentiometer 10k.
- A big red Button.
- Micro Sd Card (in this case 16 Gb but any memory works).
- Speaker with integrated lithium Battery.
- DJI Drone Tello.
- RaspberryPi or any machine with Python (In this case my Laptop).

Software: 

- Arduino IDE. 
- Python.

Python Libraries:

- TelloPy.
- OpenCV.

## Spresense Hardware:

<img src="https://i.ibb.co/7t6VXcG/Spresense-1.png" width="1000">

We need to make the following hardware connections in order to develope this project.

- The MB1040 sensor will be used to detect when there is a customer near the device.
- The potentiometer will help us to modify the volume of the system easily.
- The speaker will provide us the output of the message that will be told to the customers.
- The button is used to activate the serial port to send the message that will call the Drone.
- The connection to the raspberry or the pc will provide us the serial communication with Python to call the Drone.

## Spresense Software:

In order to program the Spresense development board, it is essential to follow the official SONY guide, before following this manual it is absolutely necessary to follow it:

Official guide: https://developer.sony.com/develop/spresense/developer-tools/get-started-using-arduino-ide/set-up-the-arduino-ide

Since we connect the board to the Arduino IDE, we will have to carry out a previous procedure to be able to flash the code in the "Arduino Code" folder.

- Format the SD card (Highly Recommended).
- Plug the SD card in the Board.
- Open the following example code of the Arduino IDE.
<img src="https://i.ibb.co/Dp56GW1/Spresense-2.png" width="800">



## Tello Important Features:

## Tello Software:

## System Connection Diagram:

## The Final Product:

## Comments:

## References:

All the information about the technology used, and direct references are in our wiki:

Wiki: 

Top:

* [Table of Contents](#table-of-contents)
