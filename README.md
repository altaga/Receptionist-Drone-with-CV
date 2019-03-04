# Receptionist Drone with CV
In the world we have seen many applications for drones; races, shows, but we have never seen a more social drone application. That is why we will make, perhaps the first receptionist drone in the world.

<img src="https://i.ibb.co/NnVwsLg/img.png" width="1000">

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

Diagram Connections.

<img src="https://i.ibb.co/vcz2CsV/Spresense-bb.png" width="1000">

We need to make the following hardware connections in order to develope this project.

Real Connections.

<img src="https://i.ibb.co/5c34Bk7/IMG-3309.jpg" width="800">

## Spresense Software:

In order to program the Spresense development board, it is essential to follow the official SONY guide, before following this manual it is absolutely necessary to follow it:

Official guide: https://developer.sony.com/develop/spresense/developer-tools/get-started-using-arduino-ide/set-up-the-arduino-ide

Since we connect the board to the Arduino IDE, we will have to carry out a previous procedure to be able to flash the code in the "Arduino Code" folder.

- Format the SD card (Highly Recommended).
- Paste the file in the "Audio" folder in the SD.
- Plug the SD card in the Board.
- Open the following example code of the Arduino IDE.
<img src="https://i.ibb.co/Dp56GW1/Spresense-2.png" width="800">
- Flash the code on the board and opens the serial monitor.
// Serial monitor image
- Select option 1 to mount the decoder to the SD.
// Image of the option.
- Once this is done, you can flash the code in the "Arduino Code" folder on the board.

We attach some videos of the operation of the system, which has the following functions.

- The MB1040 sensor will be used to detect when there is a customer near the device.
- The potentiometer will help us to modify the volume of the system easily.
- The speaker will provide us the output of the message that will be told to the customers.
- The button is used to activate the serial port to send the message that will call the Drone.
- The connection to the raspberry or the pc will provide us the serial communication with Python to call the Drone.

Note 1: The Push Button libraries do not work on this board so we made our own debounce algorithm to operate the button correctly.

      if (digitalRead(2)==LOW)
      {
        delay(10);
        if((digitalRead(2)==LOW))
        {
          puts("Calling Drone");
          delay(3000);
        }
      }

Note 2: The MB1040 has an analog output which has to be converted to distance, the part of the code that performs this conversion is the following, the distance is shown in meters.

    distance=((sensorValue*0.00976*3)/0.3858); 

Video 1: Detection, Volume and Speaker.

[![Video 1: Detection, Volume and Speaker.](https://i.ibb.co/QQ985bK/1.png)](https://youtu.be/dQ3Qmobqo6U)

Video 2: Serial Distance and Drone Call.

[![Video 2: Serial Distance and Drone Call.](https://i.ibb.co/SBbyjKt/2.png)](https://youtu.be/ojqytcHTXnQ)

## Tello Important Considerations:

- Check the propeller order, if the order of the propellers is not correct, the drone will not fly.
<img src="https://i.ibb.co/QJxjrsX/Correct-Drone-Propeller.png" width="600">

- This drone is very unstable outdoors because the wind affects it, I recommend it only be used for indoor applications.

- I recommend using a protective cage so that the drone is 100% safe.

<img src="https://gloimg.gbtcdn.com/soa/gb/pdm-product-pic/Electronic/2019/01/14/goods_img_big-v1/20190114092657_21926.jpg" width="600">

- If you use the protective cage the drone can not make flips, if you try the drone will fall and hit.

- Always check the battery level of the drone, if the battery is less than 10% the drone will not take off, also if it is flying and reaches 10% the drone will land.

## Tello Software:

Libraries that you have to install before continue.

- https://pypi.org/project/tellopy/
- https://pypi.org/project/pyserial/
- https://pypi.org/project/av/
- https://pypi.org/project/opencv-python/
- https://pypi.org/project/numpy/

The flight algorithm of the Drone is based on pure programming along with the libraries that were previously commented, the algorithm reviews at all times that there is a human face in front of it and looks for the way to focus and approach.

Face recognition is done using Face Detection using Haar Cascades, the Haar Cascade file used will be in the "Haar" folder, more information in the link below.

Link: https://docs.opencv.org/3.4.3/d7/d8b/tutorial_py_face_detection.html

It is important to mention, this code provide the method to check all the sensors of the drone, for example the height, the level of the battery, position, etc ... However in the code it is only attached that in the OpenCV screen it will be displayed all the time the level of the battery.

    def handler(event, sender, data, **args):
        global prev_flight_data
        global battery
        drone = sender
        if event is drone.EVENT_FLIGHT_DATA:
            if prev_flight_data != str(data):
                #print(data)
                datas=str(data)
                num = datas.find("BAT")
                battery=int(datas[num+4:-31])
                print("Battery:" + str(battery))
                prev_flight_data = str(data)
        else:
            print('event="%s" data=%s' % (event.getname(), str(data)))
            
            
<img src="https://i.ibb.co/n0SPQpc/rep.png" width="1000">

The system works like a state machine, because it keeps the state of the machine and as the case requires the command that requires the drone to approach the client, with this type of system we avoid sending commands that are useless to the drone.

Lateral Fly Control Diagram (This is the diagram of how the drone moves if you are looking it from the side):
<img src="https://i.ibb.co/qmyyPNW/Control.png" width="1000">

Frontal Fly Control Diagram (This is the diagram of how the drone moves if you are looking it from the front):
<img src="https://i.ibb.co/nCCYmbw/Frontal-control-diagram.png" width="1000">

## System Connection Diagram:

This is our general connection diagram.

<img src="https://i.ibb.co/4Zz9tCM/Spresense-Diagram-bb.png" width="1000">

## The Final Product:

After all this process we have our receptionist drone!

[![Receptionist Drone with CV](https://i.ibb.co/164hWN4/Drone-Botones.png)](https://www.youtube.com/watch?v=3FCZAMbMd8s)

## Comments:

## References:

All the information about the technology used, and direct references are in our wiki:

Wiki: 

Top:

* [Table of Contents](#table-of-contents)
