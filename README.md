# Receptionist Drone with CV

## Elevator Pitch:
Receptionist drone, have a flying assistant show you the way to the lobby. Powered by Sony Spresense.

## Story

We have seen many applications for drones; races, shows, and several others. But we have never seen a more social drone application. That is why we will make, perhaps the first receptionist drone in the world.

<img src="https://i.ibb.co/NnVwsLg/img.png" width="1000">

Always use technology to improve the world, if you are a black hat or gray hat hacker please abstain at this point ......... or at least leave your star to make me feel less guilty XP.

# Table of contents

* [Introduction](#introduction)
* [Materials](#materials)
* [Spresense Hardware](#spresense-hardware)
* [Spresense Software](#spresense-software)
* [Videos demonstrated the operation](#videos-demonstrated-the-operation:)
* [Tello Important Features](#tello-important-features)
* [Tello Software](#tello-software)
* [System Connection Diagram](#system-connection-diagram)
* [The Final Product](#the-final-product)
* [Comments](#comments)
* [References](#references)

## Introduction:

We will use the Spresense development board which will be able to interact with hotel users via Computer Vision. We know that there are robots receptionists and even robots with dinosaur forms that take orders in restaurants, but a drone that performs such work has been seldom seen. 

<img src="https://i.ibb.co/164hWN4/Drone-Botones.png" width="1000">

Through an Spresense development board and one ultrasonic distance sensor, we will detect customers and the drone will show the way to the client to arrive to reception, to make his check-in or booking.

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

Connections Diagram.

<img src="https://i.ibb.co/vcz2CsV/Spresense-bb.png" width="1000">

We need to make the following hardware connections in order to develope this project.

Real Connections.

<img src="https://i.ibb.co/5c34Bk7/IMG-3309.jpg" width="800">

## Spresense Software:

In order to program the Spresense development board, it is essential to follow the official SONY guide:

Official guide: https://developer.sony.com/develop/spresense/developer-tools/get-started-using-arduino-ide/set-up-the-arduino-ide

Since we are using the Arduino IDE, we will have to carry out this procedure to be able to flash the code you can find in the "Arduino Code" folder (at the bottom).

- Format the SD card (Highly Recommended).
- Plug the SD card in the Board.
- Open the following example code of the Arduino IDE.
<img src="https://i.ibb.co/Dp56GW1/Spresense-2.png" width="800">
- Flash the code on the board and open the serial monitor.
<img src="https://i.ibb.co/qB2hGhY/Capture.png" width="800">
- Select option 1 to mount the decoder to the SD.
<img src="https://i.ibb.co/cQMv76Z/Capture1.png" width="800">
- Once this is done, you can flash the code in the "Arduino Code" folder on the board, named "PlayerFull".

We attached some videos of the operation of the system, but first check what the code does, enjoy it!

- The MB1040 sensor will be used to detect when there is a customer near the device.

The MB1040 has an analog output which has to be converted to distance, the formula by performing the corresponding convertion is the following.

<img src="https://i.ibb.co/RBKhd0r/Code-Cogs-Eqn.gif" width="800">
<img src="https://i.ibb.co/ZmH9mNF/Code-Cogs-Eqn-1.gif" width="800">

The part of the code that performs this conversion is the following, the distance is shown in meters.

      distance=((sensorValue*0.00976*3)/0.3858); 

- The potentiometer will help us to modify the volume of the system easily.

Because the system works with digitally controlled volume, we will have to use an ADC system with a potentiometer to be able to modify the volume value analogically, this type of voltage control by a potentiometer is called a voltage divider.

<img src="https://hackster.imgix.net/uploads/attachments/789257/imagen_BVTlQgx8yM.png?auto=compress%2Cformat&w=1280&h=960&fit=max" width="800">

With our voltage divider installed, we will read the value of the voltage in the central pin, which according to its position will oscillate between 0 and 5 volts.

In our analogRead(A0) we will obtain a value of 10 bits between 0 and 1024, but since these values are not valid for the setVolume command, we had to make a map transforming the read range to a range between -800 to - 100

       analog=analogRead(A0);
       analog = map(analog, 0, 1023, -800, -100);
       theAudio->setVolume(analog);

Once we have the value on the variable analog we set the volume in each cycle of void loop ()

- The speaker will provide us the output of the message that will be played to the customers.

All the sound reproduction logic is done automatically thanks to the example code "Player" besides the audio file has to be called "Sound.mp3" and obviously be in mp3 format.

However, we have to play the audio every time a client comes close to the device, so we need restart this audio every so often.

       if (distance<2 && counter2==201)
       {
          // Start the audio if the distance is less than 2
         theAudio->startPlayer(AudioClass::Player0);
         puts("Play!"); 
         counter2=0;
       }
       if (counter2<200)
       {
         counter2++;
       }
       else if (counter2==200)
       {
       counter2++;
       theAudio->stopPlayer(AudioClass::Player0);
       myFile.close();
       myFile = theSD.open("Sound.mp3");
       puts("Reset Audio");
      }

The audio starts to play if the distance with the client is less than 2 meters, in turn the audio will restart once our variable "counter2" reaches 200, approximately 20 seconds.

- The button is used to activate the serial port to send the message that will call the Drone.

The Push Button libraries do not work on this board, so we made our own debounce algorithm to operate the button correctly.

       if (digitalRead(2)==LOW)
        {
          delay(10);
          if((digitalRead(2)==LOW))
          {
            puts("Calling Drone");
            delay(3000);
          }
        }

- Send the value in meters of the MB1040 sensor by serial.

To be able to send anything through Serial, it is necessary to use the "puts" command, instead of the classic "Serial.println()", unlike this command to be able to print variables of "int" type in serial, it is necessary to convert the int variable into a char* array, this can not be done automatically unless the following function.

      char* string2char(String command){
         if(command.length()!=0){
             char *p = const_cast<char*>(command.c_str());
             return p;
         }
      }

Now with this function we can call it in the following way to be able to print variables "int" type by serial.

       if(counter==9)
       {
        sensorValue/=10;  
        distance=((sensorValue*0.00976*3)/0.3858); 
        counter=0;
        sensorValue=0;
        puts(string2char(String(distance))); //This is the correct way to call the function
       }


- The connection to the raspberry or the pc will provide us the serial communication with Python to call the Drone.

To initialize the drone, we must send the following message by serial, this can be modified by the developer as desired.

       puts("Calling Drone");

Before we can call the drone with a serial command, we will have to know what is the COMXX port that the board has on our computer, this we will review with our ArduinoIDE.

<img src="https://hackster.imgix.net/uploads/attachments/789318/imagen_igPOPBXF3O.png?auto=compress%2Cformat&w=740&h=555&fit=max" width="800">

In the case of having several active serial ports, check which are the active ports.

<img src="https://hackster.imgix.net/uploads/attachments/789323/imagen_XqE3HNWYFl.png?auto=compress%2Cformat&w=740&h=555&fit=max" width="800">

Disconnect the Spresence and check which port has disappeared.

<img src="https://hackster.imgix.net/uploads/attachments/789326/imagen_qbtnXLKCQV.png?auto=compress%2Cformat&w=740&h=555&fit=max" width="800">

In this case the Spresense is in COM11, this data will be used in our Python code to receive serial commands from this port, the Baudrate of the Spresense is 115200 bauds.

      ser = serial.Serial("COM11", 115200)

So that the drone takes off just when we send the command and not before. We will have to put it in a while loop until it receives the message from the board by serial as shown below.

         while star==1:
             cc=str(ser.readline())
             if cc[2:][:-5]=="Calling Drone":
                 print(cc[2:][:-5])
                 star=2
                 break


## Videos demonstrated the operation:

Video 1: Detection, Volume and Speaker.

[![Video 1: Detection, Volume and Speaker.](https://i.ibb.co/QQ985bK/1.png)](https://youtu.be/dQ3Qmobqo6U)

Video 2: Serial Distance and Drone Call.

[![Video 2: Serial Distance and Drone Call.](https://i.ibb.co/SBbyjKt/2.png)](https://youtu.be/ojqytcHTXnQ)

## Tello Important Considerations:

- Check the propeller order, if the order of the propellers is not correct, the drone will not fly.
<img src="https://i.ibb.co/QJxjrsX/Correct-Drone-Propeller.png" width="600">

- This drone is very unstable outdoors because wind affects it, I recommend for it only to be used for indoor applications.

- I recommend using a protective cage so that the drone is 100% safe.

<img src="https://gloimg.gbtcdn.com/soa/gb/pdm-product-pic/Electronic/2019/01/14/goods_img_big-v1/20190114092657_21926.jpg" width="600">

- If you use the protective cage the drone can not perform flips, if you try them, the drone will fall and hit itself hard.

- Always check the battery level of the drone, if the battery is less than 10% the drone will not take off, also if it is flying and reaches 10% the drone will land.

## Tello Software:

Libraries that you have to install before continuing.

- https://pypi.org/project/tellopy/
- https://pypi.org/project/pyserial/
- https://pypi.org/project/av/
- https://pypi.org/project/opencv-python/
- https://pypi.org/project/numpy/

The flight algorithm of the Drone is based on pure programming along with the libraries that were previously mentioned. The algorithm reviews at all times that there is a human face in front of it and looks for the way to focus and approach.

Face recognition is done using Face Detection using Haar Cascades, the Haar Cascade file used will be in the "haarcascade" folder, inside "Python Code", more information in the link below.

Link: https://docs.opencv.org/3.4.3/d7/d8b/tutorial_py_face_detection.html

It is important to mention that this code provides the method to check all the sensors of the drone, for example the height, the level of the battery, position, etc ... However we added that the battery level has to be displayed in the OpenCV screen at all times:

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

The system works like a state machine, the case requires the command that makes the drone approach the client, with this type of system we avoid sending commands that are useless to the drone.

Lateral Fly Control Diagram (This is the diagram of how the drone moves if you are looking at it from the side):
<img src="https://i.ibb.co/qmyyPNW/Control.png" width="1000">

Frontal Fly Control Diagram (This is the diagram of how the drone moves if you are looking at it from the front):
<img src="https://i.ibb.co/nCCYmbw/Frontal-control-diagram.png" width="1000">

## System Connection Diagram:

This is our general connection diagram.

<img src="https://i.ibb.co/4Zz9tCM/Spresense-Diagram-bb.png" width="1000">

## The Final Product:

After all this process we have our receptionist drone!

Video: Click on the image:

[![Receptionist Drone with CV](https://i.ibb.co/164hWN4/Drone-Botones.png)](https://www.youtube.com/watch?v=3FCZAMbMd8s)

## Comments:

Faces are part of the inherent identity of people, and identifying individuals through their face has been a great inspiration to developers throughout the years. Face recognition capability is undoubtedly a key for drones to identify specific individuals or people in general. 

We have several use cases that we might explore in the future with this technology:

The search of missing elders or children in the neighborhood, identifying dangeorus criminals, etc...

Face recognition on drones will be a vital part moving forward, in order to disrupt the UAV (unmanned aerial vehicle) technologies.

## References:

All the information about the technology used, and direct references are in our wiki:

Wiki: https://github.com/altaga/Receptionist-Drone-with-CV/wiki

Top:

* [Table of Contents](#table-of-contents)
