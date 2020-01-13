// Ehab Al Khatib

#include <XsensUart.h>

// ___ Xsens ______
// Define the serial port for the xsens
HardwareSerial & XsensSerial = Serial2;
// xsens object
XsensUart xsens(XsensSerial);


void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // set the data rate for the Serial port
  XsensSerial.begin(115200);
}

void loop() { // run over and over

  xsens.getMeasures();
  if (xsens.newData == true) {
      xsens.newData = false;
      xsens.QuatToEuler ();
      Serial.print(xsens.XsensTime*1e-4); Serial.print(" , ");
      Serial.print(xsens.euler[0] * 180 / PI); Serial.print(" , ");
      Serial.print(xsens.euler[1] * 180 / PI); Serial.print(" , ");
      Serial.print(xsens.euler[2] * 180 / PI); Serial.print(" , ");
      Serial.print(xsens.rot[0] * 180 / PI); Serial.print(" , ");
      Serial.print(xsens.rot[1] * 180 / PI); Serial.print(" , ");
      Serial.print(xsens.rot[2] * 180 / PI); Serial.print(" , ");
      Serial.println(" ");
      //Serial.println(micros()*1e-6);

    }
    delay(10);
  }
