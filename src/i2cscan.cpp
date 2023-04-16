
#ifdef M5STACK

#include <M5Unified.h>

void i2cScan(void) {
  Serial.printf("\ninternal I2C devices: ('Wire'):\n");
  bool scan[128];
  M5.In_I2C.scanID(scan);
  for (int i = 8; i < 0x78; ++i) {
    if (scan[i]) {
      Serial.printf("intern: 0x%x\n", i);
    }
  }
  Serial.printf("\nexternal I2C (red port) devices: ('Wire1'):\n");
  M5.Ex_I2C.scanID(scan);
  for (int i = 8; i < 0x78; ++i) {
    if (scan[i]) {
      Serial.printf("extern: 0x%x\n", i);
    }
  }
  Serial.println();
}
#endif

#ifdef WROVER_KIT
#include <Arduino.h>
#include <Wire.h>

void i2cScan(void) {
  byte error, address;
  int nDevices;
  Serial.println("Scanning...");
  nDevices = 0;
  for (address = 8; address < 0x78; address++) {
    // The i2c_scanner uses the return value of
    // the Write.endTransmisstion to see if
    // a device did acknowledge to the address.
    Wire.beginTransmission(address);
    error = Wire.endTransmission();
    if (error == 0) {
      Serial.print("I2C device found at address 0x");
      if (address < 16)
        Serial.print("0");
      Serial.print(address, HEX);
      Serial.println("  !");
      nDevices++;
    } else if (error == 4) {
      Serial.print("Unknown error at address 0x");
      if (address < 16)
        Serial.print("0");
      Serial.println(address, HEX);
    }
  }
  if (nDevices == 0)
    Serial.println("No I2C devices found\n");
  else
    Serial.println("done\n");
}
#endif
