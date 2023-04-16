
#ifdef M5STACK
#include <M5Unified.h>
#endif
#include "Arduino_BMI270_BMM150.h"

BoschSensorClass *myIMU;

extern void i2cScan(void);

void print_data() {
  // we can also read accelerometer / gyro data here!
  Serial.println("Got new data!");
}

void setup() {
#ifdef M5STACK
  auto cfg = M5.config();
  cfg.serial_baudrate = 115200;
  cfg.internal_imu = false; // default=true. use internal IMU.
  cfg.external_imu = false; // default=false. use Unit Accel & Gyro.
  cfg.led_brightness = 128; // default= 0. system LED brightness (0=off /
                            // 255=max) (※ not NeoPixel)
  M5.begin(cfg);
  // M5.Ex_I2C.begin();
#else
  Serial.begin(115200);
#endif

  /* Wait for the Serial Monitor */
  while (!Serial) {
    yield();
  }

  i2cScan();
  SENSOR_BUS.begin();

  myIMU = new BoschSensorClass(SENSOR_BUS);

  myIMU->debug(Serial);
  // myIMU->onInterrupt(print_data);
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
  delay(10);
}
