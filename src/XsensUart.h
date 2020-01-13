#ifndef XSensUart_h
#define XSensUart_h

#include <Arduino.h>

class XsensUart {
  public:
    XsensUart(Stream& serial);
	

    void getMeasures();
    void parseData();
    void dataswapendian();
    void QuatToEuler ();

    float quat[4];
    float accel[3];
    float headingYaw;
    float mag[3];
    float rot[3];
    float euler[3];
    long XsensTime;
    boolean newData = false;


  private:
    Stream& serial_;
    void dataswapendian(uint8_t* data, uint8_t length);
    uint8_t data[4];
    uint8_t datadt[4];

    uint8_t datanotif[4];
    uint8_t datameas[256];

    const uint8_t len = 43;
    // Receiver Code
    const uint8_t numbytes = len;
    uint8_t receivedBytes[43];
    uint8_t tempBytes[43];        // temporary array for use when parsing



};


#endif //ODriveArduino_h
