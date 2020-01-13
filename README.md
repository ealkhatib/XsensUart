# XsensUart
This library allows you to communicate with XSens module using UART.

How to use it:
1- Place this folder in your Arduino library folder
2- Open XSensUartTest.ino
3- Change this line HardwareSerial & XsensSerial = Serial2; to your serial port or you can use software serial.
4- Upload
5- You should see the following on the serial monitor (XsensTime,eular angels, and the angular velocity). All on Degrees or Degrees/s.

Note: In order to read other measurements provided by Xsens (e.g Acceleration), you have to add them manully on  XsensUart.cpp like what I did in XsensUart::parseData(). 

For more information visit https://www.xsens.com/ and https://base.xsens.com/hc/en-us/community/topics.

