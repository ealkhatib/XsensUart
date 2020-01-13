#include "XsensUart.h"

XsensUart::XsensUart(Stream& serial)
    : serial_(serial) {}

    
void XsensUart::getMeasures(){
  static boolean recvInProgress = false;
  static boolean recvInProgress2 = false;

  static byte ndx = 0;
  byte startbyte = 0xFA;
  byte secondbyte = 0xFF;
  byte rc;

  while (serial_.available() > 0 && newData == false) {
    rc = serial_.read();

    if (rc == startbyte) {
      recvInProgress = true;
      receivedBytes[0]  = 0xFA;
    }

    if (recvInProgress == true & rc == secondbyte) {
      recvInProgress2 = true;
    }

    if (recvInProgress == true & recvInProgress2 == true ) {
      if (ndx < len) {
        receivedBytes[ndx] = rc;
        ndx++;
      }
      else {
        recvInProgress = false;
        recvInProgress2 = false;

        ndx = 1;
        newData = true;
      }
    }
  }
}

void XsensUart::parseData(){
/* 	    for (int i = 0; i < len; ++i) {
      Serial.print(receivedBytes[i], HEX); Serial.print(",");
	     }
      Serial.println("->");
 */	
  // SampleTime = 0x1070;
  if (receivedBytes[4] == 0x10 & receivedBytes[5] == 0x60) {
    for (int i = 0; i < 4 ; i++) {
      datadt[i]= receivedBytes[7+i];
    }
    dataswapendian(datadt, sizeof(float));
	XsensTime = *( (long*) datadt );
  }

  // QUAT = 0x2010;
  if (receivedBytes[11] == 0x20 & receivedBytes[12] == 0x10) {
    for (int i = 0; i < 16 ; i++) {
      data[i]= receivedBytes[14+i];
    }
    dataswapendian(data, sizeof(float) * 4);
    memcpy(quat, data , sizeof(float) * 4);
  } 

   // rate = 0x8020;
  if (receivedBytes[30] == 0x80 & receivedBytes[31] == 0x20) {
    for (int i = 0; i < 12 ; i++) {
      data[i]= receivedBytes[33+i];
    }
    dataswapendian(data, sizeof(float) * 3);
    memcpy(rot, data , sizeof(float) * 3);
  } 
  
}


void XsensUart:: dataswapendian(uint8_t* data, uint8_t length) {
  uint8_t cpy[length];
  memcpy(cpy, data, length);
  for (int i = 0; i < length / 4; i++) {
    for (int j = 0; j < 4; j++) {
      data[j + i * 4] = cpy[3 - j + i * 4];
    }
  }

}

void  XsensUart::QuatToEuler ()
{
	parseData();
  float w = quat[0];
  float x = quat[1];
  float y = quat[2];
  float z = quat[3];



  // roll (x-axis rotation)
  double sinr_cosp = 2 * (w * x + y * z);
  double cosr_cosp = 1 - 2 * (x * x + y * y);
  euler[0] = atan2(sinr_cosp, cosr_cosp);

  // pitch (y-axis rotation)
  double sinp = 2 * (w * y - z * x);
  if (abs(sinp) >= 1)
    euler[1] = copysign(M_PI / 2, sinp); // use 90 degrees if out of range
  else
    euler[1] = asin(sinp);
  // yaw (z-axis rotation)
  double siny_cosp = 2 * (w * z + x * y);
  double cosy_cosp = 1 - 2 * (y * y + z * z);
  euler[2] = atan2(siny_cosp, cosy_cosp);


}
