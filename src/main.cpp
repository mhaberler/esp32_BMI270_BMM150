
#ifdef M5UNIFIED
#include <M5Unified.h>
#endif
#include "Arduino_BMI270_BMM150.h"

BoschSensorClass *myIMU;

#ifndef I2CSPEED
#define I2CSPEED 100000
#endif

extern void i2cScan(void);

void print_data() {
  // we can also read accelerometer / gyro data here!
  Serial.println("Got new data!");
}

void setup() {
#ifdef M5UNIFIED
  auto cfg = M5.config();
  cfg.serial_baudrate = 115200;
  cfg.internal_imu = false; // default=true. use internal IMU.
  cfg.external_imu = false; // default=false. use Unit Accel & Gyro.
  cfg.led_brightness = 128; // default= 0. system LED brightness (0=off /
                            // 255=max) (※ not NeoPixel)
  M5.begin(cfg);
#ifdef RED_PORT
  Wire.begin(32, 33, I2CSPEED);
#else
  Wire.begin(21, 22,
             I2CSPEED); // Set the frequency of the SDA SCL.
                        // 设置SDA和SCL的频率
#endif
#else
  Serial.begin(115200);
#endif

  /* Wait for the Serial Monitor */
  while (!Serial) {
    yield();
  }

  i2cScan();

  myIMU = new BoschSensorClass(Wire);

  myIMU->debug(Serial);
#ifdef __MBED__
  myIMU->onInterrupt(print_data);
#endif
  myIMU->begin();

  Serial.print("Accelerometer sample rate = ");
  Serial.println(myIMU->accelerationSampleRate());
}

void loop() {
  // put your main code here, to run repeatedly:
  float x, y, z;

  if (myIMU->accelerationAvailable()) {
    myIMU->readAcceleration(x, y, z);
    Serial.printf(">accelX: %f\n>accelY: %f\n>accelz: %f\n", x, y, z);
  }

  if (myIMU->gyroscopeAvailable()) {
    myIMU->readGyroscope(x, y, z);
    Serial.printf(">gyroX: %f\n>gyroY: %f\n>gyroZ: %f\n", x, y, z);
  }

  if (myIMU->magneticFieldAvailable()) {

    myIMU->readMagneticField(x, y, z);
    Serial.printf(">magX: %f\n>magY: %f\n>magZ: %f\n", x, y, z);
  }
  delay(50);
}
