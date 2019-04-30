# Gesture Controlled Robot

A gesture controlled robot is a simple vehicle, whose movement is
controlled by the gestures or movement of a simple controller. Depending on the
gesture made using the controller, the robot can move forward, backward, left,
right or come to a halt.

## Features
* Wireless control
* Forward/Backward motion with 3-level speed controls
* Turn Left/Right both with and without forward/backward motion
* Front obstacle sensing to prevent collision during motion

# File organization



# Software requirements

Download and install the [Arduino IDE](https://www.arduino.cc/en/Main/Software/) to compile and run the .ino files.

Note that you would have to include the header files which we have defined like the motor.h, drive.h, transmit.h etc for the code to function appropriately.

# Hardware requirements

This project can be broadly classified and designed into two major parts:

1. Transmitter side: Gesture control

The components used on the transmitter side include a 2 axis accelerometer(ADXL335), an encoder(HT12E), a 433MHz RF     transmitter, a simple copper wire to be used as an antenna and the arduino uno board built using the ATmega32 chip. 
Connect the X and Y pins of the accelerometer to analog pins A0 and A1 of the Arduino board. Also connect the digital pins 10, 11, 12 and 13 of the Arduino to pins 8, 9, 10 and 11 of the digital encoder HT12E. The data pin of the transmitter is connected to DOUT (Pin 17) of the encoder. The rest of the connections are as shown in the wiring diagram.


2. Receiver side: Vehicle control

The components used on the receiver side include a 433MHz RF receiver, a decoder( HT12D), 2 dual H-bridge motor drivers( L298N), 4 motors and an ultrasonic sensor(HC-SR04).
Connect the 2 data pins of the RF receiver to the DIN pin( Pin 14) of the decoder. The digital output pins 10,11,12 and 13 of the decoder are connected to pins 16,17,18 and 19 to read the decoded data. This data is in turn used for the motor control using an H bridge with the following connections made for the 4 motors, each having an enable pin and 2 IN pins:


#define L298N_L_EN_B  (GPIO_PIN_9)
#define L298N_L_IN_3  (GPIO_PIN_11)
#define L298N_L_IN_4  (GPIO_PIN_8)

#define L298N_L_EN_A  (GPIO_PIN_10)
#define L298N_L_IN_1  (GPIO_PIN_13)
#define L298N_L_IN_2  (GPIO_PIN_12)

#define L298N_R_EN_A  (GPIO_PIN_6)
#define L298N_R_IN_1  (GPIO_PIN_7)
#define L298N_R_IN_2  (GPIO_PIN_4)

#define L298N_R_EN_B  (GPIO_PIN_5)
#define L298N_R_IN_3  (GPIO_PIN_3)
#define L298N_R_IN_4  (GPIO_PIN_2)

The TRIG and ECHO pin of the ultrasonic sensor are connected to the A0 and A1 pin of the Arduino. The rest of the connections are as seen in the wiring diagram.



## Working mechanism:

The X and Y values are read by the accelerometer based on the gestures made. These values are read using an AnalogRead and are compared to fixed predefined reference values for X and Y to encode the 4 digital pins for directions and speed values. This data is then transferred via the RF transmitter. 
On the receiver side, these values are further decoded for direction and speed control by making the respective motors rotate clockwise/anti-clockwise or by varying the PWM for speed control respectively. Also, an analog read on pins A0 and A1 are used for obstacle detection, thus stopping the forward movement of the vehicle when a certain distance value between the obstacle and the vehicle is obtained. The calculations for these are included in the code.


For further detailed information regarding this project, please take a look at the report and other important files available under docs.
