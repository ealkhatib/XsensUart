# XsensUart
This library allows you to communicate with Xsens MTi 1-series DK module using UART.

How to use it:
1. Connect the Xsens MTi 1-series DK to the Arduino ( TX(Xsens) to RX(Arduino) , RX(Xsens) to TX(Arduino), and GRD(Xsens) to GRD(Arduino).
2. Place this folder in your Arduino library folder.
3. Open XSensUartTest.ino
4. Change this line HardwareSerial & XsensSerial = Serial2; to your serial port or you can use software serial.
5. Upload!
6. You should see the following on the serial monitor (XsensTime,eular angels, and the angular velocity). All units in Degrees or Degrees/s.

Note: In order to read other measurements provided by Xsens (e.g Acceleration), you have to add them manually on XsensUart.cpp like what I did in XsensUart::parseData(). 

For more information visit https://www.xsens.com/ and https://base.xsens.com/hc/en-us/community/topics.

