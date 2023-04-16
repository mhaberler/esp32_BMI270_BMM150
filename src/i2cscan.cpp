
#ifdef M5_I2CSCAN

#include <M5Unified.h>

void i2cScan(void) {
  Serial.printf("\ninternal I2C devices: ('Wire'):\n");
  bool scan[128];
  M5.In_I2C.scanID(scan);
  for (int i = 8; i < 0x7f; ++i) {
    if (scan[i]) {
      Serial.printf("intern: 0x%x\n", i);
    }
  }
#ifdef SECONDARY_I2C_PORT
  Serial.printf("\nexternal I2C (red port) devices: ('Wire1'):\n");
  M5.Ex_I2C.scanID(scan);
  for (int i = 8; i < 0x7f; ++i) {
    if (scan[i]) {
      Serial.printf("extern: 0x%x\n", i);
    }
  }
#endif
  Serial.println();
}

#else

#include <Arduino.h>
#include <Wire.h>

void printI2CBusScan(TwoWire &theWire, const char *tag) {
  theWire.begin();
  for (uint8_t addr = 0x8; addr <= 0x7f; addr++) {
    theWire.beginTransmission(addr);
    if (theWire.endTransmission() == 0) {
      Serial.printf("%s0x%x\n", tag, addr);
    }
  }
  Serial.println();
}

void i2cScan(void) {
  Serial.println("");
  Serial.println("");
  Serial.printf("Default port (Wire) I2C scan\n");
  printI2CBusScan(DEFAULT_I2C_PORT, "");

#if defined(SECONDARY_I2C_PORT)
  Serial.printf("Secondary port (Wire1) I2C scan\n");
  printI2CBusScan(SECONDARY_I2C_PORT, "";
#endif
  Serial.println("");
  Serial.println("");
}
#endif
